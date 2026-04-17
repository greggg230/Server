#include <gtest/gtest.h>
#include "common/inventory_slot.h"
#include "common/emu_constants.h"

using namespace EQ;

// ============================================================
// InventorySlot constructors and accessors
// ============================================================
TEST(InventorySlotTest, DefaultConstructorAllInvalid) {
    InventorySlot s;
    EXPECT_EQ(s.TypeIndex(), invtype::TYPE_INVALID);
    EXPECT_EQ(s.SlotIndex(), invslot::SLOT_INVALID);
    EXPECT_EQ(s.ContainerIndex(), invbag::SLOT_INVALID);
    EXPECT_EQ(s.SocketIndex(), invaug::SOCKET_INVALID);
    EXPECT_FALSE(s.Typeless());
}

TEST(InventorySlotTest, TypeOnlyConstructor) {
    InventorySlot s(invtype::typePossessions);
    EXPECT_EQ(s.TypeIndex(), invtype::typePossessions);
    EXPECT_EQ(s.SlotIndex(), invslot::SLOT_INVALID);
    EXPECT_EQ(s.ContainerIndex(), invbag::SLOT_INVALID);
    EXPECT_EQ(s.SocketIndex(), invaug::SOCKET_INVALID);
}

TEST(InventorySlotTest, TypeAndSlotConstructor) {
    InventorySlot s(invtype::typePossessions, invslot::slotHead);
    EXPECT_EQ(s.TypeIndex(), invtype::typePossessions);
    EXPECT_EQ(s.SlotIndex(), invslot::slotHead);
    EXPECT_EQ(s.ContainerIndex(), invbag::SLOT_INVALID);
}

TEST(InventorySlotTest, TypeSlotContainerConstructor) {
    InventorySlot s(invtype::typePossessions, invslot::slotGeneral1, 0);
    EXPECT_EQ(s.TypeIndex(), invtype::typePossessions);
    EXPECT_EQ(s.SlotIndex(), invslot::slotGeneral1);
    EXPECT_EQ(s.ContainerIndex(), 0);
}

TEST(InventorySlotTest, FullConstructor) {
    InventorySlot s(invtype::typePossessions, invslot::slotGeneral1, 0, 0);
    EXPECT_EQ(s.TypeIndex(), invtype::typePossessions);
    EXPECT_EQ(s.SlotIndex(), invslot::slotGeneral1);
    EXPECT_EQ(s.ContainerIndex(), 0);
    EXPECT_EQ(s.SocketIndex(), 0);
}

TEST(InventorySlotTest, CopyConstructor) {
    InventorySlot orig(invtype::typePossessions, invslot::slotHead);
    InventorySlot copy(orig);
    EXPECT_EQ(copy.TypeIndex(), invtype::typePossessions);
    EXPECT_EQ(copy.SlotIndex(), invslot::slotHead);
}

TEST(InventorySlotTest, Setters) {
    InventorySlot s;
    s.SetType(invtype::typePossessions);
    s.SetSlot(invslot::slotPrimary);
    s.SetContainer(0);
    s.SetSocket(1);
    EXPECT_EQ(s.TypeIndex(), invtype::typePossessions);
    EXPECT_EQ(s.SlotIndex(), invslot::slotPrimary);
    EXPECT_EQ(s.ContainerIndex(), 0);
    EXPECT_EQ(s.SocketIndex(), 1);
}

TEST(InventorySlotTest, InvalidateSetters) {
    InventorySlot s(invtype::typePossessions, invslot::slotHead, 0, 0);
    s.SetTypeInvalid();
    s.SetSlotInvalid();
    s.SetContainerInvalid();
    s.SetSocketInvalid();
    EXPECT_EQ(s.TypeIndex(), invtype::TYPE_INVALID);
    EXPECT_EQ(s.SlotIndex(), invslot::SLOT_INVALID);
    EXPECT_EQ(s.ContainerIndex(), invbag::SLOT_INVALID);
    EXPECT_EQ(s.SocketIndex(), invaug::SOCKET_INVALID);
}

// ============================================================
// Static slot category checks
// ============================================================
TEST(InventorySlotIndexTest, EquipmentIndexBeginAndEnd) {
    EXPECT_TRUE(InventorySlot::IsEquipmentIndex(invslot::EQUIPMENT_BEGIN));
    EXPECT_TRUE(InventorySlot::IsEquipmentIndex(invslot::EQUIPMENT_END));
}

TEST(InventorySlotIndexTest, EquipmentIndexCommonSlots) {
    EXPECT_TRUE(InventorySlot::IsEquipmentIndex(invslot::slotHead));
    EXPECT_TRUE(InventorySlot::IsEquipmentIndex(invslot::slotChest));
    EXPECT_TRUE(InventorySlot::IsEquipmentIndex(invslot::slotPrimary));
    EXPECT_TRUE(InventorySlot::IsEquipmentIndex(invslot::slotSecondary));
}

TEST(InventorySlotIndexTest, EquipmentIndexGeneralSlotsFalse) {
    EXPECT_FALSE(InventorySlot::IsEquipmentIndex(invslot::slotGeneral1));
    EXPECT_FALSE(InventorySlot::IsEquipmentIndex(invslot::slotCursor));
}

TEST(InventorySlotIndexTest, GeneralIndexCommonSlots) {
    EXPECT_TRUE(InventorySlot::IsGeneralIndex(invslot::GENERAL_BEGIN));
    EXPECT_TRUE(InventorySlot::IsGeneralIndex(invslot::GENERAL_END));
    EXPECT_TRUE(InventorySlot::IsGeneralIndex(invslot::slotGeneral1));
}

TEST(InventorySlotIndexTest, GeneralIndexEquipmentFalse) {
    EXPECT_FALSE(InventorySlot::IsGeneralIndex(invslot::slotHead));
    EXPECT_FALSE(InventorySlot::IsGeneralIndex(invslot::slotCursor));
}

TEST(InventorySlotIndexTest, CursorIndex) {
    EXPECT_TRUE(InventorySlot::IsCursorIndex(invslot::slotCursor));
    EXPECT_FALSE(InventorySlot::IsCursorIndex(invslot::slotHead));
    EXPECT_FALSE(InventorySlot::IsCursorIndex(invslot::slotGeneral1));
}

TEST(InventorySlotIndexTest, WeaponIndex) {
    EXPECT_TRUE(InventorySlot::IsWeaponIndex(invslot::slotPrimary));
    EXPECT_TRUE(InventorySlot::IsWeaponIndex(invslot::slotSecondary));
    EXPECT_TRUE(InventorySlot::IsWeaponIndex(invslot::slotRange));
    EXPECT_FALSE(InventorySlot::IsWeaponIndex(invslot::slotHead));
    EXPECT_FALSE(InventorySlot::IsWeaponIndex(invslot::slotGeneral1));
}

TEST(InventorySlotIndexTest, TextureIndex) {
    EXPECT_TRUE(InventorySlot::IsTextureIndex(invslot::slotHead));
    EXPECT_TRUE(InventorySlot::IsTextureIndex(invslot::slotChest));
    EXPECT_TRUE(InventorySlot::IsTextureIndex(invslot::slotArms));
    EXPECT_TRUE(InventorySlot::IsTextureIndex(invslot::slotPrimary));
    EXPECT_TRUE(InventorySlot::IsTextureIndex(invslot::slotSecondary));
    EXPECT_FALSE(InventorySlot::IsTextureIndex(invslot::slotGeneral1));
    EXPECT_FALSE(InventorySlot::IsTextureIndex(invslot::slotCursor));
}

TEST(InventorySlotIndexTest, TintableIndex) {
    EXPECT_TRUE(InventorySlot::IsTintableIndex(invslot::slotHead));
    EXPECT_TRUE(InventorySlot::IsTintableIndex(invslot::slotChest));
    EXPECT_TRUE(InventorySlot::IsTintableIndex(invslot::slotFeet));
    EXPECT_FALSE(InventorySlot::IsTintableIndex(invslot::slotPrimary));   // weapons not tintable
    EXPECT_FALSE(InventorySlot::IsTintableIndex(invslot::slotSecondary)); // weapons not tintable
    EXPECT_FALSE(InventorySlot::IsTintableIndex(invslot::slotGeneral1));
}

// ============================================================
// AccountStatus
// ============================================================
TEST(AccountStatusTest, PlayerName) {
    EXPECT_EQ(AccountStatus::GetName(AccountStatus::Player), "Player");
}

TEST(AccountStatusTest, GMAdminName) {
    EXPECT_EQ(AccountStatus::GetName(AccountStatus::GMAdmin), "GM Admin");
}

TEST(AccountStatusTest, MaxName) {
    EXPECT_EQ(AccountStatus::GetName(AccountStatus::Max), "GM Max");
}

TEST(AccountStatusTest, BetweenTwoLevelsReturnsLower) {
    // Status 11 is between Player(0) and Steward(10) — actually above Steward
    EXPECT_EQ(AccountStatus::GetName(11), "Steward");
}

// ============================================================
// ComparisonType
// ============================================================
TEST(ComparisonTypeTest, IsValidKnownTypes) {
    EXPECT_TRUE(ComparisonType::IsValid(ComparisonType::Equal));
    EXPECT_TRUE(ComparisonType::IsValid(ComparisonType::NotEqual));
    EXPECT_TRUE(ComparisonType::IsValid(ComparisonType::Between));
    EXPECT_TRUE(ComparisonType::IsValid(ComparisonType::NotBetween));
}

TEST(ComparisonTypeTest, IsValidUnknownType) {
    EXPECT_FALSE(ComparisonType::IsValid(200));
}

TEST(ComparisonTypeTest, GetNameKnownTypes) {
    EXPECT_EQ(ComparisonType::GetName(ComparisonType::Equal), "Equal");
    EXPECT_EQ(ComparisonType::GetName(ComparisonType::NotEqual), "Not Equal");
    EXPECT_EQ(ComparisonType::GetName(ComparisonType::GreaterOrEqual), "Greater or Equal");
    EXPECT_EQ(ComparisonType::GetName(ComparisonType::Between), "Between");
}

TEST(ComparisonTypeTest, GetNameUnknownType) {
    EXPECT_EQ(ComparisonType::GetName(200), "UNKNOWN COMPARISON TYPE");
}
