#include <gtest/gtest.h>
#include "common/packet_dump.h"
#include "common/evolving_items.h"

#include <string>
#include <vector>

// ============================================================
// DumpPacketHexToString — boundary conditions
// ============================================================
TEST(DumpPacketHexTest, EmptySizeReturnsEmpty) {
    uint8_t buf[] = {0x41};
    EXPECT_EQ(DumpPacketHexToString(buf, 0), "");
}

TEST(DumpPacketHexTest, OversizedBufferReturnsEmpty) {
    // size > 39565 returns ""
    uint8_t buf[1] = {0};
    EXPECT_EQ(DumpPacketHexToString(buf, 39566), "");
}

TEST(DumpPacketHexTest, SingleByteReturnsNonEmpty) {
    uint8_t buf[] = {0x41}; // 'A'
    std::string result = DumpPacketHexToString(buf, 1);
    EXPECT_FALSE(result.empty());
}

TEST(DumpPacketHexTest, StartsWithNewline) {
    uint8_t buf[] = {0x41};
    std::string result = DumpPacketHexToString(buf, 1);
    EXPECT_EQ(result[0], '\n');
}

TEST(DumpPacketHexTest, ContainsHexDigits) {
    uint8_t buf[] = {0xFF, 0x00, 0xAB};
    std::string result = DumpPacketHexToString(buf, 3);
    EXPECT_NE(result.find("FF"), std::string::npos);
    EXPECT_NE(result.find("00"), std::string::npos);
    EXPECT_NE(result.find("AB"), std::string::npos);
}

TEST(DumpPacketHexTest, PrintableAsciiShowsInOutput) {
    uint8_t buf[] = {'H', 'e', 'l', 'l', 'o'};
    std::string result = DumpPacketHexToString(buf, 5);
    EXPECT_NE(result.find("Hello"), std::string::npos);
}

TEST(DumpPacketHexTest, NonPrintableShowsDot) {
    uint8_t buf[] = {0x01}; // non-printable (control char)
    std::string result = DumpPacketHexToString(buf, 1);
    EXPECT_NE(result.find('.'), std::string::npos);
}

TEST(DumpPacketHexTest, DeterministicOutput) {
    uint8_t buf[] = {0x12, 0x34, 0x56};
    EXPECT_EQ(DumpPacketHexToString(buf, 3), DumpPacketHexToString(buf, 3));
}

TEST(DumpPacketHexTest, DifferentBuffersDifferentOutput) {
    uint8_t buf1[] = {0x01, 0x02};
    uint8_t buf2[] = {0xFE, 0xFF};
    EXPECT_NE(DumpPacketHexToString(buf1, 2), DumpPacketHexToString(buf2, 2));
}

TEST(DumpPacketHexTest, MaxValidSizeAccepted) {
    // size=39565 is the maximum accepted value (> 39565 returns "")
    std::vector<uint8_t> buf(39565, 0xAA);
    std::string result = DumpPacketHexToString(buf.data(), 39565);
    EXPECT_FALSE(result.empty());
}

TEST(DumpPacketHexTest, CustomColsChangesOutput) {
    uint8_t buf[16];
    memset(buf, 0x41, 16);
    std::string result16 = DumpPacketHexToString(buf, 16, 16);
    std::string result8  = DumpPacketHexToString(buf, 16, 8);
    EXPECT_NE(result16, result8);
}

TEST(DumpPacketHexTest, SpaceAtByteOffsetZeroInOutput) {
    // The output starts with an offset like "   0: " before the hex bytes
    uint8_t buf[] = {0xAA};
    std::string result = DumpPacketHexToString(buf, 1);
    EXPECT_NE(result.find("0:"), std::string::npos);
}

// ============================================================
// EvolvingItemsManager::CalculateProgression — static, no DB
// ============================================================
TEST(EvolvingItemsProgressionTest, UnknownItemIDReturnsZero) {
    // Cache is empty without DB so any item_id returns 0
    EXPECT_DOUBLE_EQ(EvolvingItemsManager::CalculateProgression(100, 0), 0.0);
}

TEST(EvolvingItemsProgressionTest, ZeroAmountUnknownItemReturnsZero) {
    EXPECT_DOUBLE_EQ(EvolvingItemsManager::CalculateProgression(0, 9999), 0.0);
}

TEST(EvolvingItemsProgressionTest, LargeAmountUnknownItemReturnsZero) {
    EXPECT_DOUBLE_EQ(EvolvingItemsManager::CalculateProgression(UINT64_MAX, 12345), 0.0);
}

// ============================================================
// EvolvingItemsManager — singleton
// ============================================================
TEST(EvolvingItemsManagerTest, InstanceIsNotNull) {
    EXPECT_NE(EvolvingItemsManager::Instance(), nullptr);
}

TEST(EvolvingItemsManagerTest, InstanceIsSameObject) {
    EXPECT_EQ(EvolvingItemsManager::Instance(), EvolvingItemsManager::Instance());
}

TEST(EvolvingItemsManagerTest, CacheInitiallyEmpty) {
    auto& cache = EvolvingItemsManager::Instance()->GetEvolvingItemsCache();
    EXPECT_TRUE(cache.empty());
}
