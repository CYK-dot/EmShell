/**
 * @file ut_rchain.cpp
 * @author CYK-Dot
 * @brief Unit tests for responsibility chain module
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include <gtest/gtest.h>
#include "em_resp_chain.h"

/* Test suites --------------------------------------------------------------------*/
typedef struct tagTestRequest {
    uint8_t numA;
    uint8_t numB;
} TestRequest;

typedef struct tagTestResponse {
    uint8_t minus;
    uint8_t plus;
} TestResponse;

static bool TestHandlerPlus(uint8_t mngId, const void *request, void *response)
{
    TestRequest *req = (TestRequest *)request;
    if (req->numA >= (UINT8_MAX - req->numB)) {
        return false;
    }
    TestResponse *resp = (TestResponse *)response;
    resp->minus = 0;
    resp->plus = req->numA + req->numB;
    return true;
}
static char TestHandleIdPlus[] = "TestHandlerPlus";

static bool TestHandlerMinus(uint8_t mngId, const void *request, void *response)
{
    TestRequest *req = (TestRequest *)request;
    if (req->numA < req->numB) {
        return false;
    }
    TestResponse *resp = (TestResponse *)response;
    resp->minus = req->numA - req->numB;
    resp->plus = 0;
    return true;
}
static char TestHandleIdMinus[] = "TestHandlerMinus";

const RChain_Desc TestRChainDesc = {
    .handleList = (RChain_Handler[]) {
        {.id = TestHandleIdPlus, .handler = TestHandlerPlus},
        {.id = TestHandleIdMinus, .handler = TestHandlerMinus},
    },
    .count = 2,
    .mngId = 0,
};

/* Test cases ---------------------------------------------------------------------*/
TEST(RChain, MatchFirstHandler) {
    TestRequest req = {.numA = 10, .numB = 5};
    TestResponse resp = {0};
    RChain_Mng mng = RChain_CreateStatic(&TestRChainDesc);
    EXPECT_EQ(RChain_Process(mng, &req, &resp), TestHandleIdPlus);
    EXPECT_EQ(resp.minus, 0);
    EXPECT_EQ(resp.plus, 15);
}

TEST(RChain, MatchSecondHandler) {
    TestRequest req = {.numA = 200, .numB = 70};
    TestResponse resp = {0};
    RChain_Mng mng = RChain_CreateStatic(&TestRChainDesc);
    EXPECT_EQ(RChain_Process(mng, &req, &resp), TestHandleIdMinus);
    EXPECT_EQ(resp.minus, 130);
    EXPECT_EQ(resp.plus, 0);
}

TEST(RChain, NotMatch) {
    TestRequest req = {.numA = 200, .numB = 219};
    TestResponse resp = {0};
    RChain_Mng mng = RChain_CreateStatic(&TestRChainDesc);
    EXPECT_EQ(RChain_Process(mng, &req, &resp), nullptr);
    EXPECT_EQ(resp.minus, 0);
    EXPECT_EQ(resp.plus, 0);
}

TEST(RChain, InvalidInput) {
    TestRequest req = {.numA = 200, .numB = 219};
    TestResponse resp = {0};
    RChain_Mng mng = RChain_CreateStatic(&TestRChainDesc);

    EXPECT_EQ(RChain_Process(mng, nullptr, &resp), nullptr);
    EXPECT_EQ(resp.minus, 0);
    EXPECT_EQ(resp.plus, 0);

    EXPECT_EQ(RChain_Process(mng, &req, nullptr), nullptr);
    EXPECT_EQ(resp.minus, 0);
    EXPECT_EQ(resp.plus, 0);

    EXPECT_EQ(RChain_Process(nullptr, &req, &resp), nullptr);
    EXPECT_EQ(resp.minus, 0);
    EXPECT_EQ(resp.plus, 0);
}