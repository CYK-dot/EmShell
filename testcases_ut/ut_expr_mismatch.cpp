/**
 * @file ut_expr_mismatch.cpp
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include <gtest/gtest.h>
#include "em_expr.h"

/* Config macros ------------------------------------------------------------------*/

/* Mock variables and functions  --------------------------------------------------*/

/* Test suites --------------------------------------------------------------------*/

/* Test cases ---------------------------------------------------------------------*/
TEST(UT_EmExprMisMatch, NoSpecify_InvalidInput) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "setup uart on\n";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(NULL, cmdExpr, EM_CMP_EXACT, NULL, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_WRONG_INPUT);
}

TEST(UT_EmExprMisMatch, NoSpecify_WrongInput) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "setup uart on\n";
    const char *invalidInput = "  \n";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, invalidInput, EM_CMP_WITH_PREFIX, NULL, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_WRONG_INPUT);
    EXPECT_EQ(wrongOffset, 0);

    result = Em_TryMatchExpr(invalidInput, cmdExpr, EM_CMP_WITH_PREFIX, NULL, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_WRONG_INPUT);
    EXPECT_EQ(wrongOffset, 0);
}

TEST(UT_EmExprMisMatch, NoSpecify_KeyMismatchButIgnore) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "setup uzrt\n";
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, nullptr, nullptr);
    EXPECT_EQ(result, EM_EXPR_TOKEN_MISMATCH);
}

TEST(UT_EmExprMisMatch, Exact_TokenWrong) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "   satup    uart\n";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, NULL, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_TOKEN_MISMATCH);
    EXPECT_EQ(wrongOffset, 4);
}

TEST(UT_EmExprMisMatch, Exact_TokenFew) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "   setup";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, NULL, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_TOKEN_TOO_FEW);
    EXPECT_EQ(wrongOffset, 8);
}

TEST(UT_EmExprMisMatch, Exact_TokenMany) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "setup uart on\n";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, NULL, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_TOKEN_TOO_MANY);
    EXPECT_EQ(wrongOffset, 11);
}