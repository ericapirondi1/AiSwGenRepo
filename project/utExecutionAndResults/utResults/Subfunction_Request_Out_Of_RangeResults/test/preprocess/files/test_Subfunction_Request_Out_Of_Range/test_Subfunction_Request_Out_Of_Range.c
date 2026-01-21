// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/Subfunction_Request_Out_Of_Range.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void)
{ }

void tearDown(void)
{ }

void test_Subfunction_Request_Out_Of_Range_WithNullErrCode(void)
{
  uint8 output = 0xFF;
  uint8 size = 0x10;
  Std_ReturnType result;

  result = Subfunction_Request_Out_Of_Range(&output, &size,
                                                           ((void *)0)
                                                               );

  UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);
}

void test_Subfunction_Request_Out_Of_Range_WithValidErrCode(void)
{
  uint8 output = 0xFF;
  uint8 size = 0x10;
  uint8 errCode = 0x00;
  Std_ReturnType result;

  result = Subfunction_Request_Out_Of_Range(&output, &size, &errCode);

  UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((UNITY_INT)((0x12)), (UNITY_INT)((errCode)), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_INT);
}

void test_Subfunction_Request_Out_Of_Range_WithNullOutput(void)
{
  uint8 size = 0x10;
  uint8 errCode = 0x00;
  Std_ReturnType result;

  result = Subfunction_Request_Out_Of_Range(
                                           ((void *)0)
                                               , &size, &errCode);

  UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((UNITY_INT)((0x12)), (UNITY_INT)((errCode)), (
 ((void *)0)
 ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_INT);
}

void test_Subfunction_Request_Out_Of_Range_WithNullSize(void)
{
  uint8 output = 0xFF;
  uint8 errCode = 0x00;
  Std_ReturnType result;

  result = Subfunction_Request_Out_Of_Range(&output,
                                                    ((void *)0)
                                                        , &errCode);

  UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((UNITY_INT)((0x12)), (UNITY_INT)((errCode)), (
 ((void *)0)
 ), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_INT);
}

void test_Subfunction_Request_Out_Of_Range_WithAllValidPointers(void)
{
  uint8 output = 0x00;
  uint8 size = 0x05;
  uint8 errCode = 0xFF;
  Std_ReturnType result;

  result = Subfunction_Request_Out_Of_Range(&output, &size, &errCode);

  UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(84), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((UNITY_INT)((0x12)), (UNITY_INT)((errCode)), (
 ((void *)0)
 ), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_INT);
}

void test_Subfunction_Request_Out_Of_Range_OutputAndSizeUnchanged(void)
{
  uint8 output = 0xAA;
  uint8 size = 0xBB;
  uint8 errCode = 0x00;
  Std_ReturnType result;

  result = Subfunction_Request_Out_Of_Range(&output, &size, &errCode);

  UnityAssertEqualNumber((UNITY_INT)((((Std_ReturnType)0x01u))), (UNITY_INT)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((UNITY_INT)((0xAA)), (UNITY_INT)((output)), (
 ((void *)0)
 ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((UNITY_INT)((0xBB)), (UNITY_INT)((size)), (
 ((void *)0)
 ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_INT);
  UnityAssertEqualNumber((UNITY_INT)((0x12)), (UNITY_INT)((errCode)), (
 ((void *)0)
 ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_INT);
}