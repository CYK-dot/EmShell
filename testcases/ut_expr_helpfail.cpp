/**
 * @file ut_expr_helpfail.cpp
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

/* Test cases ---------------------------------------------------------------------*/
TEST(UT_EmExprHelpFail, NoSpecify_InputInvalid) {
    const char *ptnExpr = "  setup uart";
    const char *cmdExpr = "setup uart on\n";

    uint16_t helpPtnOffset = 0;
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(nullptr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_WRONG_INPUT);

    result = Em_TryHelpExpr(ptnExpr, "   \n\r", EM_CMP_EXACT, &helpPtnOffset, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_WRONG_INPUT);
}

TEST(UT_EmExprHelpFail, Exact_NothingToHelp) {
    const char *ptnExpr = "  setup uart";
    const char *cmdExpr = " setup  uart   \n";

    uint16_t helpPtnOffset = 0;
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_MATCH);
}

TEST(UT_EmExprHelpFail, Exact_KeyMismatch) {
    const char *ptnExpr = "  setup uart on";
    const char *cmdExpr = " setup  uzrt   on\n";

    uint16_t helpPtnOffset = 0;
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_TOKEN_MISMATCH);
    EXPECT_EQ(wrongOffset, 9);
}

TEST(UT_EmExprHelpFail, Exact_TokenTooMany) {
    const char *ptnExpr = "  setup uart";
    const char *cmdExpr = "setup uart on\n";

    uint16_t helpPtnOffset = 0;
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_TOKEN_TOO_MANY);
    EXPECT_EQ(wrongOffset, 11);
}