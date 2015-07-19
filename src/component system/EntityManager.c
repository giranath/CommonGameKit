//
//  EntityManager.c
//  Blob Game
//
//  Created by Stefan Johnson on 23/02/2015.
//  Copyright (c) 2015 Stefan Johnson. All rights reserved.
//

#include "EntityManager.h"
#include "Entity.h"
#include "ComponentBase.h"
#include "ComponentSystem.h"
#include <CommonC/Common.h>
#include <tinycthread.h>
#include <stdatomic.h>


typedef struct {
    CCCollection active, added, removed, destroy;
    atomic_flag addedLock, removedLock;
} CCEntityManager;

static CCEntityManager EntityManager = {
    .addedLock = ATOMIC_FLAG_INIT,
    .removedLock = ATOMIC_FLAG_INIT
};

static void CCEntityDestructor(CCCollection Collection, CCEntity *Entity)
{
    CCEntityDestroy(*Entity);
}

static mtx_t Lock;
void CCEntityManagerCreate(void)
{
    int err;
    if ((err = mtx_init(&Lock, mtx_plain | mtx_recursive)) != thrd_success)
    {
        CC_LOG_ERROR("Failed to create entity manager lock (%d)", err);
        exit(EXIT_FAILURE); //TODO: How should we handle this?
    }
    
    EntityManager = (CCEntityManager){
        .active = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeMedium | CCCollectionHintHeavyEnumerating | CCCollectionHintHeavyInserting | CCCollectionHintHeavyDeleting, sizeof(CCEntity), NULL),
        .added = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall | CCCollectionHintHeavyInserting | CCCollectionHintHeavyDeleting, sizeof(CCEntity), NULL),
        .removed = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall | CCCollectionHintHeavyInserting | CCCollectionHintHeavyDeleting, sizeof(CCEntity), NULL),
        .destroy = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall | CCCollectionHintHeavyInserting | CCCollectionHintHeavyDeleting, sizeof(CCEntity), (CCCollectionElementDestructor)CCEntityDestructor),
        .addedLock = ATOMIC_FLAG_INIT,
        .removedLock = ATOMIC_FLAG_INIT
    };
}

void CCEntityManagerDestroy(void)
{
    mtx_destroy(&Lock);
    
    if (EntityManager.active) CCCollectionDestroy(EntityManager.active);
    if (EntityManager.added) CCCollectionDestroy(EntityManager.added);
    if (EntityManager.removed) CCCollectionDestroy(EntityManager.removed);
    if (EntityManager.destroy) CCCollectionDestroy(EntityManager.destroy);
}

void CCEntityManagerUpdate(void)
{
    //Add to active
    while (!atomic_flag_test_and_set(&EntityManager.addedLock));
    CCCollectionInsertCollection(EntityManager.active, EntityManager.added, NULL); //TODO: make a consumed insert or a retained list?
    
    CCCollectionRemoveAllElements(EntityManager.added);
    
    atomic_flag_clear(&EntityManager.addedLock);
    
    
    //Remove from active
    while (!atomic_flag_test_and_set(&EntityManager.removedLock));
    CCCollection Entries = CCCollectionFindCollection(EntityManager.active, EntityManager.removed, NULL);
    CCCollectionRemoveCollection(EntityManager.active, Entries);
    CCCollectionDestroy(Entries);
    
    CCCollectionInsertCollection(EntityManager.destroy, EntityManager.removed, NULL); //TODO: make a consumed insert or a retained list?
    
    CCCollectionRemoveAllElements(EntityManager.removed);
    atomic_flag_clear(&EntityManager.removedLock);
    
    
    CCCollection DestroyableEntries = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall | CCCollectionHintHeavyInserting, sizeof(CCCollectionEntry), NULL);
    
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(EntityManager.destroy, &Enumerator);
    for (CCEntity *Entity = CCCollectionEnumeratorGetCurrent(&Enumerator); Entity; Entity = CCCollectionEnumeratorNext(&Enumerator))
    {
        _Bool DestroyEntity = TRUE;
        CCEnumerator ComponentEnumerator;
        CCCollectionGetEnumerator(CCEntityGetComponents(*Entity), &ComponentEnumerator);
        for (CCComponent *Component = CCCollectionEnumeratorGetCurrent(&ComponentEnumerator); Component; Component = CCCollectionEnumeratorNext(&ComponentEnumerator))
        {
            if (CCComponentGetIsManaged(*Component))
            {
                CCComponentSystemRemoveComponent(*Component);
                DestroyEntity = FALSE;
            }
        }
        
        
        if (DestroyEntity) CCCollectionInsertElement(DestroyableEntries, &(CCCollectionEntry){ CCCollectionEnumeratorGetEntry(&Enumerator) });
    }
    
    CCCollectionRemoveCollection(EntityManager.destroy, DestroyableEntries);
    CCCollectionDestroy(DestroyableEntries);
}

void CCEntityManagerAddEntity(CCEntity Entity)
{
    while (!atomic_flag_test_and_set(&EntityManager.addedLock));
    CCCollectionInsertElement(EntityManager.added, &Entity);
    atomic_flag_clear(&EntityManager.addedLock);
}

void CCEntityManagerRemoveEntity(CCEntity Entity)
{
    while (!atomic_flag_test_and_set(&EntityManager.removedLock));
    CCCollectionInsertElement(EntityManager.removed, &Entity);
    atomic_flag_clear(&EntityManager.removedLock);
}

CCCollection CCEntityManagerGetEntities(void)
{
    return EntityManager.active;
}

_Bool CCEntityManagerTryLock(void)
{
    int err = mtx_trylock(&Lock);
    if ((err != thrd_success) && (err != thrd_busy))
    {
        CC_LOG_ERROR("Failed to lock entity manager (%d)", err);
    }
    
    return err == thrd_success;
}

void CCEntityManagerLock(void)
{
    int err;
    if ((err = mtx_lock(&Lock)) != thrd_success)
    {
        CC_LOG_ERROR("Failed to lock entity manager (%d)", err);
    }
}

void CCEntityManagerUnlock(void)
{
    int err;
    if ((err = mtx_unlock(&Lock)) != thrd_success)
    {
        CC_LOG_ERROR("Failed to unlock entity manager (%d)", err);
    }
}