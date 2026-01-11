/**
 * @file ut_token_pattern.cpp
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
TEST(UT_EmToken_Construct, FirstToken) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("hello world", &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    char strBuf[16];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_STREQ(strBuf, "hello");
}

TEST(UT_EmToken_Construct, FirstToken_WithUnreadableAscii) {
    Em_TokenImpl tokenImpl;
    char str[] = {'a', 'b', 'c', '\x7F', 'd', 'e', 'f', '\0'};
    Em_Token token = Em_GetFirstToken(str, &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    char strBuf[16];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_STREQ(strBuf, "abc");
}

TEST(UT_EmToken_Construct, FirstToken_WithSpace) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("    hello  ", &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    char strBuf[16];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_STREQ(strBuf, "hello");
}

TEST(UT_EmToken_Construct, FirstToken_WithNoToken) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("  ", &tokenImpl);
    EXPECT_EQ(token, nullptr);
    
    token = Em_GetFirstToken("", &tokenImpl);
    EXPECT_EQ(token, nullptr);
}

TEST(UT_EmToken_Construct, FirstToken_InvalidInput) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken(nullptr, &tokenImpl);
    EXPECT_EQ(token, nullptr);

    token = Em_GetFirstToken("hello", nullptr);
    EXPECT_EQ(token, nullptr);
}

TEST(UT_EmToken_Construct, NextToken) {
    Em_TokenImpl firstTokenImpl;
    Em_TokenImpl tokenImpl;
    Em_Token firstToken = Em_GetFirstToken("hello world", &firstTokenImpl);
    EXPECT_NE(firstToken, nullptr);
    Em_Token token = Em_GetNextToken(firstToken, &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    char strBuf[16];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_STREQ(strBuf, "world");
}

TEST(UT_EmToken_Construct, NextToken_WithSameImpl) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("hello world", &tokenImpl);
    EXPECT_NE(token, nullptr);
    token = Em_GetNextToken(token, &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    char strBuf[16];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_STREQ(strBuf, "world");
}

TEST(UT_EmToken_Construct, NextToken_Self) {
    Em_TokenImpl tokenImpl;
    Em_Token token = Em_GetFirstToken("hello world", &tokenImpl);
    EXPECT_NE(token, nullptr);
    Em_SelfNextToken(&token);
    EXPECT_NE(token, nullptr);
    
    char strBuf[16];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_STREQ(strBuf, "world");
}

TEST(UT_EmToken_Construct, NextToken_WithSpace) {
    Em_TokenImpl firstTokenImpl;
    Em_TokenImpl tokenImpl;
    Em_Token firstToken = Em_GetFirstToken("  hello    world\n", &firstTokenImpl);
    EXPECT_NE(firstToken, nullptr);
    Em_Token token = Em_GetNextToken(firstToken, &tokenImpl);
    EXPECT_NE(token, nullptr);
    
    char strBuf[16];
    bool ret = Em_CopyTokenString(token, strBuf, sizeof(strBuf));
    EXPECT_TRUE(ret);
    EXPECT_STREQ(strBuf, "world");
}

TEST(UT_EmToken_Construct, NextToken_WithNoToken) {
    Em_TokenImpl firstTokenImpl;
    Em_TokenImpl tokenImpl;
    Em_Token firstToken = Em_GetFirstToken("  hello  \n", &firstTokenImpl);
    EXPECT_NE(firstToken, nullptr);
    Em_Token token = Em_GetNextToken(firstToken, &tokenImpl);
    EXPECT_EQ(token, nullptr);

    firstToken = Em_GetFirstToken("world", &firstTokenImpl);
    EXPECT_NE(firstToken, nullptr);
    token = Em_GetNextToken(firstToken, &tokenImpl);
    EXPECT_EQ(token, nullptr);
}

TEST(UT_EmToken_Construct, NextToken_InvalidInput) {
    Em_TokenImpl firstTokenImpl;
    Em_Token firstToken = Em_GetFirstToken("hello", &firstTokenImpl);
    EXPECT_NE(firstToken, nullptr);

    Em_TokenImpl tokenImpl;
    bool ret = Em_GetNextToken(nullptr, &tokenImpl);
    EXPECT_FALSE(ret);

    ret = Em_GetNextToken(firstToken, nullptr);
    EXPECT_FALSE(ret);
}
