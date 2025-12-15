// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/VoltMon_ReadVoltageProject_mV.h"

extern uint16_t supplyDcFiler_u16;
extern uint16_t supplyDcNotFiler_u16;
extern const uint16_t lowerVoltMonCfg_cu16;
extern const uint16_t higherVoltMonCfg_cu16;
extern const uint16_t middleLowerVoltMonCfg_cu16;
extern const uint16_t middleHigherVoltMonCfg_cu16;

void setUp(void)
{
    supplyDcFiler_u16 = 0u;
    supplyDcNotFiler_u16 = 0u;
}

void tearDown(void)
{
}
void test_VoltMon_ReadVoltageProject_mV_LowBand_LowerBoundaryPlus1(void)
{
    supplyDcNotFiler_u16 = 1u;
    supplyDcFiler_u16 = 5000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((1u)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_LowBand_MidValue(void)
{
    supplyDcNotFiler_u16 = 2500u;
    supplyDcFiler_u16 = 8000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((2500u)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_LowBand_UpperBoundaryMinus1(void)
{
    supplyDcNotFiler_u16 = 4999u;
    supplyDcFiler_u16 = 10000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((4999u)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_UINT16);
}
void test_VoltMon_ReadVoltageProject_mV_MiddleBand_LowerBoundary(void)
{
    supplyDcNotFiler_u16 = 5000u;
    supplyDcFiler_u16 = 6000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (6000u + 5000u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(98), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_MiddleBand_MidValue(void)
{
    supplyDcNotFiler_u16 = 7500u;
    supplyDcFiler_u16 = 8000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (8000u + 7500u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_MiddleBand_UpperBoundary(void)
{
    supplyDcNotFiler_u16 = 10000u;
    supplyDcFiler_u16 = 9500u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (9500u + 10000u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_MiddleBand_SameValues(void)
{
    supplyDcNotFiler_u16 = 7500u;
    supplyDcFiler_u16 = 7500u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (7500u + 7500u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_UINT16);
}
void test_VoltMon_ReadVoltageProject_mV_HighBand_LowerBoundaryPlus1(void)
{
    supplyDcNotFiler_u16 = 10001u;
    supplyDcFiler_u16 = 12000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (12000u + 10001u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(168), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_HighBand_MidValue(void)
{
    supplyDcNotFiler_u16 = 15000u;
    supplyDcFiler_u16 = 14000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (14000u + 15000u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(184), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_HighBand_UpperBoundaryMinus1(void)
{
    supplyDcNotFiler_u16 = 19999u;
    supplyDcFiler_u16 = 18000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (18000u + 19999u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(200), UNITY_DISPLAY_STYLE_UINT16);
}
void test_VoltMon_ReadVoltageProject_mV_OutOfRange_AtLowerBoundary(void)
{
    supplyDcNotFiler_u16 = 0u;
    supplyDcFiler_u16 = 5000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0u)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(221), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_OutOfRange_AtUpperBoundary(void)
{
    supplyDcNotFiler_u16 = 20000u;
    supplyDcFiler_u16 = 15000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0u)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(236), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_OutOfRange_AboveUpperBoundary(void)
{
    supplyDcNotFiler_u16 = 20001u;
    supplyDcFiler_u16 = 15000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0u)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(251), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_OutOfRange_MaxUint16(void)
{
    supplyDcNotFiler_u16 = 65535u;
    supplyDcFiler_u16 = 10000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0u)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(266), UNITY_DISPLAY_STYLE_UINT16);
}
void test_VoltMon_ReadVoltageProject_mV_MiddleBand_FilteredZero(void)
{
    supplyDcNotFiler_u16 = 7500u;
    supplyDcFiler_u16 = 0u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (0u + 7500u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(286), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_MiddleBand_FilteredMaxValue(void)
{
    supplyDcNotFiler_u16 = 10000u;
    supplyDcFiler_u16 = 65535u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (65535u + 10000u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(302), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_BoundaryTransition_5000(void)
{
    supplyDcNotFiler_u16 = 5000u;
    supplyDcFiler_u16 = 6000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (6000u + 5000u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(318), UNITY_DISPLAY_STYLE_UINT16);
}

void test_VoltMon_ReadVoltageProject_mV_BoundaryTransition_10000(void)
{
    supplyDcNotFiler_u16 = 10000u;
    supplyDcFiler_u16 = 9000u;

    uint16_t result = VoltMon_ReadVoltageProject_mV();

    uint16_t expected = (9000u + 10000u) >> 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(334), UNITY_DISPLAY_STYLE_UINT16);
}