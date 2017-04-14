//This file is automatically generated, modifications will be lost!
#include "ExpressionSetup.h"
#include "ExpressionEvaluator.h"

#include "GUIExpression.h"
#include "AssetExpressions.h"
#include "BitwiseExpressions.h"
#include "ColourExpressions.h"
#include "ComponentExpressions.h"
#include "ControlFlowExpressions.h"
#include "DebugExpressions.h"
#include "EntityExpressions.h"
#include "EqualityExpressions.h"
#include "GraphicsExpressions.h"
#include "IOExpressions.h"
#include "ListExpressions.h"
#include "MacroExpressions.h"
#include "MathExpressions.h"
#include "StateExpressions.h"
#include "StringExpressions.h"
#include "TextExpressions.h"
#include "TypeCastExpressions.h"
#include "WindowExpressions.h"

void CCExpressionSetup(void)
{
    CCExpressionEvaluatorRegister(CC_STRING("gui"), GUIExpressionRegisterObject);
    CCExpressionEvaluatorRegister(CC_STRING("percent-width"), GUIExpressionPercentWidth);
    CCExpressionEvaluatorRegister(CC_STRING("percent-height"), GUIExpressionPercentHeight);
    CCExpressionEvaluatorRegister(CC_STRING("on"), GUIExpressionOnEvent);
    CCExpressionEvaluatorRegister(CC_STRING("shader"), CCAssetExpressionShader);
    CCExpressionEvaluatorRegister(CC_STRING("texture"), CCAssetExpressionTexture);
    CCExpressionEvaluatorRegister(CC_STRING("font"), CCAssetExpressionFont);
    CCExpressionEvaluatorRegister(CC_STRING("library"), CCAssetExpressionLibrary);
    CCExpressionEvaluatorRegister(CC_STRING("source"), CCAssetExpressionLibrarySource);
    CCExpressionEvaluatorRegister(CC_STRING("asset"), CCAssetExpressionAsset);
    CCExpressionEvaluatorRegister(CC_STRING("not"), CCBitwiseExpressionNot);
    CCExpressionEvaluatorRegister(CC_STRING("and"), CCBitwiseExpressionAnd);
    CCExpressionEvaluatorRegister(CC_STRING("lighten"), CCColourExpressionLighten);
    CCExpressionEvaluatorRegister(CC_STRING("darken"), CCColourExpressionDarken);
    CCExpressionEvaluatorRegister(CC_STRING("component"), CCComponentExpressionComponent);
    CCExpressionEvaluatorRegister(CC_STRING("begin"), CCControlFlowExpressionBegin);
    CCExpressionEvaluatorRegister(CC_STRING("if"), CCControlFlowExpressionBranch);
    CCExpressionEvaluatorRegister(CC_STRING("loop"), CCControlFlowExpressionLoop);
    CCExpressionEvaluatorRegister(CC_STRING("repeat"), CCControlFlowExpressionRepeat);
    CCExpressionEvaluatorRegister(CC_STRING("inspect"), CCDebugExpressionInspect);
    CCExpressionEvaluatorRegister(CC_STRING("break"), CCDebugExpressionBreak);
    CCExpressionEvaluatorRegister(CC_STRING("entity"), CCEntityExpressionEntity);
    CCExpressionEvaluatorRegister(CC_STRING("="), CCEqualityExpressionEqual);
    CCExpressionEvaluatorRegister(CC_STRING("!="), CCEqualityExpressionNotEqual);
    CCExpressionEvaluatorRegister(CC_STRING("<="), CCEqualityExpressionLessThanEqual);
    CCExpressionEvaluatorRegister(CC_STRING(">="), CCEqualityExpressionGreaterThanEqual);
    CCExpressionEvaluatorRegister(CC_STRING("<"), CCEqualityExpressionLessThan);
    CCExpressionEvaluatorRegister(CC_STRING(">"), CCEqualityExpressionGreaterThan);
    CCExpressionEvaluatorRegister(CC_STRING("render-rect"), CCGraphicsExpressionRenderRect);
    CCExpressionEvaluatorRegister(CC_STRING("render-text"), CCGraphicsExpressionRenderText);
    CCExpressionEvaluatorRegister(CC_STRING("print"), CCIOExpressionPrint);
    CCExpressionEvaluatorRegister(CC_STRING("search"), CCIOExpressionSearch);
    CCExpressionEvaluatorRegister(CC_STRING("eval"), CCIOExpressionEval);
    CCExpressionEvaluatorRegister(CC_STRING("get"), CCListExpressionGetter);
    CCExpressionEvaluatorRegister(CC_STRING("flatten"), CCListExpressionFlatten);
    CCExpressionEvaluatorRegister(CC_STRING("parts"), CCListExpressionParts);
    CCExpressionEvaluatorRegister(CC_STRING("split"), CCListExpressionSplit);
    CCExpressionEvaluatorRegister(CC_STRING("count"), CCListExpressionCount);
    CCExpressionEvaluatorRegister(CC_STRING("quote"), CCMacroExpressionQuote);
    CCExpressionEvaluatorRegister(CC_STRING("unquote"), CCMacroExpressionUnquote);
    CCExpressionEvaluatorRegister(CC_STRING("+"), CCMathExpressionAddition);
    CCExpressionEvaluatorRegister(CC_STRING("-"), CCMathExpressionSubtract);
    CCExpressionEvaluatorRegister(CC_STRING("*"), CCMathExpressionMultiply);
    CCExpressionEvaluatorRegister(CC_STRING("/"), CCMathExpressionDivide);
    CCExpressionEvaluatorRegister(CC_STRING("min"), CCMathExpressionMinimum);
    CCExpressionEvaluatorRegister(CC_STRING("max"), CCMathExpressionMaximum);
    CCExpressionEvaluatorRegister(CC_STRING("random"), CCMathExpressionRandom);
    CCExpressionEvaluatorRegister(CC_STRING("round"), CCMathExpressionRound);
    CCExpressionEvaluatorRegister(CC_STRING("state!"), CCStateExpressionCreateState);
    CCExpressionEvaluatorRegister(CC_STRING("namespace!"), CCStateExpressionCreateNamespace);
    CCExpressionEvaluatorRegister(CC_STRING("enum!"), CCStateExpressionCreateEnum);
    CCExpressionEvaluatorRegister(CC_STRING("super"), CCStateExpressionSuper);
    CCExpressionEvaluatorRegister(CC_STRING("strict-super"), CCStateExpressionStrictSuper);
    CCExpressionEvaluatorRegister(CC_STRING("prefix"), CCStringExpressionPrefix);
    CCExpressionEvaluatorRegister(CC_STRING("suffix"), CCStringExpressionSuffix);
    CCExpressionEvaluatorRegister(CC_STRING("filename"), CCStringExpressionFilename);
    CCExpressionEvaluatorRegister(CC_STRING("replace"), CCStringExpressionReplace);
    CCExpressionEvaluatorRegister(CC_STRING("cat"), CCStringExpressionConcatenate);
    CCExpressionEvaluatorRegister(CC_STRING("length"), CCStringExpressionLength);
    CCExpressionEvaluatorRegister(CC_STRING("insert"), CCStringExpressionInsert);
    CCExpressionEvaluatorRegister(CC_STRING("remove"), CCStringExpressionRemove);
    CCExpressionEvaluatorRegister(CC_STRING("chop"), CCStringExpressionChop);
    CCExpressionEvaluatorRegister(CC_STRING("format"), CCStringExpressionFormat);
    CCExpressionEvaluatorRegister(CC_STRING("text-visible-length"), CCTextExpressionGetVisibleLength);
    CCExpressionEvaluatorRegister(CC_STRING("text-cursor-position"), CCTextExpressionGetCursorPosition);
    CCExpressionEvaluatorRegister(CC_STRING("integer->float"), CCTypeCastExpressionIntegerToFloat);
    CCExpressionEvaluatorRegister(CC_STRING("float->integer"), CCTypeCastExpressionFloatToInteger);
    CCExpressionEvaluatorRegister(CC_STRING("window-percent-width"), CCWindowExpressionPercentageWidth);
    CCExpressionEvaluatorRegister(CC_STRING("window-percent-height"), CCWindowExpressionPercentageHeight);
    CCExpressionEvaluatorRegister(CC_STRING("window-width"), CCWindowExpressionWidth);
    CCExpressionEvaluatorRegister(CC_STRING("window-height"), CCWindowExpressionHeight);
    CCExpressionEvaluatorRegister(CC_STRING("frame-changed?"), CCWindowExpressionFrameChanged);
}
