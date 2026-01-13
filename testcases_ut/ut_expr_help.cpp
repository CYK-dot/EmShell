/**
 * @file ut_expr_help.cpp
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
TEST(UT_EmExprHelp, Exact_HelpLastKey) {
    const char *ptnExpr = "  setup uart";
    const char *cmdExpr = "set";

    uint16_t helpPtnOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, nullptr);
    EXPECT_EQ(result, EM_EXPR_HELP_LAST_TOKEN);
    EXPECT_EQ(helpPtnOffset, 2);
}

TEST(UT_EmExprHelp, Exact_HelpNextKey) {
    const char *ptnExpr = "   setup uart";
    const char *cmdExpr = "setup";

    uint16_t helpPtnOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, nullptr);
    EXPECT_EQ(result, EM_EXPR_HELP_NEXT_TOKEN);
    EXPECT_EQ(helpPtnOffset, 9);
}

TEST(UT_EmExprHelp, Exact_HelpNextParam) {
    const char *ptnExpr = "setup   $device on";
    const char *cmdExpr = "setup\n \r";

    uint16_t helpPtnOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, nullptr);
    EXPECT_EQ(result, EM_EXPR_HELP_NEXT_TOKEN);
    EXPECT_EQ(helpPtnOffset, 8);
}

TEST(UT_EmExprHelpFail, Exact_CorrectLastKey) {
    const char *ptnExpr = "  setup uart";
    const char *cmdExpr = " sat   ";

    uint16_t helpPtnOffset = 0;
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &helpPtnOffset, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_HELP_LAST_TOKEN);
    EXPECT_EQ(wrongOffset, 2);
}

TEST(UT_EmExprHelp, Prefix_HelpNextKey) {
    const char *ptnExpr = "  setup uart";
    const char *cmdExpr = "set";

    uint16_t helpPtnOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, &helpPtnOffset, nullptr);
    EXPECT_EQ(result, EM_EXPR_HELP_NEXT_TOKEN);
    EXPECT_EQ(helpPtnOffset, 8);
}

TEST(UT_EmExprHelpFail, Prefix_CorrectLastKey) {
    const char *ptnExpr = "  setup uart";
    const char *cmdExpr = " sat   ";

    uint16_t helpPtnOffset = 0;
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryHelpExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, &helpPtnOffset, &wrongOffset);
    EXPECT_EQ(result, EM_EXPR_HELP_LAST_TOKEN);
    EXPECT_EQ(wrongOffset, 2);
}