#include "unity.h"
#include "ApplLinDiagReadDataById.h"
#include "diagnostic_cfg.h"
#include "mock_diagnostic_priv.h"

/* --------------------------------------------------------------------------
 * Test setup and teardown
 * -------------------------------------------------------------------------- */
void setUp(void)
{
    extern uint8_t pbLinDiagBuffer[32];
    extern uint16_t g_linDiagDataLength;
    
    /* Reset global buffers and flags before each test */
    memset(pbLinDiagBuffer, 0, sizeof(pbLinDiagBuffer));
    g_linDiagDataLength = 0;
    ckCurrentNad_called = false;
    checkMsgDataLength_called = false;
    getHandlersForReadDataById_called = false;
}

void tearDown(void)
{
    /* Nothing to clean up after each test */
}

/* --------------------------------------------------------------------------
 * TEST CASE: DID not supported
 * Expectation: Negative response, data length remains 0
 * -------------------------------------------------------------------------- */
void test_ReadDataById_DidNotSupported_ShouldSendNegativeResponse(void)
{
    extern uint8_t pbLinDiagBuffer[32];
    extern uint16_t g_linDiagDataLength;

    /* Configure buffer with unsupported DID */
    pbLinDiagBuffer[1] = 0x12;
    pbLinDiagBuffer[2] = 0x34;
    pbLinDiagBuffer[3] = 0xAA;
    pbLinDiagBuffer[4] = 0xBB;
    pbLinDiagBuffer[5] = 0xCC;

    const uint16_t l_did_cu16 = ((uint16_t)(pbLinDiagBuffer[1] << 8) & 0xFF00) |
                                ((uint16_t)pbLinDiagBuffer[2] & 0x00FF);
    Std_ReturnType l_result_ = E_OK;
    uint8_t l_errCode_u8 = 0;
    uint8_t * const l_diagBuf_pu8 = &pbLinDiagBuffer[3];
    uint8_t l_diagBufSize_u8 = 0;
    Std_ReturnType l_didSupported_ = E_OK;
    uint8 currentNad = 0;

    /* Stub return values */
    checkCurrentNad_return_stub = E_OK;
    checkMsgDataLength_return_stub = E_OK;
    getHandlersForReadDataById_return_stub = E_NOT_OK;

    /* Expect negative response */
    LinDiagSendNegResponse_Expect(l_errCode_u8);

    /* Execute */
    ApplLinDiagReadDataById();

    /* Verify */
    TEST_ASSERT_EQUAL(g_linDiagDataLength , 0);
    TEST_ASSERT_EQUAL(true , ckCurrentNad_called);
    TEST_ASSERT_EQUAL(true , checkMsgDataLength_called);
    TEST_ASSERT_EQUAL(true , getHandlersForReadDataById_called);
}

/* --------------------------------------------------------------------------
 * TEST CASE: DID supported
 * Expectation: Positive response, data length updated
 * -------------------------------------------------------------------------- */
void test_ReadDataById_DidSupported_ShouldSendPositiveResponse(void)
{
    extern uint8_t pbLinDiagBuffer[32];
    extern uint16_t g_linDiagDataLength;

    /* Configure buffer with supported DID (F308) */
    pbLinDiagBuffer[1] = 0xF3;
    pbLinDiagBuffer[2] = 0x08;
    pbLinDiagBuffer[3] = 0xAA;
    pbLinDiagBuffer[4] = 0xBB;
    pbLinDiagBuffer[5] = 0xCC;

    const uint16_t l_did_cu16 = ((uint16_t)(pbLinDiagBuffer[1] << 8) & 0xFF00) |
                                ((uint16_t)pbLinDiagBuffer[2] & 0x00FF);
    Std_ReturnType l_result_ = E_OK;
    uint8_t l_errCode_u8 = 0;
    uint8_t * const l_diagBuf_pu8 = &pbLinDiagBuffer[3];
    uint8_t l_diagBufSize_u8 = 0;
    Std_ReturnType l_didSupported_ = E_OK;
    uint8 currentNad = 0;

    /* Stub return values */
    checkCurrentNad_return_stub = E_OK;
    checkMsgDataLength_return_stub = E_OK;
    getHandlersForReadDataById_return_stub = E_OK;

    /* Expect positive response */
    LinDiagSendPosResponse_Expect();

    /* Execute */
    ApplLinDiagReadDataById();

    /* Verify */
    TEST_ASSERT_EQUAL(g_linDiagDataLength , l_diagBufSize_u8 + 2);
    TEST_ASSERT_EQUAL(true , ckCurrentNad_called);
    TEST_ASSERT_EQUAL(true , checkMsgDataLength_called);
    TEST_ASSERT_EQUAL(true , getHandlersForReadDataById_called);
}

/* --------------------------------------------------------------------------
 * TEST CASE: Incorrect NAD
 * Expectation: Negative response, data length remains 0
 * -------------------------------------------------------------------------- */
void test_ReadDataById_IncorrectNad_ShouldSendNegativeResponse(void)
{
    extern uint8_t pbLinDiagBuffer[32];
    extern uint16_t g_linDiagDataLength;

    /* Configure buffer with DID but incorrect NAD */
    pbLinDiagBuffer[1] = 0xF3;
    pbLinDiagBuffer[2] = 0x00;
    pbLinDiagBuffer[3] = 0xAA;
    pbLinDiagBuffer[4] = 0xBB;
    pbLinDiagBuffer[5] = 0xCC;

    const uint16_t l_did_cu16 = ((uint16_t)(pbLinDiagBuffer[1] << 8) & 0xFF00) |
                                ((uint16_t)pbLinDiagBuffer[2] & 0x00FF);
    Std_ReturnType l_result_ = E_OK;
    uint8_t l_errCode_u8 = 0;
    uint8_t * const l_diagBuf_pu8 = &pbLinDiagBuffer[3];
    uint8_t l_diagBufSize_u8 = 0;
    Std_ReturnType l_didSupported_ = E_OK;
    uint8 currentNad = 0;

    /* Stub return values */
    checkCurrentNad_return_stub = E_NOT_OK;
    checkMsgDataLength_return_stub = E_OK;
    getHandlersForReadDataById_return_stub = E_OK;

    /* Expect negative response */
    LinDiagSendNegResponse_Expect(l_errCode_u8);

    /* Execute */
    ApplLinDiagReadDataById();

    /* Verify */
    TEST_ASSERT_EQUAL(g_linDiagDataLength , 0);
    TEST_ASSERT_EQUAL(true , ckCurrentNad_called);
    TEST_ASSERT_EQUAL(false , checkMsgDataLength_called);
    TEST_ASSERT_EQUAL(false , getHandlersForReadDataById_called);
}

/* --------------------------------------------------------------------------
 * TEST CASE: Incorrect message length
 * Expectation: Negative response, data length remains 0
 * -------------------------------------------------------------------------- */
void test_ReadDataById_IncorrectLength_ShouldSendNegativeResponse(void)
{
    extern uint8_t pbLinDiagBuffer[32];
    extern uint16_t g_linDiagDataLength;

    /* Configure buffer with DID but incorrect length */
    pbLinDiagBuffer[1] = 0xF3;
    pbLinDiagBuffer[2] = 0x00;
    pbLinDiagBuffer[3] = 0xAA;
    pbLinDiagBuffer[4] = 0xBB;
    pbLinDiagBuffer[5] = 0xCC;

    const uint16_t l_did_cu16 = ((uint16_t)(pbLinDiagBuffer[1] << 8) & 0xFF00) |
                                ((uint16_t)pbLinDiagBuffer[2] & 0x00FF);
    Std_ReturnType l_result_ = E_OK;
    uint8_t l_errCode_u8 = 0;
    uint8_t * const l_diagBuf_pu8 = &pbLinDiagBuffer[3];
    uint8_t l_diagBufSize_u8 = 0;
    Std_ReturnType l_didSupported_ = E_OK;
    uint8 currentNad = 0;

    /* Stub return values */
    checkCurrentNad_return_stub = E_OK;
    checkMsgDataLength_return_stub = E_NOT_OK;
    getHandlersForReadDataById_return_stub = E_OK;

    /* Expect negative response */
    LinDiagSendNegResponse_Expect(l_errCode_u8);

    /* Execute */
    ApplLinDiagReadDataById();

    /* Verify */
    TEST_ASSERT_EQUAL(g_linDiagDataLength , 0);
    TEST_ASSERT_EQUAL(true , ckCurrentNad_called);
    TEST_ASSERT_EQUAL(true , checkMsgDataLength_called);
    TEST_ASSERT_EQUAL(false , getHandlersForReadDataById_called);
}
