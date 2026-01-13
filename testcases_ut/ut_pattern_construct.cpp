/**
 * @file ut_pattern.cpp
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include <gtest/gtest.h>
#include "em_token_matcher.h"

/* Test cases ---------------------------------------------------------------------*/
TEST(UT_EmPattern_Construct, First) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_EXACT, &ptnImpl);
    EXPECT_NE(ptn, nullptr);

    ptn = Em_GetFirstPattern("hello", EM_CMP_WITH_PREFIX, &ptnImpl);
    EXPECT_NE(ptn, nullptr);

    char strBuf[16];
    (void)Em_CopyPatternString(ptn, strBuf, sizeof(strBuf));
    EXPECT_STREQ(strBuf, "hello");
}

TEST(UT_EmPattern_Construct, Next) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello world", EM_CMP_EXACT, &ptnImpl);

    Em_PatternImpl nextPtnImpl;
    Em_Pattern nextPtn = Em_GetNextPattern(ptn, &nextPtnImpl);
    EXPECT_NE(nextPtn, nullptr);

    char strBuf[16];
    (void)Em_CopyPatternString(nextPtn, strBuf, sizeof(strBuf));
    EXPECT_STREQ(strBuf, "world");
}

TEST(UT_EmPattern_Construct, Next_WithSameImpl) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello world", EM_CMP_EXACT, &ptnImpl);

    ptn = Em_GetNextPattern(ptn, &ptnImpl);
    EXPECT_NE(ptn, nullptr);

    char strBuf[16];
    (void)Em_CopyPatternString(ptn, strBuf, sizeof(strBuf));
    EXPECT_STREQ(strBuf, "world");
}

TEST(UT_EmPattern_Construct, Next_Self) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello world", EM_CMP_EXACT, &ptnImpl);

    Em_SelfNextPattern(&ptn);
    EXPECT_NE(ptn, nullptr);

    char strBuf[16];
    (void)Em_CopyPatternString(ptn, strBuf, sizeof(strBuf));
    EXPECT_STREQ(strBuf, "world");
}
