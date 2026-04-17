#include <gtest/gtest.h>
#include <cmath>
#include "common/misc_functions.h"

// EQ13 format: fixed-point with 1/64 precision
TEST(EQ13Test, ZeroRoundTrip) {
    EXPECT_FLOAT_EQ(EQ13toFloat(0), 0.0f);
    EXPECT_EQ(FloatToEQ13(0.0f), 0);
}

TEST(EQ13Test, PositiveValues) {
    EXPECT_FLOAT_EQ(EQ13toFloat(64), 1.0f);
    EXPECT_FLOAT_EQ(EQ13toFloat(128), 2.0f);
    EXPECT_FLOAT_EQ(EQ13toFloat(32), 0.5f);
    EXPECT_EQ(FloatToEQ13(1.0f), 64);
    EXPECT_EQ(FloatToEQ13(2.0f), 128);
}

TEST(EQ13Test, NegativeValues) {
    EXPECT_FLOAT_EQ(EQ13toFloat(-64), -1.0f);
    EXPECT_EQ(FloatToEQ13(-1.0f), -64);
}

TEST(EQ13Test, RoundTrip) {
    for (int i = -5; i <= 5; ++i) {
        EXPECT_EQ(FloatToEQ13(EQ13toFloat(i * 64)), i * 64);
    }
}

// EQ19 format: fixed-point with 1/8 precision
TEST(EQ19Test, ZeroRoundTrip) {
    EXPECT_FLOAT_EQ(EQ19toFloat(0), 0.0f);
    EXPECT_EQ(FloatToEQ19(0.0f), 0);
}

TEST(EQ19Test, PositiveValues) {
    EXPECT_FLOAT_EQ(EQ19toFloat(8), 1.0f);
    EXPECT_FLOAT_EQ(EQ19toFloat(16), 2.0f);
    EXPECT_FLOAT_EQ(EQ19toFloat(4), 0.5f);
    EXPECT_EQ(FloatToEQ19(1.0f), 8);
    EXPECT_EQ(FloatToEQ19(2.0f), 16);
}

TEST(EQ19Test, RoundTrip) {
    for (int i = -5; i <= 5; ++i) {
        EXPECT_EQ(FloatToEQ19(EQ19toFloat(i * 8)), i * 8);
    }
}

// EQ12 format: 1/4 precision with wrapping offset
TEST(EQ12Test, ZeroConverts) {
    EXPECT_FLOAT_EQ(EQ12toFloat(0), 0.0f);
}

TEST(EQ12Test, PositiveValues) {
    EXPECT_FLOAT_EQ(EQ12toFloat(4), 1.0f);
    EXPECT_FLOAT_EQ(EQ12toFloat(8), 2.0f);
}

TEST(EQ12Test, FloatToEQ12NonNegative) {
    // FloatToEQ12 uses modulo so result is always in [0, 2047]
    EXPECT_EQ(FloatToEQ12(0.0f), 0);
    EXPECT_EQ(FloatToEQ12(1.0f), 4);
    EXPECT_EQ(FloatToEQ12(2.0f), 8);
}

// EQ10 format: 1/20 precision
TEST(EQ10Test, ZeroRoundTrip) {
    EXPECT_FLOAT_EQ(EQ10toFloat(0), 0.0f);
    EXPECT_EQ(FloatToEQ10(0.0f), 0);
}

TEST(EQ10Test, PositiveValues) {
    EXPECT_FLOAT_EQ(EQ10toFloat(20), 1.0f);
    EXPECT_FLOAT_EQ(EQ10toFloat(40), 2.0f);
    EXPECT_EQ(FloatToEQ10(1.0f), 20);
    EXPECT_EQ(FloatToEQ10(2.0f), 40);
}

TEST(EQ10Test, RoundTrip) {
    for (int i = 0; i <= 10; ++i) {
        EXPECT_EQ(FloatToEQ10(EQ10toFloat(i * 20)), i * 20);
    }
}

// EQSpeedRun format: 1/40 precision
TEST(EQSpeedRunTest, ZeroRoundTrip) {
    EXPECT_FLOAT_EQ(EQSpeedRunToFloat(0), 0.0f);
    EXPECT_EQ(FloatToEQSpeedRun(0.0f), 0);
}

TEST(EQSpeedRunTest, PositiveValues) {
    EXPECT_FLOAT_EQ(EQSpeedRunToFloat(40), 1.0f);
    EXPECT_FLOAT_EQ(EQSpeedRunToFloat(80), 2.0f);
    EXPECT_EQ(FloatToEQSpeedRun(1.0f), 40);
    EXPECT_EQ(FloatToEQSpeedRun(2.0f), 80);
}

TEST(EQSpeedRunTest, RoundTrip) {
    for (int i = 0; i <= 5; ++i) {
        EXPECT_EQ(FloatToEQSpeedRun(EQSpeedRunToFloat(i * 40)), i * 40);
    }
}

// EQH heading: 360 degrees mapped to 0-2048 EQ units
TEST(EQHTest, ZeroDegrees) {
    EXPECT_FLOAT_EQ(EQHtoFloat(FloatToEQH(0.0f)), 0.0f);
}

TEST(EQHTest, NinetyDegrees) {
    int eq = FloatToEQH(90.0f);
    EXPECT_EQ(eq, 1536);
    EXPECT_FLOAT_EQ(EQHtoFloat(eq), 90.0f);
}

TEST(EQHTest, OneEightyDegrees) {
    int eq = FloatToEQH(180.0f);
    EXPECT_EQ(eq, 1024);
    EXPECT_FLOAT_EQ(EQHtoFloat(eq), 180.0f);
}

TEST(EQHTest, TwoSeventyDegrees) {
    int eq = FloatToEQH(270.0f);
    EXPECT_EQ(eq, 512);
    EXPECT_FLOAT_EQ(EQHtoFloat(eq), 270.0f);
}

// FixHeading: wraps angle into [0, 512)
TEST(FixHeadingTest, InRangeUnchanged) {
    EXPECT_FLOAT_EQ(FixHeading(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(FixHeading(256.0f), 256.0f);
    EXPECT_FLOAT_EQ(FixHeading(511.9f), 511.9f);
}

TEST(FixHeadingTest, ExactlyFiveTwelveWraps) {
    EXPECT_FLOAT_EQ(FixHeading(512.0f), 0.0f);
}

TEST(FixHeadingTest, LargeValueWraps) {
    EXPECT_FLOAT_EQ(FixHeading(768.0f), 256.0f);
    EXPECT_FLOAT_EQ(FixHeading(1024.0f), 0.0f);
}

TEST(FixHeadingTest, NegativeValueWraps) {
    EXPECT_FLOAT_EQ(FixHeading(-256.0f), 256.0f);
    EXPECT_FLOAT_EQ(FixHeading(-512.0f), 0.0f);
}

// SwapBits21And22: swaps bits 21 and 22 when they differ
TEST(SwapBits21And22Test, BothClearNoSwap) {
    uint32 mask = 0x00000000u;
    EXPECT_EQ(SwapBits21And22(mask), 0x00000000u);
}

TEST(SwapBits21And22Test, BothSetNoSwap) {
    uint32 mask = (1u << 21) | (1u << 22);
    EXPECT_EQ(SwapBits21And22(mask), mask);
}

TEST(SwapBits21And22Test, OnlyBit21SetSwapsTobit22) {
    uint32 mask = (1u << 21);
    uint32 result = SwapBits21And22(mask);
    EXPECT_EQ(result, (1u << 22));
    EXPECT_EQ(result & (1u << 21), 0u);
}

TEST(SwapBits21And22Test, OnlyBit22SetSwapsToBit21) {
    uint32 mask = (1u << 22);
    uint32 result = SwapBits21And22(mask);
    EXPECT_EQ(result, (1u << 21));
    EXPECT_EQ(result & (1u << 22), 0u);
}

TEST(SwapBits21And22Test, OtherBitsUnaffected) {
    uint32 other = 0x000FFFFFu; // bits 0-19 set
    uint32 mask = other | (1u << 21); // bit21 set, bit22 clear → swap
    uint32 result = SwapBits21And22(mask);
    EXPECT_EQ(result & other, other); // low bits untouched
    EXPECT_EQ(result & (1u << 22), (1u << 22)); // bit22 now set
    EXPECT_EQ(result & (1u << 21), 0u);          // bit21 now clear
}

// Catch22: clears bit 22
TEST(Catch22Test, ClearsBit22) {
    uint32 mask = (1u << 22);
    EXPECT_EQ(Catch22(mask), 0u);
}

TEST(Catch22Test, PreservesOtherBits) {
    uint32 mask = 0xFFFFFFFFu;
    uint32 result = Catch22(mask);
    EXPECT_EQ(result & (1u << 22), 0u);
    EXPECT_EQ(result & ~(1u << 22), ~(1u << 22));
}

TEST(Catch22Test, AlreadyClearUnchanged) {
    uint32 mask = 0x001FFFFFu; // bits 0-20 only
    EXPECT_EQ(Catch22(mask), mask);
}

TEST(Catch22Test, Bit21Preserved) {
    uint32 mask = (1u << 21) | (1u << 22);
    uint32 result = Catch22(mask);
    EXPECT_EQ(result, (1u << 21));
}
