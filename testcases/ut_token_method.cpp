/**
 * @file ut_token_method.cpp
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
TEST(UT_EmToken_Method, GetOffset) {
    Em_TokenImpl firstTokenImpl;
    Em_Token firstToken = Em_GetFirstToken("   hello    world", &firstTokenImpl);
    EXPECT_NE(firstToken, nullptr);

    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetNextToken(firstToken, &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    EXPECT_EQ(Em_GetTokenOffset(firstToken), 3);
    EXPECT_EQ(Em_GetTokenOffset(token), 12);
}

TEST(UT_EmToken_Method, GetLength) {
    Em_TokenImpl firstTokenImpl;
    Em_Token firstToken = Em_GetFirstToken("   hello    worlds\n", &firstTokenImpl);
    EXPECT_NE(firstToken, nullptr);

    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetNextToken(firstToken, &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    EXPECT_EQ(Em_GetTokenLength(firstToken), 5);
    EXPECT_EQ(Em_GetTokenLength(token), 6);
}

TEST(UT_EmToken_Method, CopyString) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("12345", &tokenImpl);
    
    char strBuf[6];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_EQ(strBuf[0], '1');
    EXPECT_EQ(strBuf[4], '5');
}

TEST(UT_EmToken_Method, CopyString_BufferTooShort) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("12345", &tokenImpl);
    
    char strBuf[5];
    bool ret = Em_CopyTokenString(NULL, strBuf, sizeof(strBuf));
    EXPECT_FALSE(ret);
}

TEST(UT_EmToken_Method, CopyString_ShouldNotOverWrite) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("12345", &tokenImpl);
    
    char strBuf[8];
    memset(strBuf, 'a', sizeof(strBuf));
    bool ret = Em_CopyTokenString(token, &strBuf[1], sizeof(strBuf) - 2);
    EXPECT_TRUE(ret);
    EXPECT_EQ(strBuf[0], 'a');
    EXPECT_EQ(strBuf[7], 'a');
}
