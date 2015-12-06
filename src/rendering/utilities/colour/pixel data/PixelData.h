/*
 *  Copyright (c) 2015 Stefan Johnson
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

#ifndef Blob_Game_PixelData_h
#define Blob_Game_PixelData_h

#include "Colour.h"
#include <CommonC/Allocator.h>


typedef struct CCPixelDataInfo *CCPixelData;

typedef void *(*CCPixelDataConstructorCallback)(CCAllocatorType Allocator);
typedef void (*CCPixelDataDestructorCallback)(void *Internal);
typedef CCColour (*CCPixelDataGetColourCallback)(CCPixelData Pixels, size_t x, size_t y, size_t z);
typedef void (*CCPixelDataGetSizeCallback)(CCPixelData Pixels, size_t *Width, size_t *Height, size_t *Depth);
typedef void (*CCPixelDataGetPackedDataCallback)(CCPixelData Pixels, CCColourFormat Type, size_t Width, size_t Height, size_t Depth, void *Data);


typedef struct {
    CCPixelDataConstructorCallback create;
    CCPixelDataDestructorCallback destroy;
    CCPixelDataGetColourCallback colour;
    struct {
        CCPixelDataGetSizeCallback size;
        CCPixelDataGetPackedDataCallback packedData;
    } optional;
} CCPixelDataInterface;

typedef struct CCPixelDataInfo {
    const CCPixelDataInterface *interface;
    CCAllocatorType allocator;
    CCColourFormat format;
    void *internal;
} CCPixelDataInfo, *CCPixelData;


CCPixelData CCPixelDataCreate(CCAllocatorType Allocator, CCColourFormat Format, const CCPixelDataInterface *Interface);
void CCPixelDataDestroy(CCPixelData Pixels);
CCColour CCPixelDataGetColour(CCPixelData Pixels, size_t x, size_t y, size_t z);
_Bool CCPixelDataHasSize(CCPixelData Pixels);
void CCPixelDataGetSize(CCPixelData Pixels, size_t *Width, size_t *Height, size_t *Depth);
void CCPixelDataGetPackedData(CCPixelData Pixels, size_t Width, size_t Height, size_t Depth, void *Data);
void CCPixelDataGetPackedDataWithFormat(CCPixelData Pixels, CCColourFormat Type, size_t Width, size_t Height, size_t Depth, void *Data);
_Bool CCPixelDataInsideBounds(CCPixelData Pixels, size_t x, size_t y, size_t z);
unsigned int CCPixelDataGetPlaneCount(CCPixelData Pixels);

#endif