// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/EDD_Crc8ComputeInternal.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_EDD_Crc8ComputeInternal_EmptyData(void)
{
    uint8_t data[] = {};
    uint8_t expected = (0x00u);

    uint8_t result = EDD_Crc8ComputeInternal(data, 0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((expected)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_SingleByte(void)
{
    uint8_t data[] = {0x00};

    uint8_t expected = 0x00;

    uint8_t result = EDD_Crc8ComputeInternal(data, 1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((expected)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_SingleByteNonZero(void)
{
    uint8_t data[] = {0x01};

    uint8_t expected = 0x07;

    uint8_t result = EDD_Crc8ComputeInternal(data, 1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((expected)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_TwoBytes(void)
{
    uint8_t data[] = {0x00, 0x00};

    uint8_t expected = 0x00;

    uint8_t result = EDD_Crc8ComputeInternal(data, 2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((expected)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_AllZeros(void)
{
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    uint8_t expected = 0x00;

    uint8_t result = EDD_Crc8ComputeInternal(data, 4);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((expected)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_AlternatingPattern(void)
{
    uint8_t data[] = {0xAA, 0x55, 0xAA, 0x55};

    uint8_t result = EDD_Crc8ComputeInternal(data, 4);

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((result)), UNITY_SMALLER_OR_EQUAL, (
   ((void *)0)
   ), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_LongData(void)
{
    uint8_t data[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };

    uint8_t result = EDD_Crc8ComputeInternal(data, 32);

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((result)), UNITY_SMALLER_OR_EQUAL, (
   ((void *)0)
   ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_ReturnValueRange(void)
{
    uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};

    uint8_t result = EDD_Crc8ComputeInternal(data, 4);

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((result)), UNITY_SMALLER_OR_EQUAL, (
   ((void *)0)
   ), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_UINT8);
    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), UNITY_GREATER_OR_EQUAL, (
   ((void *)0)
   ), (UNITY_UINT)(147), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_Consistency(void)
{
    uint8_t data[] = {0x12, 0x34, 0x56, 0x78};

    uint8_t result1 = EDD_Crc8ComputeInternal(data, 4);
    uint8_t result2 = EDD_Crc8ComputeInternal(data, 4);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((result1)), (UNITY_INT)(UNITY_UINT8 )((result2)), (
   ((void *)0)
   ), (UNITY_UINT)(161), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_DifferentLengths(void)
{
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};

    uint8_t result_len1 = EDD_Crc8ComputeInternal(data, 1);
    uint8_t result_len2 = EDD_Crc8ComputeInternal(data, 2);
    uint8_t result_len4 = EDD_Crc8ComputeInternal(data, 4);

    do { if (((result_len1) != (result_len2)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((177))); } } while (0);
    do { if (((result_len2) != (result_len4)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((178))); } } while (0);
}

void test_EDD_Crc8ComputeInternal_BoundaryValue(void)
{
    uint8_t data[] = {0x80};

    uint8_t result = EDD_Crc8ComputeInternal(data, 1);

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((result)), UNITY_SMALLER_OR_EQUAL, (
   ((void *)0)
   ), (UNITY_UINT)(192), UNITY_DISPLAY_STYLE_UINT8);
}

void test_EDD_Crc8ComputeInternal_PotentialOverflowValues(void)
{
    uint8_t data[] = {0xFF, 0xFE, 0xFD};

    uint8_t result = EDD_Crc8ComputeInternal(data, 3);

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((result)), UNITY_SMALLER_OR_EQUAL, (
   ((void *)0)
   ), (UNITY_UINT)(206), UNITY_DISPLAY_STYLE_UINT8);
}