#include <gtest/gtest.h>
#include "common/emu_opcodes.h"

#include <cstring>

// ============================================================
// EmuOpcode enum — internal opcode list
// ============================================================

TEST(EmuOpcodeTest, UnknownIsZero) {
    EXPECT_EQ(OP_Unknown, 0);
}

TEST(EmuOpcodeTest, MaxOpcodeIsPositive) {
    EXPECT_GT(_maxEmuOpcode, 0);
}

TEST(EmuOpcodeTest, MaxOpcodeAboveKnownOpcodes) {
    // Sanity: many opcodes are defined — max should be well above 100
    EXPECT_GT(_maxEmuOpcode, 100);
}

TEST(EmuOpcodeTest, KnownOpcodesAreOrdered) {
    // emu_oplist.h entries are in ascending order after OP_Unknown
    EXPECT_GT(OP_AAAction, OP_Unknown);
    EXPECT_LT(OP_AAAction, _maxEmuOpcode);
}

TEST(EmuOpcodeTest, MaxEQOpcodeIs0xFFFF) {
    EXPECT_EQ(MAX_EQ_OPCODE, 0xFFFFu);
}

// ============================================================
// OpcodeNames[] — parallel string array for opcode names
// ============================================================

TEST(OpcodeNamesTest, IndexZeroIsOPUnknown) {
    EXPECT_STREQ(OpcodeNames[0], "OP_Unknown");
}

TEST(OpcodeNamesTest, OPUnknownIndexMatchesEnumValue) {
    EXPECT_STREQ(OpcodeNames[OP_Unknown], "OP_Unknown");
}

TEST(OpcodeNamesTest, NameAtAAActionContainsOpAAAction) {
    EXPECT_STREQ(OpcodeNames[OP_AAAction], "OP_AAAction");
}

TEST(OpcodeNamesTest, NameAtDeathIsOPDeath) {
    EXPECT_STREQ(OpcodeNames[OP_Death], "OP_Death");
}

TEST(OpcodeNamesTest, NameAtLogoutIsOPLogout) {
    EXPECT_STREQ(OpcodeNames[OP_Logout], "OP_Logout");
}

TEST(OpcodeNamesTest, NameAtPlayerProfileIsOPPlayerProfile) {
    EXPECT_STREQ(OpcodeNames[OP_PlayerProfile], "OP_PlayerProfile");
}

TEST(OpcodeNamesTest, NameAtZoneEntryIsOPZoneEntry) {
    EXPECT_STREQ(OpcodeNames[OP_ZoneEntry], "OP_ZoneEntry");
}

TEST(OpcodeNamesTest, AllNamesAreNonEmpty) {
    // Spot-check: names for first 10 opcodes are non-empty strings
    for (int i = 0; i <= 10 && i < _maxEmuOpcode; ++i) {
        EXPECT_NE(OpcodeNames[i], nullptr) << "null at index " << i;
        EXPECT_GT(strlen(OpcodeNames[i]), 0u) << "empty at index " << i;
    }
}

TEST(OpcodeNamesTest, AllNamesStartWithOP) {
    // Every opcode name should start with "OP_"
    for (int i = 0; i < _maxEmuOpcode; ++i) {
        ASSERT_NE(OpcodeNames[i], nullptr) << "null at index " << i;
        EXPECT_EQ(strncmp(OpcodeNames[i], "OP_", 3), 0)
            << "index " << i << " name: " << OpcodeNames[i];
    }
}
