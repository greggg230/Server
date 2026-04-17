#include <gtest/gtest.h>
#include "common/net/packet.h"

#include <cstdint>
#include <cstring>

// ============================================================
// EQ::Net::DynamicPacket — default construction
// ============================================================
TEST(DynamicPacketTest, DefaultLengthIsZero) {
    EQ::Net::DynamicPacket pkt;
    EXPECT_EQ(pkt.Length(), 0u);
}

TEST(DynamicPacketTest, DefaultDoesNotCrash) {
    EXPECT_NO_THROW(EQ::Net::DynamicPacket pkt);
}

// ============================================================
// EQ::Net::DynamicPacket — Resize
// ============================================================
TEST(DynamicPacketTest, ResizeExpandsLength) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(16);
    EXPECT_EQ(pkt.Length(), 16u);
}

TEST(DynamicPacketTest, ResizeZeroCollapses) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(32);
    pkt.Resize(0);
    EXPECT_EQ(pkt.Length(), 0u);
}

TEST(DynamicPacketTest, ResizeReturnTrue) {
    EQ::Net::DynamicPacket pkt;
    EXPECT_TRUE(pkt.Resize(8));
}

TEST(DynamicPacketTest, DataNonNullAfterResize) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(4);
    EXPECT_NE(pkt.Data(), nullptr);
}

// ============================================================
// EQ::Net::DynamicPacket — Clear
// ============================================================
TEST(DynamicPacketTest, ClearReturnsTrue) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(8);
    EXPECT_TRUE(pkt.Clear());
}

TEST(DynamicPacketTest, ClearResetsLength) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(8);
    pkt.Clear();
    EXPECT_EQ(pkt.Length(), 0u);
}

// ============================================================
// EQ::Net::DynamicPacket — copy construction
// ============================================================
TEST(DynamicPacketTest, CopyConstructorPreservesLength) {
    EQ::Net::DynamicPacket src;
    src.Resize(20);
    EQ::Net::DynamicPacket dst(src);
    EXPECT_EQ(dst.Length(), 20u);
}

TEST(DynamicPacketTest, MoveConstructorPreservesLength) {
    EQ::Net::DynamicPacket src;
    src.Resize(12);
    EQ::Net::DynamicPacket dst(std::move(src));
    EXPECT_EQ(dst.Length(), 12u);
}

// ============================================================
// EQ::Net::DynamicPacket — PutSerialize / GetSerialize (uint8)
// ============================================================
TEST(DynamicPacketTest, PutGetUInt8RoundTrip) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(4);
    pkt.PutSerialize<uint8_t>(0, 0xAB);
    EXPECT_EQ(pkt.GetSerialize<uint8_t>(0), 0xABu);
}

TEST(DynamicPacketTest, PutGetUInt16RoundTrip) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(8);
    pkt.PutSerialize<uint16_t>(0, 0x1234);
    EXPECT_EQ(pkt.GetSerialize<uint16_t>(0), 0x1234u);
}

TEST(DynamicPacketTest, PutGetUInt32RoundTrip) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(8);
    pkt.PutSerialize<uint32_t>(0, 0xDEADBEEFu);
    EXPECT_EQ(pkt.GetSerialize<uint32_t>(0), 0xDEADBEEFu);
}

TEST(DynamicPacketTest, PutGetAtOffset) {
    // PutUInt8 is a dedicated helper that doesn't share the internal stream
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(8);
    pkt.PutUInt8(0, 0x11);
    pkt.PutUInt8(4, 0x22);
    EXPECT_EQ(pkt.GetUInt8(0), (uint8_t)0x11);
    EXPECT_EQ(pkt.GetUInt8(4), (uint8_t)0x22);
}

// ============================================================
// EQ::Net::DynamicPacket — GetInt* / PutSerialize typed helpers
// ============================================================
TEST(DynamicPacketTest, GetInt8AfterPut) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(4);
    pkt.PutSerialize<int8_t>(0, -5);
    EXPECT_EQ(pkt.GetInt8(0), (int8_t)-5);
}

TEST(DynamicPacketTest, GetInt16AfterPut) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(4);
    pkt.PutSerialize<int16_t>(0, -300);
    EXPECT_EQ(pkt.GetInt16(0), (int16_t)-300);
}

TEST(DynamicPacketTest, GetUInt8AfterPut) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(4);
    pkt.PutSerialize<uint8_t>(0, 200);
    EXPECT_EQ(pkt.GetUInt8(0), (uint8_t)200);
}

TEST(DynamicPacketTest, GetUInt32AfterPut) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(8);
    pkt.PutSerialize<uint32_t>(0, 999999u);
    EXPECT_EQ(pkt.GetUInt32(0), 999999u);
}

// ============================================================
// EQ::Net::DynamicPacket — GetString / PutString
// ============================================================
TEST(DynamicPacketTest, PutGetCStringRoundTrip) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(32);
    pkt.PutCString(0, "hello");
    std::string result = pkt.GetCString(0);
    EXPECT_EQ(result, "hello");
}

TEST(DynamicPacketTest, PutGetStringWithLength) {
    EQ::Net::DynamicPacket pkt;
    pkt.Resize(32);
    pkt.PutString(0, "world");
    std::string result = pkt.GetString(0, 5);
    EXPECT_EQ(result, "world");
}

// ============================================================
// EQ::Net::StaticPacket — basic construction
// ============================================================
TEST(StaticPacketTest, LengthMatchesBuffer) {
    uint8_t buf[16] = {0};
    EQ::Net::StaticPacket pkt(buf, sizeof(buf));
    EXPECT_EQ(pkt.Length(), 16u);
}

TEST(StaticPacketTest, DataPointsToBuffer) {
    uint8_t buf[8] = {0xAA, 0xBB};
    EQ::Net::StaticPacket pkt(buf, sizeof(buf));
    EXPECT_EQ(pkt.Data(), buf);
}

TEST(StaticPacketTest, ClearReturnsFalse) {
    uint8_t buf[8] = {0};
    EQ::Net::StaticPacket pkt(buf, sizeof(buf));
    EXPECT_FALSE(pkt.Clear());
}

TEST(StaticPacketTest, PutGetUInt8RoundTrip) {
    uint8_t buf[8] = {0};
    EQ::Net::StaticPacket pkt(buf, sizeof(buf));
    pkt.PutSerialize<uint8_t>(0, 0xCC);
    EXPECT_EQ(pkt.GetSerialize<uint8_t>(0), 0xCCu);
}

TEST(StaticPacketTest, CopyConstructorPreservesLength) {
    uint8_t buf[12] = {0};
    EQ::Net::StaticPacket src(buf, sizeof(buf));
    EQ::Net::StaticPacket dst(src);
    EXPECT_EQ(dst.Length(), 12u);
}
