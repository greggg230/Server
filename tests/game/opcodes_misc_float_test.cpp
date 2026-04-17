#include <gtest/gtest.h>
#include "common/op_codes.h"
#include "common/misc_functions.h"

#include <cmath>

// ============================================================
// op_codes.h — session-layer opcode constants
// ============================================================
TEST(OpCodeTest, SessionRequestIsOne) {
    EXPECT_EQ(static_cast<int>(OP_SessionRequest), 0x01);
}

TEST(OpCodeTest, SessionResponseIsTwo) {
    EXPECT_EQ(static_cast<int>(OP_SessionResponse), 0x02);
}

TEST(OpCodeTest, CombinedIsThree) {
    EXPECT_EQ(static_cast<int>(OP_Combined), 0x03);
}

TEST(OpCodeTest, SessionDisconnectIsFive) {
    EXPECT_EQ(static_cast<int>(OP_SessionDisconnect), 0x05);
}

TEST(OpCodeTest, AllDistinct) {
    EXPECT_NE(OP_SessionRequest,    OP_SessionResponse);
    EXPECT_NE(OP_SessionResponse,   OP_Combined);
    EXPECT_NE(OP_SessionDisconnect, OP_KeepAlive);
    EXPECT_NE(OP_Packet,            OP_Fragment);
    EXPECT_NE(OP_Ack,               OP_OutOfOrderAck);
}

// ============================================================
// EQ13 / FloatToEQ13 — scale factor 64
// ============================================================
TEST(EQ13FloatTest, ZeroRoundTrip) {
    EXPECT_FLOAT_EQ(EQ13toFloat(0), 0.0f);
    EXPECT_EQ(FloatToEQ13(0.0f), 0);
}

TEST(EQ13FloatTest, PositiveValue) {
    // 64 EQ13 units = 1.0f
    EXPECT_FLOAT_EQ(EQ13toFloat(64), 1.0f);
    EXPECT_EQ(FloatToEQ13(1.0f), 64);
}

TEST(EQ13FloatTest, NegativeValue) {
    EXPECT_FLOAT_EQ(EQ13toFloat(-64), -1.0f);
    EXPECT_EQ(FloatToEQ13(-1.0f), -64);
}

TEST(EQ13FloatTest, RoundTrip) {
    for (int i = -200; i <= 200; i += 10) {
        EXPECT_EQ(FloatToEQ13(EQ13toFloat(i)), i);
    }
}

// ============================================================
// EQ19 / FloatToEQ19 — scale factor 8
// ============================================================
TEST(EQ19FloatTest, ZeroRoundTrip) {
    EXPECT_FLOAT_EQ(EQ19toFloat(0), 0.0f);
    EXPECT_EQ(FloatToEQ19(0.0f), 0);
}

TEST(EQ19FloatTest, EightUnitsIsOne) {
    EXPECT_FLOAT_EQ(EQ19toFloat(8), 1.0f);
    EXPECT_EQ(FloatToEQ19(1.0f), 8);
}

TEST(EQ19FloatTest, RoundTrip) {
    for (int i = -100; i <= 100; i += 8) {
        EXPECT_EQ(FloatToEQ19(EQ19toFloat(i)), i);
    }
}

// ============================================================
// EQ10 / FloatToEQ10 — scale factor 20
// ============================================================
TEST(EQ10FloatTest, ZeroRoundTrip) {
    EXPECT_FLOAT_EQ(EQ10toFloat(0), 0.0f);
    EXPECT_EQ(FloatToEQ10(0.0f), 0);
}

TEST(EQ10FloatTest, TwentyUnitsIsOne) {
    EXPECT_FLOAT_EQ(EQ10toFloat(20), 1.0f);
    EXPECT_EQ(FloatToEQ10(1.0f), 20);
}

TEST(EQ10FloatTest, RoundTrip) {
    for (int i = 0; i <= 200; i += 20) {
        EXPECT_EQ(FloatToEQ10(EQ10toFloat(i)), i);
    }
}

// ============================================================
// EQ12 / FloatToEQ12 — scale factor 4, wrapping mod
// ============================================================
TEST(EQ12FloatTest, ZeroDecodesCorrectly) {
    EXPECT_FLOAT_EQ(EQ12toFloat(0), 0.0f);
}

TEST(EQ12FloatTest, FourUnitsIsOne) {
    EXPECT_FLOAT_EQ(EQ12toFloat(4), 1.0f);
}

TEST(EQ12FloatTest, NegativeDecodes) {
    EXPECT_FLOAT_EQ(EQ12toFloat(-4), -1.0f);
}

// ============================================================
// EQH heading conversions (360-degree range)
// ============================================================
TEST(EQHFloatTest, ZeroHeadingIsAtMost360) {
    float h = EQHtoFloat(0);
    EXPECT_GE(h, 0.0f);
    EXPECT_LE(h, 360.0f);
}

TEST(EQHFloatTest, RoundTripHeading) {
    // For a heading of 90 degrees
    float original = 90.0f;
    int encoded = FloatToEQH(original);
    float decoded = EQHtoFloat(encoded);
    EXPECT_NEAR(decoded, original, 1.0f); // allow 1 degree rounding error
}
