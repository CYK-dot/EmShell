/**
 * @file ut_pattern_method.cpp
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

/* Config macros ------------------------------------------------------------------*/

/* Mock variables and functions  --------------------------------------------------*/

/* Test suites --------------------------------------------------------------------*/

/* Test cases ---------------------------------------------------------------------*/

TEST(UT_EmPattern_Method, GetPatterType) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_EXACT, &ptnImpl);
    Em_PatternType ptnType = Em_GetPatternType(ptn);
    EXPECT_EQ(ptnType, EM_PATTERN_KEY);

    ptn = Em_GetFirstPattern("$", EM_CMP_WITH_PREFIX, &ptnImpl);
    ptnType = Em_GetPatternType(ptn);
    EXPECT_EQ(ptnType, EM_PATTERN_PARAMETER);

    ptn = Em_GetFirstPattern("$number", EM_CMP_EXACT, &ptnImpl);
    ptnType = Em_GetPatternType(ptn);
    EXPECT_EQ(ptnType, EM_PATTERN_PARAMETER);
}

TEST(UT_EmPattern_Method, GetLength) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("   hello   ", EM_CMP_EXACT, &ptnImpl);
    EXPECT_EQ(Em_GetPatternLength(ptn), 5);
    
    ptn = Em_GetFirstPattern("   $\n", EM_CMP_WITH_PREFIX, &ptnImpl);
    EXPECT_EQ(Em_GetPatternLength(ptn), 1);
    
    ptn = Em_GetFirstPattern("$number   ", EM_CMP_EXACT, &ptnImpl);
    EXPECT_EQ(Em_GetPatternLength(ptn), 7);
}

TEST(UT_EmPattern_Method, GetOffset) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("   hello   ", EM_CMP_EXACT, &ptnImpl);
    EXPECT_EQ(Em_GetPatternOffset(ptn), 3);
    
    ptn = Em_GetFirstPattern("   $number\n setup", EM_CMP_WITH_PREFIX, &ptnImpl);
    Em_SelfNextPattern(&ptn);
    EXPECT_EQ(Em_GetPatternOffset(ptn), 12);
}

TEST(UT_EmPattern_Method, MatchToken_Exact) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_EXACT, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("    hello\n", &matchTokenImpl);

    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, nullptr);
    EXPECT_TRUE(ret);
}

TEST(UT_EmPattern_Method, MatchToken_ExactMiss) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_EXACT, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("hallo\n", &matchTokenImpl);

    uint16_t wrongIndex = 0;
    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, &wrongIndex);
    EXPECT_FALSE(ret);
    EXPECT_EQ(wrongIndex, 1);
}

TEST(UT_EmPattern_Method, MatchToken_ExactMiss_NoSpecifyIndex) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_EXACT, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("hallo\n", &matchTokenImpl);

    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, nullptr);
    EXPECT_FALSE(ret);
}

TEST(UT_EmPattern_Method, MatchToken_ExactMiss_WithPrefix) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("he", EM_CMP_EXACT, &ptnImpl);
    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("hello", &matchTokenImpl);

    uint16_t wrongIndex = 0;
    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, &wrongIndex);
    EXPECT_FALSE(ret);
    EXPECT_EQ(wrongIndex, 2);

    matchToken = Em_GetFirstToken("h", &matchTokenImpl);
    ret = Em_TryMatchPatternToToken(ptn, matchToken, &wrongIndex);
    EXPECT_FALSE(ret);
    EXPECT_EQ(wrongIndex, 1);
}

TEST(UT_EmPattern_Method, MatchToken_ExactMiss_WithSpace) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_EXACT, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("   hallo\n", &matchTokenImpl);

    uint16_t wrongIndex = 0;
    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, &wrongIndex);
    EXPECT_FALSE(ret);
    EXPECT_EQ(wrongIndex, 4);
}

TEST(UT_EmPattern_Method, MatchToken_ExactMiss_WithNextToken) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("world", EM_CMP_EXACT, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("   hallo\n World", &matchTokenImpl);
    Em_TokenImpl secondTokenImpl;
    Em_Token secondToken = Em_GetNextToken(matchToken, &secondTokenImpl);

    uint16_t wrongIndex = 0;
    bool ret = Em_TryMatchPatternToToken(ptn, secondToken, &wrongIndex);
    EXPECT_FALSE(ret);
    EXPECT_EQ(wrongIndex, 10);
}

TEST(UT_EmPattern_Method, MatchToken_Prefix) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_WITH_PREFIX, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("    he\n", &matchTokenImpl);

    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, nullptr);
    EXPECT_TRUE(ret);
}

TEST(UT_EmPattern_Method, MatchToken_PrefixMiss) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hello", EM_CMP_WITH_PREFIX, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("hallo\n", &matchTokenImpl);

    uint16_t wrongIndex = 0;
    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, &wrongIndex);
    EXPECT_FALSE(ret);
    EXPECT_EQ(wrongIndex, 1);
}

TEST(UT_EmPattern_Method, MatchToken_PrefixMiss_WithLongToken) {
    Em_PatternImpl ptnImpl;
    Em_Pattern ptn = Em_GetFirstPattern("hell", EM_CMP_WITH_PREFIX, &ptnImpl);

    Em_TokenImpl matchTokenImpl;
    Em_Token matchToken = Em_GetFirstToken("hello", &matchTokenImpl);

    uint16_t wrongIndex = 0;
    bool ret = Em_TryMatchPatternToToken(ptn, matchToken, &wrongIndex);
    EXPECT_FALSE(ret);
    EXPECT_EQ(wrongIndex, 4);
}
