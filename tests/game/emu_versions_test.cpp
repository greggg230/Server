#include <gtest/gtest.h>
#include "common/emu_versions.h"

namespace cv = EQ::versions;
namespace exp = EQ::expansions;

// ============================================================
// EQ::versions::IsValidClientVersion
// ============================================================
TEST(ClientVersionTest, IsValidKnownVersions) {
    EXPECT_TRUE(cv::IsValidClientVersion(cv::ClientVersion::Titanium));
    EXPECT_TRUE(cv::IsValidClientVersion(cv::ClientVersion::SoF));
    EXPECT_TRUE(cv::IsValidClientVersion(cv::ClientVersion::SoD));
    EXPECT_TRUE(cv::IsValidClientVersion(cv::ClientVersion::UF));
    EXPECT_TRUE(cv::IsValidClientVersion(cv::ClientVersion::RoF));
    EXPECT_TRUE(cv::IsValidClientVersion(cv::ClientVersion::RoF2));
}

TEST(ClientVersionTest, IsValidUnknownAndOutOfRange) {
    EXPECT_FALSE(cv::IsValidClientVersion(cv::ClientVersion::Unknown));
    EXPECT_FALSE(cv::IsValidClientVersion(static_cast<cv::ClientVersion>(999)));
}

// ============================================================
// EQ::versions::ValidateClientVersion
// ============================================================
TEST(ClientVersionTest, ValidateKnownVersionsReturnsSelf) {
    EXPECT_EQ(cv::ValidateClientVersion(cv::ClientVersion::Titanium), cv::ClientVersion::Titanium);
    EXPECT_EQ(cv::ValidateClientVersion(cv::ClientVersion::SoF),      cv::ClientVersion::SoF);
    EXPECT_EQ(cv::ValidateClientVersion(cv::ClientVersion::RoF2),     cv::ClientVersion::RoF2);
}

TEST(ClientVersionTest, ValidateUnknownReturnsUnknown) {
    EXPECT_EQ(cv::ValidateClientVersion(cv::ClientVersion::Unknown), cv::ClientVersion::Unknown);
    EXPECT_EQ(cv::ValidateClientVersion(static_cast<cv::ClientVersion>(999)), cv::ClientVersion::Unknown);
}

// ============================================================
// EQ::versions::ClientVersionName
// ============================================================
TEST(ClientVersionTest, NameKnownVersions) {
    EXPECT_STREQ(cv::ClientVersionName(cv::ClientVersion::Unknown),  "Unknown Version");
    EXPECT_STREQ(cv::ClientVersionName(cv::ClientVersion::Titanium), "Titanium");
    EXPECT_STREQ(cv::ClientVersionName(cv::ClientVersion::SoF),      "SoF");
    EXPECT_STREQ(cv::ClientVersionName(cv::ClientVersion::SoD),      "SoD");
    EXPECT_STREQ(cv::ClientVersionName(cv::ClientVersion::UF),       "UF");
    EXPECT_STREQ(cv::ClientVersionName(cv::ClientVersion::RoF),      "RoF");
    EXPECT_STREQ(cv::ClientVersionName(cv::ClientVersion::RoF2),     "RoF2");
}

TEST(ClientVersionTest, NameOutOfRangeReturnsInvalid) {
    EXPECT_STREQ(cv::ClientVersionName(static_cast<cv::ClientVersion>(999)), "Invalid Version");
}

// ============================================================
// ConvertClientVersionToClientVersionBit / back
// ============================================================
TEST(ClientVersionTest, ConvertToVersionBit) {
    EXPECT_EQ(cv::ConvertClientVersionToClientVersionBit(cv::ClientVersion::Titanium), (uint32)cv::bitTitanium);
    EXPECT_EQ(cv::ConvertClientVersionToClientVersionBit(cv::ClientVersion::SoD),      (uint32)cv::bitSoD);
    EXPECT_EQ(cv::ConvertClientVersionToClientVersionBit(cv::ClientVersion::UF),       (uint32)cv::bitUF);
    EXPECT_EQ(cv::ConvertClientVersionToClientVersionBit(cv::ClientVersion::RoF),      (uint32)cv::bitRoF);
    EXPECT_EQ(cv::ConvertClientVersionToClientVersionBit(cv::ClientVersion::RoF2),     (uint32)cv::bitRoF2);
}

TEST(ClientVersionTest, ConvertUnknownVersionToUnknownBit) {
    EXPECT_EQ(cv::ConvertClientVersionToClientVersionBit(cv::ClientVersion::Unknown), (uint32)cv::bitUnknown);
}

TEST(ClientVersionTest, ConvertBitToVersionRoundTrip) {
    const cv::ClientVersion versions[] = {
        cv::ClientVersion::Titanium, cv::ClientVersion::SoD,
        cv::ClientVersion::UF, cv::ClientVersion::RoF, cv::ClientVersion::RoF2
    };
    for (auto v : versions) {
        uint32 bit = cv::ConvertClientVersionToClientVersionBit(v);
        EXPECT_EQ(cv::ConvertClientVersionBitToClientVersion(bit), v);
    }
}

TEST(ClientVersionTest, ConvertUnknownBitToUnknownVersion) {
    EXPECT_EQ(cv::ConvertClientVersionBitToClientVersion(cv::bitUnknown), cv::ClientVersion::Unknown);
    EXPECT_EQ(cv::ConvertClientVersionBitToClientVersion(0xDEADBEEFu),   cv::ClientVersion::Unknown);
}

// ============================================================
// EQ::versions::IsValidMobVersion
// ============================================================
TEST(MobVersionTest, IsValidKnownMobVersions) {
    EXPECT_TRUE(cv::IsValidMobVersion(cv::MobVersion::Titanium));
    EXPECT_TRUE(cv::IsValidMobVersion(cv::MobVersion::RoF2));
    EXPECT_TRUE(cv::IsValidMobVersion(cv::MobVersion::NPC));
    EXPECT_TRUE(cv::IsValidMobVersion(cv::MobVersion::Bot));
    EXPECT_TRUE(cv::IsValidMobVersion(cv::MobVersion::OfflineRoF2));
}

TEST(MobVersionTest, IsValidUnknownMobVersion) {
    EXPECT_FALSE(cv::IsValidMobVersion(cv::MobVersion::Unknown));
    EXPECT_FALSE(cv::IsValidMobVersion(static_cast<cv::MobVersion>(999)));
}

TEST(MobVersionTest, IsValidPCMobVersion) {
    EXPECT_TRUE(cv::IsValidPCMobVersion(cv::MobVersion::Titanium));
    EXPECT_TRUE(cv::IsValidPCMobVersion(cv::MobVersion::RoF2));
    EXPECT_FALSE(cv::IsValidPCMobVersion(cv::MobVersion::Unknown));
    EXPECT_FALSE(cv::IsValidPCMobVersion(cv::MobVersion::NPC));
}

TEST(MobVersionTest, IsValidNonPCMobVersion) {
    EXPECT_TRUE(cv::IsValidNonPCMobVersion(cv::MobVersion::NPC));
    EXPECT_TRUE(cv::IsValidNonPCMobVersion(cv::MobVersion::Bot));
    EXPECT_FALSE(cv::IsValidNonPCMobVersion(cv::MobVersion::RoF2));
    EXPECT_FALSE(cv::IsValidNonPCMobVersion(cv::MobVersion::Unknown));
}

// ============================================================
// EQ::expansions::ExpansionName
// ============================================================
TEST(ExpansionTest, NameKnownExpansions) {
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::EverQuest), "EverQuest");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::RoK),       "The Ruins of Kunark");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::SoV),       "The Scars of Velious");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::SoL),       "The Shadows of Luclin");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::PoP),       "The Planes of Power");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::LDoN),      "Lost Dungeons of Norrath");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::GoD),       "Gates of Discord");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::OoW),       "Omens of War");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::TSS),       "The Serpent's Spine");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::UF),        "Underfoot");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::VoA),       "Veil of Alaris");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::RoF),       "Rain of Fear");
    EXPECT_STREQ(exp::ExpansionName(exp::Expansion::CotF),      "Call of the Forsaken");
}

TEST(ExpansionTest, NameOutOfRangeReturnsInvalid) {
    EXPECT_STREQ(exp::ExpansionName(static_cast<exp::Expansion>(999)), "Invalid Expansion");
}

// ============================================================
// ConvertExpansionToExpansionBit / back
// ============================================================
TEST(ExpansionTest, ConvertToExpansionBit) {
    EXPECT_EQ(exp::ConvertExpansionToExpansionBit(exp::Expansion::RoK),  (uint32)exp::bitRoK);
    EXPECT_EQ(exp::ConvertExpansionToExpansionBit(exp::Expansion::PoP),  (uint32)exp::bitPoP);
    EXPECT_EQ(exp::ConvertExpansionToExpansionBit(exp::Expansion::CotF), (uint32)exp::bitCotF);
}

TEST(ExpansionTest, ConvertBitToExpansionRoundTrip) {
    const exp::Expansion exps[] = {
        exp::Expansion::RoK, exp::Expansion::SoV, exp::Expansion::PoP, exp::Expansion::LDoN,
        exp::Expansion::GoD, exp::Expansion::OoW, exp::Expansion::TSS,
        exp::Expansion::SoD, exp::Expansion::UF,  exp::Expansion::HoT, exp::Expansion::VoA,
        exp::Expansion::RoF, exp::Expansion::CotF
    };
    for (auto e : exps) {
        uint32 bit = exp::ConvertExpansionToExpansionBit(e);
        EXPECT_EQ(exp::ConvertExpansionBitToExpansion(bit), e) << "Round-trip failed for expansion " << (int)e;
    }
}

// ============================================================
// ConvertExpansionToExpansionsMask (cumulative bitmask)
// ============================================================
TEST(ExpansionTest, MaskEverQuestIsZero) {
    EXPECT_EQ(exp::ConvertExpansionToExpansionsMask(exp::Expansion::EverQuest), (uint32)exp::maskEverQuest);
}

TEST(ExpansionTest, MaskRoKIncludesRoKBit) {
    uint32 mask = exp::ConvertExpansionToExpansionsMask(exp::Expansion::RoK);
    EXPECT_EQ(mask, (uint32)exp::maskRoK);
    EXPECT_NE(mask & exp::bitRoK, 0u);
}

TEST(ExpansionTest, MaskPoPIncludesAllPriorBits) {
    uint32 mask = exp::ConvertExpansionToExpansionsMask(exp::Expansion::PoP);
    EXPECT_NE(mask & exp::bitRoK, 0u);
    EXPECT_NE(mask & exp::bitSoV, 0u);
    EXPECT_NE(mask & exp::bitSoL, 0u);
    EXPECT_NE(mask & exp::bitPoP, 0u);
}

// ============================================================
// ExpansionName from bit (overload)
// ============================================================
TEST(ExpansionTest, NameFromBitMatchesNameFromEnum) {
    EXPECT_STREQ(exp::ExpansionName(exp::bitRoK),  exp::ExpansionName(exp::Expansion::RoK));
    EXPECT_STREQ(exp::ExpansionName(exp::bitPoP),  exp::ExpansionName(exp::Expansion::PoP));
    EXPECT_STREQ(exp::ExpansionName(exp::bitCotF), exp::ExpansionName(exp::Expansion::CotF));
}
