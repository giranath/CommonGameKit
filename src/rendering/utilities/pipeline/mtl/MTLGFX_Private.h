/*
 *  Copyright (c) 2019, Stefan Johnson
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

#ifndef CommonGameKit_MTLGFX_Private_h
#define CommonGameKit_MTLGFX_Private_h

#import "MTLGFX.h"
#import <CommonObjc/Common.h>
@import Metal;

typedef struct {
    _Bool allowGPUOptimizedContents;
} MTLInternalFeatureMTLTextureDescriptor;

typedef struct {
    _Bool inputPrimitiveTopology;
    _Bool vertexBuffers;
    _Bool fragmentBuffers;
} MTLInternalFeatureMTLRenderPipelineDescriptor;

typedef struct {
    MTLInternalFeatureMTLTextureDescriptor MTLTextureDescriptor;
    MTLInternalFeatureMTLRenderPipelineDescriptor MTLRenderPipelineDescriptor;
} MTLInternalSupport;

typedef struct {
    __unsafe_unretained id <MTLDevice>device;
    __unsafe_unretained id <MTLCommandQueue>commandQueue;
    GFXTexture drawable;
    MTLInternalSupport *support;
    __unsafe_unretained id <MTLSamplerState>samplers[255];
} MTLInternal;

id <MTLSamplerState>MTLGFXGetSampler(GFXTextureHint Hint);

#endif

