/*
 *  Copyright (c) 2016, Stefan Johnson
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

#ifndef CommonGameKit_AssetExpressions_h
#define CommonGameKit_AssetExpressions_h

#include <CommonGameKit/ExpressionEvaluator.h>
#include <CommonGameKit/GFX.h>


typedef enum {
    CCAssetExpressionValueTypeShader = 'shd\0',
    CCAssetExpressionValueTypeTexture = 'tex\0',
    CCAssetExpressionValueTypeFont = 'fnt\0',
    CCAssetExpressionValueTypeShaderLibrary = 'lib\0'
} CCAssetExpressionValueType;

typedef struct {
    CCString name;
    GFXShaderLibrary library;
} CCAssetExpressionValueShaderLibrary;


CC_EXPRESSION_EVALUATOR(shader) CCExpression CCAssetExpressionShader(CCExpression Expression);
CC_EXPRESSION_EVALUATOR(texture) CCExpression CCAssetExpressionTexture(CCExpression Expression);
CC_EXPRESSION_EVALUATOR(font) CCExpression CCAssetExpressionFont(CCExpression Expression);
CC_EXPRESSION_EVALUATOR(library) CCExpression CCAssetExpressionLibrary(CCExpression Expression);
CC_EXPRESSION_EVALUATOR(source) CCExpression CCAssetExpressionLibrarySource(CCExpression Expression);
CC_EXPRESSION_EVALUATOR(asset) CCExpression CCAssetExpressionAsset(CCExpression Expression);


#endif
