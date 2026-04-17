#include <gtest/gtest.h>
#include "common/inventory_slot.h"
#include "common/textures.h"

using namespace EQ;

// ============================================================
// EQ::inventory::ConvertEquipmentIndexToTextureIndex
// ============================================================

TEST(InventoryConvertSlotToTextureTest, HeadSlotMapsToArmorHead) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotHead),
              textures::armorHead);
}

TEST(InventoryConvertSlotToTextureTest, ChestSlotMapsToArmorChest) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotChest),
              textures::armorChest);
}

TEST(InventoryConvertSlotToTextureTest, ArmsSlotMapsToArmorArms) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotArms),
              textures::armorArms);
}

TEST(InventoryConvertSlotToTextureTest, WristSlotMapsToArmorWrist) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotWrist1),
              textures::armorWrist);
}

TEST(InventoryConvertSlotToTextureTest, HandsSlotMapsToArmorHands) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotHands),
              textures::armorHands);
}

TEST(InventoryConvertSlotToTextureTest, LegsSlotMapsToArmorLegs) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotLegs),
              textures::armorLegs);
}

TEST(InventoryConvertSlotToTextureTest, FeetSlotMapsToArmorFeet) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotFeet),
              textures::armorFeet);
}

TEST(InventoryConvertSlotToTextureTest, PrimarySlotMapsToWeaponPrimary) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotPrimary),
              textures::weaponPrimary);
}

TEST(InventoryConvertSlotToTextureTest, SecondarySlotMapsToWeaponSecondary) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotSecondary),
              textures::weaponSecondary);
}

TEST(InventoryConvertSlotToTextureTest, InvalidSlotReturnsTextureInvalid) {
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(invslot::SLOT_INVALID),
              textures::materialInvalid);
}

TEST(InventoryConvertSlotToTextureTest, NonEquipmentSlotReturnsTextureInvalid) {
    // Slot 100 is not an equipment slot
    EXPECT_EQ(inventory::ConvertEquipmentIndexToTextureIndex(100),
              textures::materialInvalid);
}

// ============================================================
// EQ::inventory::ConvertTextureIndexToEquipmentIndex
// ============================================================

TEST(InventoryConvertTextureToSlotTest, ArmorHeadMapsToHeadSlot) {
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(textures::armorHead),
              invslot::slotHead);
}

TEST(InventoryConvertTextureToSlotTest, ArmorChestMapsToChestSlot) {
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(textures::armorChest),
              invslot::slotChest);
}

TEST(InventoryConvertTextureToSlotTest, ArmorArmsMapsToArmsSlot) {
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(textures::armorArms),
              invslot::slotArms);
}

TEST(InventoryConvertTextureToSlotTest, WeaponPrimaryMapsToPrimarySlot) {
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(textures::weaponPrimary),
              invslot::slotPrimary);
}

TEST(InventoryConvertTextureToSlotTest, WeaponSecondaryMapsToSecondarySlot) {
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(textures::weaponSecondary),
              invslot::slotSecondary);
}

TEST(InventoryConvertTextureToSlotTest, InvalidTextureReturnsSlotInvalid) {
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(textures::materialInvalid),
              invslot::SLOT_INVALID);
}

// ============================================================
// Roundtrip: slot → texture → slot
// ============================================================

TEST(InventoryConvertRoundtripTest, HeadRoundtrip) {
    int8 tex = inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotHead);
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(tex), invslot::slotHead);
}

TEST(InventoryConvertRoundtripTest, ChestRoundtrip) {
    int8 tex = inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotChest);
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(tex), invslot::slotChest);
}

TEST(InventoryConvertRoundtripTest, PrimaryWeaponRoundtrip) {
    int8 tex = inventory::ConvertEquipmentIndexToTextureIndex(invslot::slotPrimary);
    EXPECT_EQ(inventory::ConvertTextureIndexToEquipmentIndex(tex), invslot::slotPrimary);
}
