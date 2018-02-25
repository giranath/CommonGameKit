/*
 *  Copyright (c) 2017, Stefan Johnson
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this list
 *     of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice, this
 *     list of conditions and the following disclaimer in the documentation and/or other
 *     materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "RelationParentComponent.h"
#include "ComponentExpressions.h"
#include "EntityExpressions.h"

const CCString CCRelationParentComponentName = CC_STRING("parent");

static void CCRelationParentComponentDeserializer(CCComponent Component, CCExpression Arg);

static const CCComponentExpressionDescriptor CCRelationParentComponentDescriptor = {
    .id = CC_RELATION_PARENT_COMPONENT_ID,
    .initialize = NULL,
    .deserialize = CCRelationParentComponentDeserializer,
    .serialize = NULL
};

void CCRelationParentComponentRegister(void)
{
    CCComponentRegister(CC_RELATION_PARENT_COMPONENT_ID, CCRelationParentComponentName, CC_STD_ALLOCATOR, sizeof(CCRelationParentComponentClass), CCRelationParentComponentInitialize, NULL, CCRelationParentComponentDeallocate);
    
    CCComponentExpressionRegister(CC_STRING("parent"), &CCRelationParentComponentDescriptor, TRUE);
}

void CCRelationParentComponentDeregister(void)
{
    CCComponentDeregister(CC_RELATION_PARENT_COMPONENT_ID);
}

void CCRelationParentComponentDeserializer(CCComponent Component, CCExpression Arg)
{
    if (CCExpressionGetType(Arg) == CCExpressionValueTypeList)
    {
        const size_t ArgCount = CCCollectionGetCount(CCExpressionGetList(Arg));
        if (CCCollectionGetCount(CCExpressionGetList(Arg)) >= 2)
        {
            CCExpression NameExpr = *(CCExpression*)CCOrderedCollectionGetElementAtIndex(CCExpressionGetList(Arg), 0);
            if (CCExpressionGetType(NameExpr) == CCExpressionValueTypeAtom)
            {
                CCString Name = CCExpressionGetAtom(NameExpr);
                if (CCStringEqual(Name, CC_STRING("entity:")))
                {
                    if (ArgCount == 2)
                    {
                        CCExpression Entity = *(CCExpression*)CCOrderedCollectionGetElementAtIndex(CCExpressionGetList(Arg), 1);
                        if (CCExpressionGetType(Entity) == CCEntityExpressionValueTypeEntity)
                        {
                            CCRelationParentComponentSetParent(Component, CCExpressionGetData(Entity));
                        }
                        
                        else CC_LOG_ERROR("Expect value for argument (entity:) to be an entity");
                    }
                    
                    else CC_LOG_ERROR("Expect value for argument (entity:) to be an entity");
                }
            }
        }
    }
}