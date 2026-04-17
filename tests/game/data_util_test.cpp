#include <gtest/gtest.h>
#include <cstring>
#include "common/data_verification.h"
#include "common/md5.h"

// ============================================================
// EQ::Clamp
// ============================================================
TEST(ClampTest, ValueBelowLowerClampsToLower) {
    EXPECT_EQ(EQ::Clamp(5, 10, 20), 10);
    EXPECT_EQ(EQ::Clamp(-5, 0, 100), 0);
}

TEST(ClampTest, ValueAboveUpperClampsToUpper) {
    EXPECT_EQ(EQ::Clamp(30, 10, 20), 20);
    EXPECT_EQ(EQ::Clamp(200, 0, 100), 100);
}

TEST(ClampTest, ValueWithinRangeUnchanged) {
    EXPECT_EQ(EQ::Clamp(15, 10, 20), 15);
    EXPECT_EQ(EQ::Clamp(0, -10, 10), 0);
}

TEST(ClampTest, ValueAtLowerBoundUnchanged) {
    EXPECT_EQ(EQ::Clamp(10, 10, 20), 10);
}

TEST(ClampTest, ValueAtUpperBoundUnchanged) {
    EXPECT_EQ(EQ::Clamp(20, 10, 20), 20);
}

TEST(ClampTest, WorksWithFloat) {
    EXPECT_FLOAT_EQ(EQ::Clamp(1.5f, 2.0f, 5.0f), 2.0f);
    EXPECT_FLOAT_EQ(EQ::Clamp(3.0f, 2.0f, 5.0f), 3.0f);
    EXPECT_FLOAT_EQ(EQ::Clamp(7.0f, 2.0f, 5.0f), 5.0f);
}

// ============================================================
// EQ::ClampLower
// ============================================================
TEST(ClampLowerTest, ValueBelowLowerClampsToLower) {
    EXPECT_EQ(EQ::ClampLower(5, 10), 10);
}

TEST(ClampLowerTest, ValueAtOrAboveLowerUnchanged) {
    EXPECT_EQ(EQ::ClampLower(10, 10), 10);
    EXPECT_EQ(EQ::ClampLower(20, 10), 20);
}

TEST(ClampLowerTest, WorksWithFloat) {
    EXPECT_FLOAT_EQ(EQ::ClampLower(1.0f, 2.0f), 2.0f);
    EXPECT_FLOAT_EQ(EQ::ClampLower(3.0f, 2.0f), 3.0f);
}

// ============================================================
// EQ::ClampUpper
// ============================================================
TEST(ClampUpperTest, ValueAboveUpperClampsToUpper) {
    EXPECT_EQ(EQ::ClampUpper(30, 20), 20);
}

TEST(ClampUpperTest, ValueAtOrBelowUpperUnchanged) {
    EXPECT_EQ(EQ::ClampUpper(20, 20), 20);
    EXPECT_EQ(EQ::ClampUpper(5, 20), 5);
}

TEST(ClampUpperTest, WorksWithFloat) {
    EXPECT_FLOAT_EQ(EQ::ClampUpper(7.0f, 5.0f), 5.0f);
    EXPECT_FLOAT_EQ(EQ::ClampUpper(3.0f, 5.0f), 3.0f);
}

// ============================================================
// EQ::ValueWithin
// ============================================================
TEST(ValueWithinTest, WithinInclusiveBoundsReturnsTrue) {
    EXPECT_TRUE(EQ::ValueWithin(10, 10, 20));
    EXPECT_TRUE(EQ::ValueWithin(15, 10, 20));
    EXPECT_TRUE(EQ::ValueWithin(20, 10, 20));
}

TEST(ValueWithinTest, OutsideBoundsReturnsFalse) {
    EXPECT_FALSE(EQ::ValueWithin(9, 10, 20));
    EXPECT_FALSE(EQ::ValueWithin(21, 10, 20));
}

TEST(ValueWithinTest, WorksWithFloat) {
    EXPECT_TRUE(EQ::ValueWithin(2.5f, 2.0f, 3.0f));
    EXPECT_FALSE(EQ::ValueWithin(1.9f, 2.0f, 3.0f));
}

TEST(ValueWithinTest, MixedTypesCompile) {
    // ValueWithin<T1, T2, T3> overload
    EXPECT_TRUE(EQ::ValueWithin(15, 10, 20));
    EXPECT_FALSE(EQ::ValueWithin(5, 10, 20));
}

// ============================================================
// MD5 — known test vectors
// ============================================================
TEST(MD5Test, EmptyStringKnownHash) {
    MD5 md5;
    md5.Generate("");
    const char* result = (const char*)md5;
    EXPECT_STREQ(result, "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(MD5Test, AbcKnownHash) {
    MD5 md5;
    md5.Generate("abc");
    EXPECT_STREQ((const char*)md5, "900150983cd24fb0d6963f7d28e17f72");
}

TEST(MD5Test, HelloKnownHash) {
    MD5 md5;
    md5.Generate("hello");
    EXPECT_STREQ((const char*)md5, "5d41402abc4b2a76b9719d911017c592");
}

TEST(MD5Test, QuickBrownFoxKnownHash) {
    MD5 md5;
    md5.Generate("The quick brown fox jumps over the lazy dog");
    EXPECT_STREQ((const char*)md5, "9e107d9d372bb6826bd81d3542a419d6");
}

TEST(MD5Test, StaticGenerateProducesSameResult) {
    uint8_t digest[16];
    const char* input = "hello";
    MD5::Generate(reinterpret_cast<const uint8_t*>(input), 5, digest);

    // Convert digest to hex string for comparison
    char hex[33];
    for (int i = 0; i < 16; ++i)
        snprintf(hex + i * 2, 3, "%02x", digest[i]);
    hex[32] = '\0';

    EXPECT_STREQ(hex, "5d41402abc4b2a76b9719d911017c592");
}

TEST(MD5Test, EqualityOperatorSameInput) {
    MD5 a, b;
    a.Generate("test");
    b.Generate("test");
    EXPECT_TRUE(a == b);
}

TEST(MD5Test, EqualityOperatorDifferentInput) {
    MD5 a, b;
    a.Generate("test");
    b.Generate("other");
    EXPECT_FALSE(a == b);
}

TEST(MD5Test, ConstructorFromHexDigestString) {
    // MD5(const char*) sets from an existing hex digest, not compute from input
    const char* known_hex = "5d41402abc4b2a76b9719d911017c592";
    MD5 md5(known_hex);
    EXPECT_STREQ((const char*)md5, known_hex);
}

TEST(MD5Test, ConstructorFromBuffer) {
    const char* buf = "hello";
    MD5 md5(reinterpret_cast<const uint8_t*>(buf), 5);
    EXPECT_STREQ((const char*)md5, "5d41402abc4b2a76b9719d911017c592");
}

TEST(MD5Test, HashStringIs32LowerHexChars) {
    MD5 md5;
    md5.Generate("eqemu");
    const char* s = (const char*)md5;
    ASSERT_EQ(strlen(s), 32u);
    for (int i = 0; i < 32; ++i)
        EXPECT_TRUE(isxdigit(s[i])) << "Non-hex at position " << i;
}
