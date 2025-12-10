// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/checkMsgDataLength.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_checkMsgDataLength_ValidMinimumBoundary(void)
{
    Std_ReturnType result;

    checkMsgDataLength(1u, &result);

    UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x00u))), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);
}

void test_checkMsgDataLength_ValidMaximumBoundary(void)
{
    Std_ReturnType result;

    checkMsgDataLength(32u, &result);

    UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x00u))), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);
}

void test_checkMsgDataLength_ValidMiddleValue(void)
{
    Std_ReturnType result;

    checkMsgDataLength(16u, &result);

    UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x00u))), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT);
}

void test_checkMsgDataLength_InvalidZero(void)
{
    Std_ReturnType result;

    checkMsgDataLength(0u, &result);

    UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);
}

void test_checkMsgDataLength_InvalidAboveMaximum(void)
{
    Std_ReturnType result;

    checkMsgDataLength(33u, &result);

    UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);
}

void test_checkMsgDataLength_InvalidLargeValue(void)
{
    Std_ReturnType result;

    checkMsgDataLength(1000u, &result);

    UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);
}

void test_checkMsgDataLength_InvalidMaxUint16(void)
{
    Std_ReturnType result;

    checkMsgDataLength(0xFFFFu, &result);

    UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_INT);
}