#include <gtest/gtest.h>
#include "common/util/memory_stream.h"
#include "common/guilds.h"

#include <cstring>
#include <cstdint>

// ============================================================
// EQ::Util::MemoryStreamWriter
// ============================================================
TEST(MemoryStreamWriterTest, WriteIntegerToBuffer) {
    char buf[64] = {};
    EQ::Util::MemoryStreamWriter w(buf, sizeof(buf));
    int32_t val = 42;
    w.write(reinterpret_cast<const char*>(&val), sizeof(val));
    EXPECT_TRUE(w.good());
    int32_t read_back = 0;
    std::memcpy(&read_back, buf, sizeof(read_back));
    EXPECT_EQ(read_back, 42);
}

TEST(MemoryStreamWriterTest, WriteStringToBuffer) {
    char buf[64] = {};
    EQ::Util::MemoryStreamWriter w(buf, sizeof(buf));
    w << "hello";
    EXPECT_EQ(std::string(buf, 5), "hello");
}

TEST(MemoryStreamWriterTest, MultipleWrites) {
    char buf[64] = {};
    EQ::Util::MemoryStreamWriter w(buf, sizeof(buf));
    w << "ab" << "cd";
    EXPECT_EQ(std::string(buf, 4), "abcd");
}

TEST(MemoryStreamWriterTest, WriteByteByByte) {
    char buf[4] = {};
    EQ::Util::MemoryStreamWriter w(buf, sizeof(buf));
    for (char c : {'A', 'B', 'C', 'D'}) {
        w.put(c);
    }
    EXPECT_TRUE(w.good());
    EXPECT_EQ(buf[0], 'A');
    EXPECT_EQ(buf[1], 'B');
    EXPECT_EQ(buf[2], 'C');
    EXPECT_EQ(buf[3], 'D');
}

TEST(MemoryStreamWriterTest, OverflowSetsBadBit) {
    char buf[4] = {};
    EQ::Util::MemoryStreamWriter w(buf, sizeof(buf));
    // Write more than buffer holds
    w.write("0123456789", 10);
    EXPECT_FALSE(w.good());
}

TEST(MemoryStreamWriterTest, EmptyBufferWriteFails) {
    char buf[1] = {};
    EQ::Util::MemoryStreamWriter w(buf, 0);
    w.put('X');
    EXPECT_FALSE(w.good());
}

// ============================================================
// EQ::Util::MemoryStreamReader
// ============================================================
TEST(MemoryStreamReaderTest, ReadIntegerFromBuffer) {
    int32_t src = 12345;
    char buf[4];
    std::memcpy(buf, &src, sizeof(src));

    EQ::Util::MemoryStreamReader r(buf, sizeof(buf));
    int32_t val = 0;
    r.read(reinterpret_cast<char*>(&val), sizeof(val));
    EXPECT_TRUE(r.good());
    EXPECT_EQ(val, 12345);
}

TEST(MemoryStreamReaderTest, ReadStringFromBuffer) {
    char buf[] = "hello";
    EQ::Util::MemoryStreamReader r(buf, 5);
    char out[6] = {};
    r.read(out, 5);
    EXPECT_EQ(std::string(out, 5), "hello");
}

TEST(MemoryStreamReaderTest, ReadByteByByte) {
    char buf[] = "ABCD";
    EQ::Util::MemoryStreamReader r(buf, 4);
    EXPECT_EQ(r.get(), 'A');
    EXPECT_EQ(r.get(), 'B');
    EXPECT_EQ(r.get(), 'C');
    EXPECT_EQ(r.get(), 'D');
    EXPECT_TRUE(r.good());
}

TEST(MemoryStreamReaderTest, ReadPastEndSetsFailBit) {
    char buf[] = "AB";
    EQ::Util::MemoryStreamReader r(buf, 2);
    char out[10];
    r.read(out, 10); // request more than available
    EXPECT_FALSE(r.good());
}

TEST(MemoryStreamReaderTest, RoundTripInt32) {
    char buf[sizeof(int32_t)];
    int32_t written = 0xDEAD;
    {
        EQ::Util::MemoryStreamWriter w(buf, sizeof(buf));
        w.write(reinterpret_cast<const char*>(&written), sizeof(written));
        ASSERT_TRUE(w.good());
    }
    {
        EQ::Util::MemoryStreamReader r(buf, sizeof(buf));
        int32_t read_val = 0;
        r.read(reinterpret_cast<char*>(&read_val), sizeof(read_val));
        ASSERT_TRUE(r.good());
        EXPECT_EQ(read_val, written);
    }
}

TEST(MemoryStreamReaderTest, RoundTripMultipleValues) {
    char buf[16];
    uint8_t byte_val   = 0xAB;
    uint32_t uint_val  = 0x12345678;
    {
        EQ::Util::MemoryStreamWriter w(buf, sizeof(buf));
        w.write(reinterpret_cast<const char*>(&byte_val),  sizeof(byte_val));
        w.write(reinterpret_cast<const char*>(&uint_val),  sizeof(uint_val));
        ASSERT_TRUE(w.good());
    }
    {
        EQ::Util::MemoryStreamReader r(buf, sizeof(buf));
        uint8_t  b2 = 0;
        uint32_t u2 = 0;
        r.read(reinterpret_cast<char*>(&b2), sizeof(b2));
        r.read(reinterpret_cast<char*>(&u2), sizeof(u2));
        ASSERT_TRUE(r.good());
        EXPECT_EQ(b2, byte_val);
        EXPECT_EQ(u2, uint_val);
    }
}

// ============================================================
// Guild constants (guilds.h)
// ============================================================
TEST(GuildConstantsTest, GuildNoneIsMaxUint32) {
    EXPECT_EQ(GUILD_NONE, 0xFFFFFFFFu);
}

TEST(GuildConstantsTest, MaxRankIs8) {
    EXPECT_EQ(GUILD_MAX_RANK, 8);
}

TEST(GuildConstantsTest, MaxFunctionsIs30) {
    EXPECT_EQ(GUILD_MAX_FUNCTIONS, 30);
}

TEST(GuildConstantsTest, StandardRankConstants) {
    EXPECT_EQ(GUILD_MEMBER_TI,     0);
    EXPECT_EQ(GUILD_OFFICER_TI,    1);
    EXPECT_EQ(GUILD_LEADER_TI,     2);
    EXPECT_EQ(GUILD_RANK_NONE_TI,  GUILD_MAX_RANK + 1);
}

TEST(GuildConstantsTest, RoF2RankConstants) {
    EXPECT_EQ(GUILD_RANK_NONE,     0);
    EXPECT_EQ(GUILD_LEADER,        1);
    EXPECT_EQ(GUILD_SENIOR_OFFICER,2);
    EXPECT_EQ(GUILD_OFFICER,       3);
    EXPECT_EQ(GUILD_SENIOR_MEMBER, 4);
    EXPECT_EQ(GUILD_MEMBER,        5);
    EXPECT_EQ(GUILD_JUNIOR_MEMBER, 6);
    EXPECT_EQ(GUILD_INITIATE,      7);
    EXPECT_EQ(GUILD_RECRUIT,       8);
}

TEST(GuildConstantsTest, TributeConstants) {
    EXPECT_EQ(GUILD_TRIBUTES_MODIFY, 1);
    EXPECT_EQ(GUILD_TRIBUTES_SAVE,   0);
    EXPECT_EQ(GUILD_TRIBUTES_OFF,    0);
    EXPECT_EQ(GUILD_TRIBUTES_ON,     1);
}

// ============================================================
// GuildAction enum
// ============================================================
TEST(GuildActionTest, BannerActionsStart) {
    EXPECT_EQ(GUILD_ACTION_BANNER_CHANGE,  1);
    EXPECT_EQ(GUILD_ACTION_BANNER_PLANT,   2);
    EXPECT_EQ(GUILD_ACTION_BANNER_REMOVE,  3);
}

TEST(GuildActionTest, MemberActions) {
    EXPECT_EQ(GUILD_ACTION_MEMBERS_INVITE,  7);
    EXPECT_EQ(GUILD_ACTION_MEMBERS_PROMOTE, 8);
    EXPECT_EQ(GUILD_ACTION_MEMBERS_DEMOTE,  9);
    EXPECT_EQ(GUILD_ACTION_MEMBERS_REMOVE, 10);
}

TEST(GuildActionTest, BankActions) {
    EXPECT_EQ(GUILD_ACTION_BANK_DEPOSIT_ITEMS,          13);
    EXPECT_EQ(GUILD_ACTION_BANK_WITHDRAW_ITEMS,         14);
    EXPECT_EQ(GUILD_ACTION_BANK_VIEW_ITEMS,             15);
}

TEST(GuildActionTest, LastActionIs30) {
    EXPECT_EQ(GUILD_ACTION_MEMBERS_DEMOTE_SELF, 30);
}
