#include <gtest/gtest.h>
#include "common/data_verification.h"
#include "common/version.h"

#include <cstring>
#include <string>

// ============================================================
// EQ::Clamp
// ============================================================
TEST(EQClampTest, ValueInRangeUnchanged) {
    EXPECT_EQ(EQ::Clamp(5, 0, 10), 5);
}

TEST(EQClampTest, ValueBelowLowerClampsToLower) {
    EXPECT_EQ(EQ::Clamp(-5, 0, 10), 0);
}

TEST(EQClampTest, ValueAboveUpperClampsToUpper) {
    EXPECT_EQ(EQ::Clamp(15, 0, 10), 10);
}

TEST(EQClampTest, ValueAtLowerBoundaryUnchanged) {
    EXPECT_EQ(EQ::Clamp(0, 0, 10), 0);
}

TEST(EQClampTest, ValueAtUpperBoundaryUnchanged) {
    EXPECT_EQ(EQ::Clamp(10, 0, 10), 10);
}

TEST(EQClampTest, FloatClamp) {
    EXPECT_FLOAT_EQ(EQ::Clamp(1.5f, 0.0f, 1.0f), 1.0f);
    EXPECT_FLOAT_EQ(EQ::Clamp(-0.5f, 0.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(EQ::Clamp(0.5f, 0.0f, 1.0f), 0.5f);
}

// ============================================================
// EQ::ClampLower
// ============================================================
TEST(EQClampLowerTest, ValueAboveLowerUnchanged) {
    EXPECT_EQ(EQ::ClampLower(5, 0), 5);
}

TEST(EQClampLowerTest, ValueBelowLowerClamped) {
    EXPECT_EQ(EQ::ClampLower(-5, 0), 0);
}

TEST(EQClampLowerTest, ValueAtLowerBoundaryUnchanged) {
    EXPECT_EQ(EQ::ClampLower(0, 0), 0);
}

// ============================================================
// EQ::ClampUpper
// ============================================================
TEST(EQClampUpperTest, ValueBelowUpperUnchanged) {
    EXPECT_EQ(EQ::ClampUpper(5, 10), 5);
}

TEST(EQClampUpperTest, ValueAboveUpperClamped) {
    EXPECT_EQ(EQ::ClampUpper(15, 10), 10);
}

TEST(EQClampUpperTest, ValueAtUpperBoundaryUnchanged) {
    EXPECT_EQ(EQ::ClampUpper(10, 10), 10);
}

// ============================================================
// EQ::ValueWithin
// ============================================================
TEST(EQValueWithinTest, InsideRangeIsTrue) {
    EXPECT_TRUE(EQ::ValueWithin(5, 0, 10));
}

TEST(EQValueWithinTest, AtLowerBoundIsTrue) {
    EXPECT_TRUE(EQ::ValueWithin(0, 0, 10));
}

TEST(EQValueWithinTest, AtUpperBoundIsTrue) {
    EXPECT_TRUE(EQ::ValueWithin(10, 0, 10));
}

TEST(EQValueWithinTest, BelowLowerIsFalse) {
    EXPECT_FALSE(EQ::ValueWithin(-1, 0, 10));
}

TEST(EQValueWithinTest, AboveUpperIsFalse) {
    EXPECT_FALSE(EQ::ValueWithin(11, 0, 10));
}

TEST(EQValueWithinTest, MixedTypesWork) {
    EXPECT_TRUE(EQ::ValueWithin(5, 0, 10));
}

// ============================================================
// version.h — preprocessor constants
// ============================================================
TEST(VersionMacroTest, ProtocolVersionIsNonEmpty) {
    const char* v = EQEMU_PROTOCOL_VERSION;
    EXPECT_NE(v, nullptr);
    EXPECT_GT(strlen(v), 0u);
}

TEST(VersionMacroTest, CurrentVersionIsNonEmpty) {
    const char* v = CURRENT_VERSION;
    EXPECT_NE(v, nullptr);
    EXPECT_GT(strlen(v), 0u);
}

TEST(VersionMacroTest, LoginVersionIsNonEmpty) {
    const char* v = LOGIN_VERSION;
    EXPECT_NE(v, nullptr);
    EXPECT_GT(strlen(v), 0u);
}

TEST(VersionMacroTest, BinaryDatabaseVersionIsPositive) {
    EXPECT_GT(CURRENT_BINARY_DATABASE_VERSION, 0);
}

TEST(VersionMacroTest, BotsDatabaseVersionIsPositive) {
    EXPECT_GT(CURRENT_BINARY_BOTS_DATABASE_VERSION, 0);
}

TEST(VersionMacroTest, CompileDateIsNonEmpty) {
    const char* d = COMPILE_DATE;
    EXPECT_NE(d, nullptr);
    EXPECT_GT(strlen(d), 0u);
}
