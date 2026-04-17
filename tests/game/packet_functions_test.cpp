#include <gtest/gtest.h>
#include "common/packet_functions.h"

#include <cstdint>

// ============================================================
// roll (left rotate) — uint32
// ============================================================
TEST(RollUint32Test, RotateZeroBitsIsIdentity) {
    EXPECT_EQ(roll(uint32_t(0x12345678), 0), uint32_t(0x12345678));
}

TEST(RollUint32Test, Rotate8Bits) {
    // 0x12345678 << 8 | 0x12345678 >> 24 = 0x34567812
    EXPECT_EQ(roll(uint32_t(0x12345678), 8), uint32_t(0x34567812));
}

TEST(RollUint32Test, Rotate16Bits) {
    // 0x12345678 rotated 16 = 0x56781234
    EXPECT_EQ(roll(uint32_t(0x12345678), 16), uint32_t(0x56781234));
}

TEST(RollUint32Test, Rotate32BitsIsIdentity) {
    EXPECT_EQ(roll(uint32_t(0xDEADBEEF), 32), uint32_t(0xDEADBEEF));
}

TEST(RollUint32Test, RotateOneIsDoubleOrWraps) {
    uint32_t in = 0x80000001u;
    // high bit goes to bit0, bit0 goes to bit1 → 0x00000003
    EXPECT_EQ(roll(in, 1), uint32_t(0x00000003));
}

// ============================================================
// rorl (right rotate) — uint32
// ============================================================
TEST(RorlUint32Test, RotateZeroBitsIsIdentity) {
    EXPECT_EQ(rorl(uint32_t(0x12345678), 0), uint32_t(0x12345678));
}

TEST(RorlUint32Test, Rotate8Bits) {
    // 0x12345678 >> 8 | 0x12345678 << 24 = 0x78123456
    EXPECT_EQ(rorl(uint32_t(0x12345678), 8), uint32_t(0x78123456));
}

TEST(RorlUint32Test, Rotate16Bits) {
    EXPECT_EQ(rorl(uint32_t(0x12345678), 16), uint32_t(0x56781234));
}

TEST(RorlUint32Test, Rotate32BitsIsIdentity) {
    EXPECT_EQ(rorl(uint32_t(0xDEADBEEF), 32), uint32_t(0xDEADBEEF));
}

// ============================================================
// roll and rorl are inverses of each other
// ============================================================
TEST(RollRorlInverseTest, Uint32RoundTrip8) {
    uint32_t in = 0xABCDEF01u;
    EXPECT_EQ(rorl(roll(in, 8), 8), in);
}

TEST(RollRorlInverseTest, Uint32RoundTrip16) {
    uint32_t in = 0x11223344u;
    EXPECT_EQ(rorl(roll(in, 16), 16), in);
}

TEST(RollRorlInverseTest, Uint32RoundTrip1) {
    uint32_t in = 0xFEDCBA98u;
    EXPECT_EQ(rorl(roll(in, 1), 1), in);
}

// ============================================================
// roll (left rotate) — uint64
// ============================================================
TEST(RollUint64Test, Rotate64BitsIsIdentity) {
    uint64_t in = 0x1234567890ABCDEFull;
    EXPECT_EQ(roll(in, 64), in);
}

TEST(RollUint64Test, Rotate8Bits) {
    uint64_t in = 0x0102030405060708ull;
    uint64_t expected = (in << 8) | (in >> 56);
    EXPECT_EQ(roll(in, 8), expected);
}

// ============================================================
// rorl (right rotate) — uint64
// ============================================================
TEST(RorlUint64Test, Rotate64BitsIsIdentity) {
    uint64_t in = 0xDEADBEEFCAFEBABEull;
    EXPECT_EQ(rorl(in, 64), in);
}

TEST(RorlUint64Test, RoundTrip8) {
    uint64_t in = 0x0807060504030201ull;
    EXPECT_EQ(rorl(roll(in, 8), 8), in);
}

// ============================================================
// GenerateCRC — determinism and basic properties
// ============================================================
TEST(GenerateCRCTest, EmptyBufferDeterministic) {
    uint8_t buf[1] = {0};
    uint32_t c1 = GenerateCRC(0, 0, buf);
    uint32_t c2 = GenerateCRC(0, 0, buf);
    EXPECT_EQ(c1, c2);
}

TEST(GenerateCRCTest, NonEmptyBufferDeterministic) {
    uint8_t buf[] = {0x01, 0x02, 0x03, 0x04};
    uint32_t c1 = GenerateCRC(0, sizeof(buf), buf);
    uint32_t c2 = GenerateCRC(0, sizeof(buf), buf);
    EXPECT_EQ(c1, c2);
}

TEST(GenerateCRCTest, DifferentDataDifferentCRC) {
    uint8_t buf1[] = {0x00};
    uint8_t buf2[] = {0xFF};
    uint32_t c1 = GenerateCRC(0, 1, buf1);
    uint32_t c2 = GenerateCRC(0, 1, buf2);
    EXPECT_NE(c1, c2);
}

TEST(GenerateCRCTest, DifferentSeedsDifferentCRC) {
    uint8_t buf[] = {0xAB, 0xCD};
    uint32_t c1 = GenerateCRC(0, sizeof(buf), buf);
    uint32_t c2 = GenerateCRC(1, sizeof(buf), buf);
    EXPECT_NE(c1, c2);
}
