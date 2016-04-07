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

#include "ExpressionHelpers.h"
#include "ExpressionEvaluator.h"


CCExpression CCExpressionCreateVector2(CCAllocatorType Allocator, CCVector2D v)
{
    CCExpression Expr = CCExpressionCreateList(Allocator);
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.y) });
    
    return Expr;
}

CCExpression CCExpressionCreateVector3(CCAllocatorType Allocator, CCVector3D v)
{
    CCExpression Expr = CCExpressionCreateList(Allocator);
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.y) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.z) });
    
    return Expr;
}

CCExpression CCExpressionCreateVector4(CCAllocatorType Allocator, CCVector4D v)
{
    CCExpression Expr = CCExpressionCreateList(Allocator);
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.y) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.z) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, v.w) });
    
    return Expr;
}

CCExpression CCExpressionCreateVector2i(CCAllocatorType Allocator, CCVector2Di v)
{
    CCExpression Expr = CCExpressionCreateList(Allocator);
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.y) });
    
    return Expr;
}

CCExpression CCExpressionCreateVector3i(CCAllocatorType Allocator, CCVector3Di v)
{
    CCExpression Expr = CCExpressionCreateList(Allocator);
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.y) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.z) });
    
    return Expr;
}

CCExpression CCExpressionCreateVector4i(CCAllocatorType Allocator, CCVector4Di v)
{
    CCExpression Expr = CCExpressionCreateList(Allocator);
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.y) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.z) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateInteger(Allocator, v.w) });
    
    return Expr;
}

CCExpression CCExpressionCreateRect(CCAllocatorType Allocator, CCRect r)
{
    CCExpression Expr = CCExpressionCreateList(Allocator);
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, r.position.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, r.position.y) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, r.size.x) });
    CCOrderedCollectionAppendElement(CCExpressionGetList(Expr), &(CCExpression){ CCExpressionCreateFloat(Allocator, r.size.y) });
    
    return Expr;
}

static _Bool CCExpressionGetFloatMinArray(CCExpression Vec, float *Values, float Factor, size_t Min, size_t Max, size_t *Count, const char *ErrMsg)
{
    if ((CCExpressionGetType(Vec) == CCExpressionValueTypeList) && ((*Count = CCCollectionGetCount(CCExpressionGetList(Vec))) >= Min) && (*Count <= Max))
    {
        for (int Loop = 0; Loop < *Count; Loop++)
        {
            CCExpression Value = *(CCExpression*)CCOrderedCollectionGetElementAtIndex(CCExpressionGetList(Vec), Loop);
            
            if (CCExpressionGetType(Value) == CCExpressionValueTypeInteger)
            {
                Values[Loop] = Factor * (float)CCExpressionGetInteger(Value);
            }
            
            else if (CCExpressionGetType(Value) == CCExpressionValueTypeFloat)
            {
                Values[Loop] = CCExpressionGetFloat(Value);
            }
            
            else
            {
                CC_EXPRESSION_EVALUATOR_LOG_ERROR(ErrMsg);
                memset(Values, 0, Max);
                *Count = Max;
                
                return FALSE;
            }
        }
        
        return TRUE;
    }
    
    CC_EXPRESSION_EVALUATOR_LOG_ERROR(ErrMsg);
    memset(Values, 0, Max);
    *Count = Max;
    
    return FALSE;
}

static _Bool CCExpressionGetIntegerMinArray(CCExpression Vec, int32_t *Values, float Factor, size_t Min, size_t Max, size_t *Count, const char *ErrMsg)
{
    if ((CCExpressionGetType(Vec) == CCExpressionValueTypeList) && ((*Count = CCCollectionGetCount(CCExpressionGetList(Vec))) >= Min) && (*Count <= Max))
    {
        for (int Loop = 0; Loop < *Count; Loop++)
        {
            CCExpression Value = *(CCExpression*)CCOrderedCollectionGetElementAtIndex(CCExpressionGetList(Vec), Loop);
            
            if (CCExpressionGetType(Value) == CCExpressionValueTypeInteger)
            {
                Values[Loop] = CCExpressionGetInteger(Value);
            }
            
            else if (CCExpressionGetType(Value) == CCExpressionValueTypeFloat)
            {
                Values[Loop] = (int32_t)(Factor * CCExpressionGetFloat(Value));
            }
            
            else
            {
                CC_EXPRESSION_EVALUATOR_LOG_ERROR(ErrMsg);
                memset(Values, 0, Max);
                *Count = Max;
                
                return FALSE;
            }
        }
        
        return TRUE;
    }
    
    CC_EXPRESSION_EVALUATOR_LOG_ERROR(ErrMsg);
    memset(Values, 0, Max);
    *Count = Max;
    
    return FALSE;
}

static _Bool CCExpressionGetFloatArray(CCExpression Vec, float *Values, size_t Count, const char *ErrMsg)
{
    return CCExpressionGetFloatMinArray(Vec, Values, 1.0f, Count, Count, &Count, ErrMsg);
}

static _Bool CCExpressionGetIntegerArray(CCExpression Vec, int32_t *Values, size_t Count, const char *ErrMsg)
{
    return CCExpressionGetIntegerMinArray(Vec, Values, 1.0f, Count, Count, &Count, ErrMsg);
}

CCVector2D CCExpressionGetVector2(CCExpression Vec)
{
    CCVector2D Result;
    CCExpressionGetFloatArray(Vec, Result.v, 2, "Vector2D should evaluate to a list of 2 numbers. (x:number y:number)");
    
    return Result;
}

CCVector3D CCExpressionGetVector3(CCExpression Vec)
{
    CCVector3D Result;
    CCExpressionGetFloatArray(Vec, Result.v, 3, "Vector3D should evaluate to a list of 3 numbers. (x:number y:number z:number)");
    
    return Result;
}

CCVector4D CCExpressionGetVector4(CCExpression Vec)
{
    CCVector4D Result;
    CCExpressionGetFloatArray(Vec, Result.v, 4, "Vector4D should evaluate to a list of 4 numbers. (x:number y:number z:number w:number)");
    
    return Result;
}

CCVector2Di CCExpressionGetVector2i(CCExpression Vec)
{
    CCVector2Di Result;
    CCExpressionGetIntegerArray(Vec, Result.v, 2, "Vector2Di should evaluate to a list of 2 numbers. (x:number y:number)");
    
    return Result;
}

CCVector3Di CCExpressionGetVector3i(CCExpression Vec)
{
    CCVector3Di Result;
    CCExpressionGetIntegerArray(Vec, Result.v, 3, "Vector3Di should evaluate to a list of 3 numbers. (x:number y:number z:number)");
    
    return Result;
}

CCVector4Di CCExpressionGetVector4i(CCExpression Vec)
{
    CCVector4Di Result;
    CCExpressionGetIntegerArray(Vec, Result.v, 4, "Vector4Di should evaluate to a list of 4 numbers. (x:number y:number z:number w:number)");
    
    return Result;
}

CCRect CCExpressionGetRect(CCExpression Rect)
{
    CCVector4D Result;
    CCExpressionGetFloatArray(Rect, Result.v, 4, "Rect should evaluate to a list of 4 numbers. (x:number y:number width:number height:number)");
    
    return (CCRect){ Result.v[0], Result.v[1], Result.v[2], Result.v[3] };
}

CCColourRGBA CCExpressionGetColour(CCExpression Colour)
{
    size_t Count;
    CCVector4D Result;
    CCExpressionGetFloatMinArray(Colour, Result.v, 0.003921568627f, 3, 4, &Count, "Colour should evaluate to a list of 3 or 4 numbers. (r:number g:number b:number [alpha:number])");
    
    return (CCColourRGBA){ Result.v[0], Result.v[1], Result.v[2], Count == 4 ? Result.v[3] : 1.0f };
}