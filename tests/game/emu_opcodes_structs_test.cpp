#include <gtest/gtest.h>
#include "common/emu_opcodes.h"
#include "common/eq_packet_structs.h"

// ============================================================
// emu_opcodes.h — EQEmu internal opcode enum
// ============================================================
TEST(EmuOpcodesTest, UnknownIsZero) {
    EXPECT_EQ(static_cast<int>(OP_Unknown), 0);
}

TEST(EmuOpcodesTest, MaxEQOpcodeConstant) {
    EXPECT_EQ(MAX_EQ_OPCODE, 0xFFFF);
}

TEST(EmuOpcodesTest, NamedOpcodesAreNonZero) {
    EXPECT_GT(static_cast<int>(OP_Camp),        0);
    EXPECT_GT(static_cast<int>(OP_Login),       0);
    EXPECT_GT(static_cast<int>(OP_ZoneChange),  0);
    EXPECT_GT(static_cast<int>(OP_ZoneEntry),   0);
    EXPECT_GT(static_cast<int>(OP_SpawnAppearance), 0);
}

TEST(EmuOpcodesTest, AllDistinct) {
    EXPECT_NE(OP_Camp,        OP_Login);
    EXPECT_NE(OP_ZoneChange,  OP_ZoneEntry);
    EXPECT_NE(OP_ZoneEntry,   OP_ZoneComplete);
    EXPECT_NE(OP_SpawnAppearance, OP_SpawnDoor);
}

TEST(EmuOpcodesTest, LoginSequential) {
    // These are consecutive entries in emu_oplist.h
    EXPECT_LT(static_cast<int>(OP_Login),         static_cast<int>(OP_LoginAccepted));
    EXPECT_LT(static_cast<int>(OP_LoginAccepted),  static_cast<int>(OP_LoginComplete));
}

// ============================================================
// eq_packet_structs.h — compile-time struct size sanity checks
// ============================================================
TEST(PacketStructSizeTest, LoginInfoSize) {
    EXPECT_EQ(sizeof(LoginInfo), 464u);
}

TEST(PacketStructSizeTest, EnterWorldSize) {
    EXPECT_EQ(sizeof(EnterWorld_Struct), 72u);
}

TEST(PacketStructSizeTest, ExpansionInfoSize) {
    EXPECT_EQ(sizeof(ExpansionInfo_Struct), 4u);
}

TEST(PacketStructSizeTest, NameApprovalSize) {
    // char[64] + uint32 + uint32 + uint32 = 64 + 4 + 4 + 4 = 76
    EXPECT_EQ(sizeof(NameApproval), 76u);
}

TEST(PacketStructSizeTest, BuffCountConstants) {
    EXPECT_EQ(BUFF_COUNT,       42u);
    EXPECT_EQ(PET_BUFF_COUNT,   30u);
    EXPECT_EQ(BLOCKED_BUFF_COUNT, 20u);
    EXPECT_EQ(QUESTREWARD_COUNT,  8u);
}
