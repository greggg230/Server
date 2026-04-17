#include <gtest/gtest.h>
#include <cmath>
#include "common/data_verification.h"
#include "common/misc_functions.h"

// ── EQ::Clamp ─────────────────────────────────────────────────────────────────

TEST(ClampTest, WithinRange) {
	EXPECT_EQ(50, EQ::Clamp(50, 0, 100));
}

TEST(ClampTest, BelowLower) {
	EXPECT_EQ(0, EQ::Clamp(-5, 0, 100));
}

TEST(ClampTest, AboveUpper) {
	EXPECT_EQ(100, EQ::Clamp(150, 0, 100));
}

TEST(ClampTest, AtLowerBound) {
	EXPECT_EQ(0, EQ::Clamp(0, 0, 100));
}

TEST(ClampTest, AtUpperBound) {
	EXPECT_EQ(100, EQ::Clamp(100, 0, 100));
}

TEST(ClampTest, FloatValues) {
	EXPECT_FLOAT_EQ(1.0f, EQ::Clamp(1.5f, 0.0f, 1.0f));
	EXPECT_FLOAT_EQ(0.5f, EQ::Clamp(0.5f, 0.0f, 1.0f));
}

TEST(ClampTest, ClampLower_Above) {
	EXPECT_EQ(10, EQ::ClampLower(10, 5));
}

TEST(ClampTest, ClampLower_Below) {
	EXPECT_EQ(5, EQ::ClampLower(3, 5));
}

TEST(ClampTest, ClampUpper_Below) {
	EXPECT_EQ(10, EQ::ClampUpper(10, 100));
}

TEST(ClampTest, ClampUpper_Above) {
	EXPECT_EQ(100, EQ::ClampUpper(150, 100));
}

// ── EQ::ValueWithin ───────────────────────────────────────────────────────────

TEST(ValueWithinTest, InsideRange) {
	EXPECT_TRUE(EQ::ValueWithin(50, 0, 100));
}

TEST(ValueWithinTest, AtLowerBound) {
	EXPECT_TRUE(EQ::ValueWithin(0, 0, 100));
}

TEST(ValueWithinTest, AtUpperBound) {
	EXPECT_TRUE(EQ::ValueWithin(100, 0, 100));
}

TEST(ValueWithinTest, BelowRange) {
	EXPECT_FALSE(EQ::ValueWithin(-1, 0, 100));
}

TEST(ValueWithinTest, AboveRange) {
	EXPECT_FALSE(EQ::ValueWithin(101, 0, 100));
}

// ── EQ Fixed-Point Conversions ────────────────────────────────────────────────

TEST(FixedPointTest, EQ13toFloat_Zero) {
	EXPECT_FLOAT_EQ(0.0f, EQ13toFloat(0));
}

TEST(FixedPointTest, EQ13toFloat_OneUnit) {
	EXPECT_FLOAT_EQ(1.0f / 64.0f, EQ13toFloat(1));
}

TEST(FixedPointTest, EQ13toFloat_RoundTrip) {
	// Float -> EQ13 -> Float should be close for values that encode exactly
	float original = 128.0f;
	EXPECT_FLOAT_EQ(original, EQ13toFloat(FloatToEQ13(original)));
}

TEST(FixedPointTest, FloatToEQ13_Zero) {
	EXPECT_EQ(0, FloatToEQ13(0.0f));
}

TEST(FixedPointTest, FloatToEQ13_OneHundred) {
	EXPECT_EQ(6400, FloatToEQ13(100.0f));
}

TEST(FixedPointTest, EQ19toFloat_RoundTrip) {
	float original = 64.0f;
	EXPECT_FLOAT_EQ(original, EQ19toFloat(FloatToEQ19(original)));
}

TEST(FixedPointTest, EQ10toFloat_Zero) {
	EXPECT_FLOAT_EQ(0.0f, EQ10toFloat(0));
}

TEST(FixedPointTest, EQ10toFloat_RoundTrip) {
	float original = 200.0f;
	EXPECT_FLOAT_EQ(original, EQ10toFloat(FloatToEQ10(original)));
}

TEST(FixedPointTest, EQSpeedRunRoundTrip) {
	float original = 150.0f;
	EXPECT_FLOAT_EQ(original, EQSpeedRunToFloat(FloatToEQSpeedRun(original)));
}

TEST(FixedPointTest, EQ12toFloat_RoundTrip) {
	// EQ12 is a position encoding; check simple non-modulo value
	EXPECT_FLOAT_EQ(0.25f, EQ12toFloat(1));
}

// ── FixHeading ────────────────────────────────────────────────────────────────

TEST(FixHeadingTest, WithinRange) {
	// Values already in [0, 512) should be unchanged
	EXPECT_FLOAT_EQ(256.0f, FixHeading(256.0f));
	EXPECT_FLOAT_EQ(0.0f, FixHeading(0.0f));
}

TEST(FixHeadingTest, AboveRange_Wraps) {
	float result = FixHeading(512.0f);
	EXPECT_GE(result, 0.0f);
	EXPECT_LT(result, 512.0f);
}

TEST(FixHeadingTest, NegativeWraps) {
	float result = FixHeading(-1.0f);
	EXPECT_GE(result, 0.0f);
	EXPECT_LT(result, 512.0f);
}

TEST(FixHeadingTest, LargePositive_Wraps) {
	float result = FixHeading(1024.0f);
	EXPECT_GE(result, 0.0f);
	EXPECT_LT(result, 512.0f);
}

TEST(FixHeadingTest, LargeNegative_Wraps) {
	float result = FixHeading(-512.0f);
	EXPECT_GE(result, 0.0f);
	EXPECT_LT(result, 512.0f);
}

// ── SwapBits21And22 ───────────────────────────────────────────────────────────

TEST(SwapBitsTest, BothClear_NoChange) {
	uint32 mask = 0x00000000;
	EXPECT_EQ(mask, SwapBits21And22(mask));
}

TEST(SwapBitsTest, BothSet_NoChange) {
	uint32 mask = (1u << 21) | (1u << 22);
	EXPECT_EQ(mask, SwapBits21And22(mask));
}

TEST(SwapBitsTest, OnlyBit21_SwapsToBit22) {
	// If only one of the two bits is set, both are XORd (swapped)
	uint32 mask = (1u << 21);
	uint32 result = SwapBits21And22(mask);
	EXPECT_EQ(1u << 22, result);
}

TEST(SwapBitsTest, OnlyBit22_SwapsToBit21) {
	uint32 mask = (1u << 22);
	uint32 result = SwapBits21And22(mask);
	EXPECT_EQ(1u << 21, result);
}

TEST(SwapBitsTest, OtherBitsPreserved) {
	uint32 mask = 0xFFFFFFFF;
	// Both bits set → no change expected
	EXPECT_EQ(mask, SwapBits21And22(mask));
}

// ── Catch22 ───────────────────────────────────────────────────────────────────

TEST(Catch22Test, Bit22Set_Cleared) {
	uint32 mask = (1u << 22);
	EXPECT_EQ(0u, Catch22(mask));
}

TEST(Catch22Test, Bit22Clear_Unchanged) {
	uint32 mask = (1u << 21) | (1u << 5);
	EXPECT_EQ(mask, Catch22(mask));
}

TEST(Catch22Test, AllBits_Bit22Cleared) {
	uint32 mask = 0xFFFFFFFF;
	uint32 result = Catch22(mask);
	EXPECT_EQ(0u, result & (1u << 22));
	EXPECT_NE(0u, result & (1u << 21)); // bit 21 preserved
}
