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

@import Cocoa;
@import OpenGL.GL3;
@import XCTest;

#import "GFX.h"
#import "GLGFX.h"
#import "GLSetup.h"

@interface GLGFXTests : XCTestCase

@end

@implementation GLGFXTests
{
    CGLContextObj ctx;
}

-(void) setUp
{
    [super setUp];
    
    CGLPixelFormatObj PixelFormat;
    CGLChoosePixelFormat((CGLPixelFormatAttribute[]){
        kCGLPFAAllRenderers,
        kCGLPFAStencilSize, 1,
        kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_GL4_Core,
        0
    }, &PixelFormat, &(GLint){0});
    
    CGLCreateContext(PixelFormat, NULL, &ctx);
    CGLDestroyPixelFormat(PixelFormat);
    
    CGLSetCurrentContext(ctx);
    
    GLGFXSetup();
}

-(void) tearDown
{
    CGLSetCurrentContext(NULL);
    
    CGLReleaseContext(ctx);
    CCGLStateDestroy(CCGLCurrentState);
    CCGLCurrentState = NULL;
    
    [super tearDown];
}

-(void) testTextureBounds
{
    GFXTexture Root = GFXTextureCreate(CC_STD_ALLOCATOR, GFXTextureHintDimension1D, CCColourFormatRGB8Unorm, 100, 1, 1, NULL);
    
    GFXTexture Sub = GFXTextureCreateSubTexture(CC_STD_ALLOCATOR, Root, 10, 0, 0, 5, 1, 1, NULL);
    
    GFXTexture Sub2 = GFXTextureCreateSubTexture(CC_STD_ALLOCATOR, Sub, 2, 0, 0, 2, 1, 1, NULL);
    
    CCVector3D Bottom, Top;
    GFXTextureGetBounds(Sub2, &Bottom, &Top);
    
    XCTAssertEqual(Bottom.x, 0.12f, @"Should have correct coord");
    XCTAssertEqual(Bottom.y, 0.0f, @"Should have correct coord");
    XCTAssertEqual(Bottom.z, 0.0f, @"Should have correct coord");
    
    XCTAssertEqual(Top.x, 0.14f, @"Should have correct coord");
    XCTAssertEqual(Top.y, 1.0f, @"Should have correct coord");
    XCTAssertEqual(Top.z, 1.0f, @"Should have correct coord");
    
    
    GFXTextureGetBounds(Sub, &Bottom, &Top);
    
    XCTAssertEqual(Bottom.x, 0.1f, @"Should have correct coord");
    XCTAssertEqual(Bottom.y, 0.0f, @"Should have correct coord");
    XCTAssertEqual(Bottom.z, 0.0f, @"Should have correct coord");
    
    XCTAssertEqual(Top.x, 0.15f, @"Should have correct coord");
    XCTAssertEqual(Top.y, 1.0f, @"Should have correct coord");
    XCTAssertEqual(Top.z, 1.0f, @"Should have correct coord");
    
    
    GFXTextureGetBounds(Root, &Bottom, &Top);
    
    XCTAssertEqual(Bottom.x, 0.0f, @"Should have correct coord");
    XCTAssertEqual(Bottom.y, 0.0f, @"Should have correct coord");
    XCTAssertEqual(Bottom.z, 0.0f, @"Should have correct coord");
    
    XCTAssertEqual(Top.x, 1.0f, @"Should have correct coord");
    XCTAssertEqual(Top.y, 1.0f, @"Should have correct coord");
    XCTAssertEqual(Top.z, 1.0f, @"Should have correct coord");
    
    GFXTextureDestroy(Sub2);
    GFXTextureDestroy(Sub);
    GFXTextureDestroy(Root);
}

-(void) testTextureCoordNormalization
{
    GFXTexture Root = GFXTextureCreate(CC_STD_ALLOCATOR, GFXTextureHintDimension1D, CCColourFormatRGB8Unorm, 100, 1, 1, NULL);
    
    GFXTexture Sub = GFXTextureCreateSubTexture(CC_STD_ALLOCATOR, Root, 10, 0, 0, 5, 1, 1, NULL);
    
    GFXTexture Root2 = GFXTextureCreate(CC_STD_ALLOCATOR, GFXTextureHintDimension1D, CCColourFormatRGB8Unorm, 50, 1, 1, NULL);
    
    CCVector3D Multiplier = GFXTextureGetMultiplier(Root);
    
    XCTAssertEqual(Multiplier.x, 0.01f, @"Should have correct multiplier");
    XCTAssertEqual(Multiplier.y, 1.0f, @"Should have correct multiplier");
    XCTAssertEqual(Multiplier.z, 1.0f, @"Should have correct multiplier");
    
    
    Multiplier = GFXTextureGetMultiplier(Sub);
    
    XCTAssertEqual(Multiplier.x, 0.01f, @"Should have correct multiplier");
    XCTAssertEqual(Multiplier.y, 1.0f, @"Should have correct multiplier");
    XCTAssertEqual(Multiplier.z, 1.0f, @"Should have correct multiplier");
    
    
    Multiplier = GFXTextureGetMultiplier(Root2);
    
    XCTAssertEqual(Multiplier.x, 0.02f, @"Should have correct multiplier");
    XCTAssertEqual(Multiplier.y, 1.0f, @"Should have correct multiplier");
    XCTAssertEqual(Multiplier.z, 1.0f, @"Should have correct multiplier");
    
    GFXTextureDestroy(Root2);
    GFXTextureDestroy(Sub);
    GFXTextureDestroy(Root);
}

@end