/*
 *  Copyright (c) 2015, Stefan Johnson
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

#include "GFXDraw.h"
#include "GFXMain.h"

static void GFXDrawInputElementDestructor(CCCollection Collection, GFXDrawInput *Element)
{
    CC_SAFE_Free(Element->name);
}

GFXDraw GFXDrawCreate(CCAllocatorType Allocator)
{
    GFXDraw Draw = CCMalloc(Allocator, sizeof(GFXDrawInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Draw)
    {
        *Draw = (GFXDrawInfo){
            .internal = NULL,
            .shader = NULL,
            .vertexBuffers = CCCollectionCreate(Allocator, CCCollectionHintSizeSmall, sizeof(GFXDrawInputVertexBuffer), (CCCollectionElementDestructor)GFXDrawInputElementDestructor),
            .buffers = CCCollectionCreate(Allocator, CCCollectionHintSizeSmall, sizeof(GFXDrawInputBuffer), (CCCollectionElementDestructor)GFXDrawInputElementDestructor),
            .textures = CCCollectionCreate(Allocator, CCCollectionHintSizeSmall, sizeof(GFXDrawInputTexture), (CCCollectionElementDestructor)GFXDrawInputElementDestructor),
            .destination = {
                .framebuffer = NULL,
                .index = 0
            },
            .index = {
                .buffer = NULL,
                .format = 0
            }

        };
        
        if (GFXMain->draw->optional.create) GFXMain->draw->optional.create(Allocator, Draw);
    }
    
    else CC_LOG_ERROR("Failed to create draw command due to allocation failure. Allocation size (%zu)", sizeof(GFXDrawInfo));
    
    return Draw;
}

void GFXDrawDestroy(GFXDraw Draw)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    if (GFXMain->draw->optional.destroy) GFXMain->draw->optional.destroy(Draw);
    
    CCCollectionDestroy(Draw->vertexBuffers);
    CCCollectionDestroy(Draw->buffers);
    CCCollectionDestroy(Draw->textures);
    CC_SAFE_Free(Draw);
}

void GFXDrawSubmit(GFXDraw Draw, GFXPrimitiveType Primitive, size_t Offset, size_t Count)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    GFXMain->draw->submit(Draw, Primitive, Offset, Count);
}

void GFXDrawSubmitIndexed(GFXDraw Draw, GFXPrimitiveType Primitive, size_t Offset, size_t Count)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    GFXMain->draw->indexedSubmit(Draw, Primitive, Offset, Count);
}

static void GFXDrawCacheShaderInputs(CCCollection Collection, GFXShader Shader)
{
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Collection, &Enumerator);
    
    for (GFXDrawInput *Current = CCCollectionEnumeratorGetCurrent(&Enumerator); Current; Current = CCCollectionEnumeratorNext(&Enumerator))
    {
        Current->shaderInput = GFXShaderGetInput(Shader, Current->name);
    }
}

void GFXDrawSetShader(GFXDraw Draw, GFXShader Shader)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    Draw->shader = Shader;
    
    if  (Shader)
    {
        GFXDrawCacheShaderInputs(Draw->vertexBuffers, Shader);
        GFXDrawCacheShaderInputs(Draw->buffers, Shader);
        GFXDrawCacheShaderInputs(Draw->textures, Shader);
    }
    
    if (GFXMain->draw->optional.setShader) GFXMain->draw->optional.setShader(Draw, Shader);
}

void GFXDrawSetFramebuffer(GFXDraw Draw, GFXFramebuffer Framebuffer, size_t Index)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    Draw->destination = (GFXDrawDestination){
        .framebuffer = Framebuffer,
        .index = Index
    };
    
    if (GFXMain->draw->optional.setFramebuffer) GFXMain->draw->optional.setFramebuffer(Draw, &Draw->destination);
}

void GFXDrawSetIndexBuffer(GFXDraw Draw, GFXBuffer Indexes, GFXBufferFormat Format)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    Draw->index = (GFXDrawIndexBuffer){
        .buffer = Indexes,
        .format = Format
    };
    
    if (GFXMain->draw->optional.setIndexBuffer) GFXMain->draw->optional.setIndexBuffer(Draw, &Draw->index);
}

static CCComparisonResult GFXDrawFindInput(const GFXDrawInput *left, const GFXDrawInput *right)
{
    return !strcmp(left->name, right->name) ? CCComparisonResultEqual : CCComparisonResultInvalid;
}

void GFXDrawSetVertexBuffer(GFXDraw Draw, const char *Input, GFXBuffer Buffer, GFXBufferFormat Format, size_t Stride, size_t Offset)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    GFXDrawInputVertexBuffer *VertexBuffer = CCCollectionGetElement(Draw->vertexBuffers, CCCollectionFindElement(Draw->vertexBuffers, &(GFXDrawInput){ .name = (char*)Input }, (CCComparator)GFXDrawFindInput));
    if (VertexBuffer)
    {
        VertexBuffer->buffer = Buffer;
        VertexBuffer->offset = Offset;
        VertexBuffer->stride = Stride;
        VertexBuffer->format = Format;
    }
    
    else
    {
        char *Str;
        CC_SAFE_Malloc(Str, sizeof(char) * (strlen(Input) + 1),
                       CC_LOG_ERROR("Failed to set vertex buffer input due to allocation failure. Allocation size: %zu", sizeof(char) * (strlen(Input) + 1));
                       return;
                       );
        
        strcpy(Str, Input);
        
        VertexBuffer = CCCollectionGetElement(Draw->vertexBuffers, CCCollectionInsertElement(Draw->vertexBuffers, &(GFXDrawInputVertexBuffer){
            .input = {
                .name = Str,
                .shaderInput = Draw->shader ? GFXShaderGetInput(Draw->shader, Input) : NULL
            },
            .buffer = Buffer,
            .offset = Offset,
            .stride = Stride,
            .format = Format
        }));
    }
    
    if (GFXMain->draw->optional.setVertexBuffer) GFXMain->draw->optional.setVertexBuffer(Draw, VertexBuffer);
}

void GFXDrawSetBuffer(GFXDraw Draw, const char *Input, GFXBuffer Buffer)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    GFXDrawInputBuffer *UniformBuffer = CCCollectionGetElement(Draw->buffers, CCCollectionFindElement(Draw->buffers, &(GFXDrawInput){ .name = (char*)Input }, (CCComparator)GFXDrawFindInput));
    if (UniformBuffer)
    {
        UniformBuffer->buffer = Buffer;
    }
    
    else
    {
        char *Str;
        CC_SAFE_Malloc(Str, sizeof(char) * (strlen(Input) + 1),
                       CC_LOG_ERROR("Failed to set buffer input due to allocation failure. Allocation size: %zu", sizeof(char) * (strlen(Input) + 1));
                       return;
                       );
        
        strcpy(Str, Input);
        
        UniformBuffer = CCCollectionGetElement(Draw->buffers, CCCollectionInsertElement(Draw->buffers, &(GFXDrawInputBuffer){
            .input = {
                .name = Str,
                .shaderInput = Draw->shader ? GFXShaderGetInput(Draw->shader, Input) : NULL
            },
            .buffer = Buffer
        }));
    }
    
    if (GFXMain->draw->optional.setBuffer) GFXMain->draw->optional.setBuffer(Draw, UniformBuffer);
}

void GFXDrawSetTexture(GFXDraw Draw, const char *Input, GFXTexture Texture)
{
    CCAssertLog(Draw, "Draw must not be null");
    
    GFXDrawInputTexture *UniformTexture = CCCollectionGetElement(Draw->textures, CCCollectionFindElement(Draw->textures, &(GFXDrawInput){ .name = (char*)Input }, (CCComparator)GFXDrawFindInput));
    if (UniformTexture)
    {
        UniformTexture->texture = Texture;
    }
    
    else
    {
        char *Str;
        CC_SAFE_Malloc(Str, sizeof(char) * (strlen(Input) + 1),
                       CC_LOG_ERROR("Failed to set texture input due to allocation failure. Allocation size: %zu", sizeof(char) * (strlen(Input) + 1));
                       return;
                       );
        
        strcpy(Str, Input);
        
        UniformTexture = CCCollectionGetElement(Draw->textures, CCCollectionInsertElement(Draw->textures, &(GFXDrawInputTexture){
            .input = {
                .name = Str,
                .shaderInput = Draw->shader ? GFXShaderGetInput(Draw->shader, Input) : NULL
            },
            .texture = Texture
        }));
    }
    
    if (GFXMain->draw->optional.setTexture) GFXMain->draw->optional.setTexture(Draw, UniformTexture);
}
