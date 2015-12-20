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

#ifndef Blob_Game_GFXShaderLibrary_h
#define Blob_Game_GFXShaderLibrary_h

#include <CommonC/Common.h>

typedef enum {
    //GFXShaderSourceTypeHeader, //TODO: add a header type
    GFXShaderSourceTypeVertex,
    GFXShaderSourceTypeFragment
} GFXShaderSourceType;


typedef struct GFXShaderLibrary *GFXShaderLibrary;
typedef struct GFXShaderSource *GFXShaderSource;


/*!
 * @brief Create a shader library.
 * @description A library to lookup shader sources from to use to create shaders.
 * @param Allocator The allocator to be used for the allocations.
 * @return The created shader library.
 */
GFXShaderLibrary GFXShaderLibraryCreate(CCAllocatorType Allocator);
//GFXShaderLibrary GFXShaderLibraryCreateFromProject(CCAllocatorType Allocator, FSPath Path);

/*!
 * @brief Destroy a shader library.
 * @param Library The shader library to be destroyed.
 */
void GFXShaderLibraryDestroy(GFXShaderLibrary Library);

/*!
 * @brief Compile a shader.
 * @param Library The shader library to compile the shader.
 * @param Type The shader source type.
 * @param Name The name to reference the compiled shader source.
 * @param Source The sourcecode for the shader.
 * @return The compiled shader source.
 */
const GFXShaderSource GFXShaderLibraryCompile(GFXShaderLibrary Library, GFXShaderSourceType Type, const char *Name, const char *Source);

/*!
 * @brief Lookup a compiled shader.
 * @param Library The shader library to lookup the shader in.
 * @param Name The name of the compiled shader source.
 * @return The compiled shader source.
 */
const GFXShaderSource GFXShaderLibraryGetSource(GFXShaderLibrary Library, const char *Name);

#endif