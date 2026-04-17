#include <gtest/gtest.h>
#include "common/emu_constants.h"
#include "common/eq_constants.h"

// ============================================================
// PetType::GetName / IsValid
// ============================================================
TEST(PetTypeTest, IsValidKnownTypes) {
    EXPECT_TRUE(PetType::IsValid(PetType::Familiar));
    EXPECT_TRUE(PetType::IsValid(PetType::Animation));
    EXPECT_TRUE(PetType::IsValid(PetType::Normal));
    EXPECT_TRUE(PetType::IsValid(PetType::Charmed));
    EXPECT_TRUE(PetType::IsValid(PetType::Follow));
    EXPECT_TRUE(PetType::IsValid(PetType::TargetLock));
    EXPECT_TRUE(PetType::IsValid(PetType::None));
}

TEST(PetTypeTest, IsValidUnknownType) {
    EXPECT_FALSE(PetType::IsValid(50));
    EXPECT_FALSE(PetType::IsValid(100));
}

TEST(PetTypeTest, GetNameKnownTypes) {
    EXPECT_EQ(PetType::GetName(PetType::Familiar),   "Familiar");
    EXPECT_EQ(PetType::GetName(PetType::Animation),  "Animation");
    EXPECT_EQ(PetType::GetName(PetType::Normal),     "Normal");
    EXPECT_EQ(PetType::GetName(PetType::Charmed),    "Charmed");
    EXPECT_EQ(PetType::GetName(PetType::Follow),     "Follow");
    EXPECT_EQ(PetType::GetName(PetType::TargetLock), "Target Lock");
    EXPECT_EQ(PetType::GetName(PetType::None),       "None");
}

TEST(PetTypeTest, GetNameUnknownReturnsDefault) {
    EXPECT_EQ(PetType::GetName(50), "UNKNOWN PET TYPE");
}

// ============================================================
// Bug::GetID (reverse lookup)
// ============================================================
TEST(BugGetIDTest, KnownCategoryNamesReturnID) {
    EXPECT_EQ(Bug::GetID("Other"),         static_cast<uint32>(Bug::Category::Other));
    EXPECT_EQ(Bug::GetID("Video"),         static_cast<uint32>(Bug::Category::Video));
    EXPECT_EQ(Bug::GetID("Audio"),         static_cast<uint32>(Bug::Category::Audio));
    EXPECT_EQ(Bug::GetID("Pathing"),       static_cast<uint32>(Bug::Category::Pathing));
    EXPECT_EQ(Bug::GetID("Quest"),         static_cast<uint32>(Bug::Category::Quest));
    EXPECT_EQ(Bug::GetID("Tradeskills"),   static_cast<uint32>(Bug::Category::Tradeskills));
    EXPECT_EQ(Bug::GetID("Spell Stacking"),static_cast<uint32>(Bug::Category::SpellStacking));
    EXPECT_EQ(Bug::GetID("NPC"),           static_cast<uint32>(Bug::Category::NPC));
    EXPECT_EQ(Bug::GetID("Mercenaries"),   static_cast<uint32>(Bug::Category::Mercenaries));
}

TEST(BugGetIDTest, UnknownNameReturnsOther) {
    // Falls back to Bug::Category::Other for unknown names
    EXPECT_EQ(Bug::GetID("NotACategory"), static_cast<uint32>(Bug::Category::Other));
    EXPECT_EQ(Bug::GetID(""),             static_cast<uint32>(Bug::Category::Other));
}

TEST(BugGetIDTest, RoundTrip) {
    // GetName(GetID(name)) == name for known categories
    const std::vector<std::string> names = {"Other", "Video", "Audio", "Quest", "NPC", "Tradeskills", "Mercenaries"};
    for (const auto& name : names) {
        uint32 id = Bug::GetID(name);
        EXPECT_EQ(Bug::GetName(id), name) << "Round-trip failed for: " << name;
    }
}

// ============================================================
// Stance::GetIndex
// ============================================================
TEST(StanceGetIndexTest, PassiveIsBaseIndex) {
    // Passive is the first stance (index 0 relative to itself)
    EXPECT_EQ(Stance::GetIndex(Stance::Passive), 0u);
}

TEST(StanceGetIndexTest, OtherStancesAreOffsetFromPassive) {
    // GetIndex returns stance_id - Passive
    EXPECT_EQ(Stance::GetIndex(Stance::Balanced),   Stance::Balanced   - Stance::Passive);
    EXPECT_EQ(Stance::GetIndex(Stance::Aggressive), Stance::Aggressive - Stance::Passive);
    EXPECT_EQ(Stance::GetIndex(Stance::Burn),       Stance::Burn       - Stance::Passive);
    EXPECT_EQ(Stance::GetIndex(Stance::AEBurn),     Stance::AEBurn     - Stance::Passive);
}

TEST(StanceGetIndexTest, InvalidStanceReturnsZero) {
    // Only truly invalid (not-in-map) stances return 0
    EXPECT_EQ(Stance::GetIndex(100), 0u);
    EXPECT_EQ(Stance::GetIndex(50),  0u);
}

// ============================================================
// EQ::constants::GetAppearanceTypeName
// ============================================================
TEST(AppearanceTypeNameTest, KnownTypes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Die),          "Die");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::WhoLevel),     "Who Level");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::MaxHealth),    "Max Health");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Invisibility), "Invisibility");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::PVP),          "PVP");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Light),        "Light");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Animation),    "Animation");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Sneak),        "Sneak");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::SpawnID),      "Spawn ID");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Health),       "Health");
}

TEST(AppearanceTypeNameTest, MoreKnownTypes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Linkdead),   "Linkdead");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::FlyMode),    "Fly Mode");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::GM),         "GM");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Anonymous),  "Anonymous");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::GuildID),    "Guild ID");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::GuildRank),  "Guild Rank");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::AFK),        "AFK");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Pet),        "Pet");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Summoned),   "Summoned");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Split),      "Split");
}

TEST(AppearanceTypeNameTest, EvenMoreKnownTypes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::Size),          "Size");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::SetType),       "Set Type");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::NPCName),       "NPCName");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::AARank),        "AARank");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::ShowHelm),      "Show Helm");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::DamageState),   "Damage State");
    EXPECT_EQ(GetAppearanceTypeName(AppearanceType::OfflineMode),   "Offline Mode");
}

TEST(AppearanceTypeNameTest, UnknownTypeReturnsEmpty) {
    EXPECT_EQ(EQ::constants::GetAppearanceTypeName(9999u), "");
    EXPECT_EQ(EQ::constants::GetAppearanceTypeName(500u),  "");
}
