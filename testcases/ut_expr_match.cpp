/**
 * @file ut_expr_match.cpp
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
TEST(UT_EmExprMatch, NoSpecify_ParamMatchButIgnore) {
    const char *ptnExpr = "setup $device";
    const char *cmdExpr = "setup uart\n";
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, nullptr, nullptr);
    EXPECT_EQ(result, EM_EXPR_MATCH);
}

TEST(UT_EmExprMatch, Exact_MultiKey) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "   setup    uart\n";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, NULL, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
}

TEST(UT_EmExprMatch, Exact_MultiParam) {
    const char *ptnExpr = "$action $";
    const char *cmdExpr = "  setup   uart\n\r";
    uint16_t paramStore[2] = { 0 };
    Em_Parameter param = { .index = paramStore, .maxCnt = 2, .curCnt = 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &param, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
    EXPECT_EQ(paramStore[0], 2);
    EXPECT_EQ(paramStore[1], 10);
}

TEST(UT_EmExprMatch, Exact_KeyMixParam) {
    const char *ptnExpr = "$action uart $number";
    const char *cmdExpr = "  setup   uart 1\n\r";
    uint16_t paramStore[2] = { 0 };
    Em_Parameter param = { .index = paramStore, .maxCnt = 2, .curCnt = 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_EXACT, &param, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
    EXPECT_EQ(paramStore[0], 2);
    EXPECT_EQ(paramStore[1], 15);
}

TEST(UT_EmExprMatch, PrefixButExact_MultiKey) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "   setup    uart\n";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, NULL, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
}

TEST(UT_EmExprMatch, PrefixButExact_MultiParam) {
    const char *ptnExpr = "$action $";
    const char *cmdExpr = "  setup   uart\n\r";
    uint16_t paramStore[2] = { 0 };
    Em_Parameter param = { .index = paramStore, .maxCnt = 2, .curCnt = 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, &param, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
    EXPECT_EQ(paramStore[0], 2);
    EXPECT_EQ(paramStore[1], 10);
}

TEST(UT_EmExprMatch, PrefixButExact_KeyMixParam) {
    const char *ptnExpr = "$action uart $number";
    const char *cmdExpr = "  setup   uart 1\n\r";
    uint16_t paramStore[2] = { 0 };
    Em_Parameter param = { .index = paramStore, .maxCnt = 2, .curCnt = 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, &param, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
    EXPECT_EQ(paramStore[0], 2);
    EXPECT_EQ(paramStore[1], 15);
}

TEST(UT_EmExprMatch, Prefix_MultiKey) {
    const char *ptnExpr = "setup uart";
    const char *cmdExpr = "   s    uart\n";
    Em_Parameter param = { 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, NULL, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
}

TEST(UT_EmExprMatch, Prefix_KeyMixParam) {
    const char *ptnExpr = "$action uart $number";
    const char *cmdExpr = "  s   u 1\n\r";
    uint16_t paramStore[2] = { 0 };
    Em_Parameter param = { .index = paramStore, .maxCnt = 2, .curCnt = 0 };
    uint16_t wrongOffset = 0;
    Em_ExprResult result = Em_TryMatchExpr(ptnExpr, cmdExpr, EM_CMP_WITH_PREFIX, &param, NULL);
    EXPECT_EQ(result, EM_EXPR_MATCH);
    EXPECT_EQ(paramStore[0], 2);
    EXPECT_EQ(paramStore[1], 8);
}