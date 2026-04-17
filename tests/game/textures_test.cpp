#include <gtest/gtest.h>
#include "common/textures.h"

namespace tex = EQ::textures;

// ============================================================
// Base sentinel values
// ============================================================
TEST(TextureBaseTest, InvalidIsNegativeOne) {
    EXPECT_EQ(tex::textureInvalid, -1);
}

TEST(TextureBaseTest, BeginIsZero) {
    EXPECT_EQ(tex::textureBegin, 0);
}

// ============================================================
// TextureSlot enum values
// ============================================================
TEST(TextureSlotTest, ArmorSlotsSequential) {
    EXPECT_EQ(tex::armorHead,  0);
    EXPECT_EQ(tex::armorChest, 1);
    EXPECT_EQ(tex::armorArms,  2);
    EXPECT_EQ(tex::armorWrist, 3);
    EXPECT_EQ(tex::armorHands, 4);
    EXPECT_EQ(tex::armorLegs,  5);
    EXPECT_EQ(tex::armorFeet,  6);
}

TEST(TextureSlotTest, WeaponSlots) {
    EXPECT_EQ(tex::weaponPrimary,   7);
    EXPECT_EQ(tex::weaponSecondary, 8);
}

TEST(TextureSlotTest, MaterialCountIsNine) {
    EXPECT_EQ(tex::materialCount, 9);
}

TEST(TextureSlotTest, MaterialInvalidIsNegativeOne) {
    EXPECT_EQ(tex::materialInvalid, -1);
}

TEST(TextureSlotTest, LastTextureIsWeaponSecondary) {
    EXPECT_EQ(tex::LastTexture, tex::weaponSecondary);
}

TEST(TextureSlotTest, FormatAsReturnsInt) {
    EXPECT_EQ(tex::format_as(tex::armorHead),       0);
    EXPECT_EQ(tex::format_as(tex::weaponPrimary),   7);
    EXPECT_EQ(tex::format_as(tex::weaponSecondary), 8);
}

// ============================================================
// TintSlot enum values
// ============================================================
TEST(TintSlotTest, TintSlotsSequential) {
    EXPECT_EQ(tex::tintHead,  0);
    EXPECT_EQ(tex::tintChest, 1);
    EXPECT_EQ(tex::tintArms,  2);
    EXPECT_EQ(tex::tintWrist, 3);
    EXPECT_EQ(tex::tintHands, 4);
    EXPECT_EQ(tex::tintLegs,  5);
    EXPECT_EQ(tex::tintFeet,  6);
}

TEST(TintSlotTest, TintCountIsSeven) {
    EXPECT_EQ(tex::tintCount, 7);
}

TEST(TintSlotTest, TintInvalidIsNegativeOne) {
    EXPECT_EQ(tex::tintInvalid, -1);
}

TEST(TintSlotTest, LastTintableTextureIsTintFeet) {
    EXPECT_EQ(tex::LastTintableTexture, tex::tintFeet);
}

TEST(TintSlotTest, TintCountLessThanMaterialCount) {
    // Weapons are not tintable
    EXPECT_LT(tex::tintCount, tex::materialCount);
}

// ============================================================
// Tint_Struct union (color packing)
// ============================================================
TEST(TintStructTest, SizeIsFourBytes) {
    EXPECT_EQ(sizeof(tex::Tint_Struct), 4u);
}

TEST(TintStructTest, ColorUnionPacksRGBU) {
    tex::Tint_Struct t;
    t.Blue    = 0x11;
    t.Green   = 0x22;
    t.Red     = 0x33;
    t.UseTint = 0xFF;
    // Color should equal (UseTint << 24) | (Red << 16) | (Green << 8) | Blue
    uint32_t expected = (0xFFu << 24) | (0x33u << 16) | (0x22u << 8) | 0x11u;
    EXPECT_EQ(t.Color, expected);
}

TEST(TintStructTest, ZeroColorMeansAllZero) {
    tex::Tint_Struct t;
    t.Color = 0;
    EXPECT_EQ(t.Blue,    0u);
    EXPECT_EQ(t.Green,   0u);
    EXPECT_EQ(t.Red,     0u);
    EXPECT_EQ(t.UseTint, 0u);
}

TEST(TintStructTest, UseTintFFMeansActive) {
    tex::Tint_Struct t;
    t.Color = 0xFF000000u; // only UseTint byte set
    EXPECT_EQ(t.UseTint, 0xFFu);
    EXPECT_EQ(t.Red,   0u);
    EXPECT_EQ(t.Green, 0u);
    EXPECT_EQ(t.Blue,  0u);
}

// ============================================================
// Texture_Struct size
// ============================================================
TEST(TextureStructTest, SizeIsFiveUint32s) {
    EXPECT_EQ(sizeof(tex::Texture_Struct), 5 * sizeof(uint32_t));
}

TEST(TextureStructTest, InternalTextureStructSizeIsThreeUint32s) {
    EXPECT_EQ(sizeof(tex::InternalTexture_Struct), 3 * sizeof(uint32_t));
}

// ============================================================
// TextureProfile slot array
// ============================================================
TEST(TextureProfileTest, SlotArraySizeMatchesMaterialCount) {
    EQ::TextureProfile profile;
    // materialCount slots in the union array
    EXPECT_EQ(sizeof(profile.Slot) / sizeof(profile.Slot[0]),
              static_cast<size_t>(tex::materialCount));
}

TEST(TextureProfileTest, NamedSlotsMatchArray) {
    EQ::TextureProfile profile;
    profile.Head.Material = 42;
    EXPECT_EQ(profile.Slot[tex::armorHead].Material, 42u);

    profile.Primary.Material = 99;
    EXPECT_EQ(profile.Slot[tex::weaponPrimary].Material, 99u);
}

// ============================================================
// TintProfile slot array
// ============================================================
TEST(TintProfileTest, SlotArraySizeMatchesMaterialCount) {
    EQ::TintProfile profile;
    EXPECT_EQ(sizeof(profile.Slot) / sizeof(profile.Slot[0]),
              static_cast<size_t>(tex::materialCount));
}

TEST(TintProfileTest, NamedTintSlotsMatchArray) {
    EQ::TintProfile profile;
    profile.Head.Color = 0xDEADBEEFu;
    EXPECT_EQ(profile.Slot[tex::armorHead].Color, 0xDEADBEEFu);
}
