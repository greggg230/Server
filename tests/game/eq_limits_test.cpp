#include <gtest/gtest.h>
#include "common/eq_limits.h"

// ============================================================
// EQ::constants::StaticLookup — per-client-version limits
// These are compile-time static tables (no InitializeDynamicLookups needed).
// ============================================================

namespace cv = EQ::versions;

TEST(EQLimitsStaticTest, TitaniumCharacterCreationLimitIs8) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::Titanium);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->CharacterCreationLimit, 8);
}

TEST(EQLimitsStaticTest, TitaniumSayLinkBodySizeIs45) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::Titanium);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->SayLinkBodySize, 45u);
}

TEST(EQLimitsStaticTest, SoFCharacterCreationLimitIs12) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::SoF);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->CharacterCreationLimit, 12);
}

TEST(EQLimitsStaticTest, SoFSayLinkBodySizeIs50) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::SoF);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->SayLinkBodySize, 50u);
}

TEST(EQLimitsStaticTest, SoDSayLinkBodySizeIs50) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::SoD);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->SayLinkBodySize, 50u);
}

TEST(EQLimitsStaticTest, UFSayLinkBodySizeIs50) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::UF);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->SayLinkBodySize, 50u);
}

TEST(EQLimitsStaticTest, RoFSayLinkBodySizeIs55) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::RoF);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->SayLinkBodySize, 55u);
}

TEST(EQLimitsStaticTest, RoF2CharacterCreationLimitIs12) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::RoF2);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->CharacterCreationLimit, 12);
}

TEST(EQLimitsStaticTest, RoF2SayLinkBodySizeIs56) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::RoF2);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->SayLinkBodySize, 56u);
}

TEST(EQLimitsStaticTest, SayLinkBodySizeIncreasesWithVersion) {
    const auto* titan = EQ::constants::StaticLookup(cv::ClientVersion::Titanium);
    const auto* rof2  = EQ::constants::StaticLookup(cv::ClientVersion::RoF2);
    ASSERT_NE(titan, nullptr);
    ASSERT_NE(rof2,  nullptr);
    EXPECT_LT(titan->SayLinkBodySize, rof2->SayLinkBodySize);
}

TEST(EQLimitsStaticTest, UnknownVersionReturnsValidPointer) {
    const auto* e = EQ::constants::StaticLookup(cv::ClientVersion::Unknown);
    EXPECT_NE(e, nullptr);
}

// ============================================================
// EQ::InitializeDynamicLookups — must be idempotent
// ============================================================
TEST(EQLimitsInitTest, InitializeIsIdempotent) {
    EXPECT_NO_THROW({
        EQ::InitializeDynamicLookups();
        EQ::InitializeDynamicLookups();
        EQ::InitializeDynamicLookups();
    });
}

TEST(EQLimitsDynamicTest, DynamicLookupAfterInitReturnsNonNull) {
    EQ::InitializeDynamicLookups();
    const auto* e = EQ::constants::DynamicNonGMLookup(cv::ClientVersion::RoF2);
    EXPECT_NE(e, nullptr);
}

TEST(EQLimitsDynamicTest, DynamicLookupSayLinkMatchesStatic) {
    EQ::InitializeDynamicLookups();
    const auto* dyn    = EQ::constants::DynamicNonGMLookup(cv::ClientVersion::RoF2);
    const auto* static_ = EQ::constants::StaticLookup(cv::ClientVersion::RoF2);
    ASSERT_NE(dyn,    nullptr);
    ASSERT_NE(static_, nullptr);
    EXPECT_EQ(dyn->SayLinkBodySize, static_->SayLinkBodySize);
}
