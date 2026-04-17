#include <gtest/gtest.h>
#include "common/server_reload_types.h"
#include "common/ptimer.h"

// ============================================================
// ServerReload::GetName
// ============================================================
TEST(ServerReloadGetNameTest, NoneReturnsNone) {
    EXPECT_EQ(ServerReload::GetName(ServerReload::ReloadTypeNone), "None");
}

TEST(ServerReloadGetNameTest, KnownTypesReturnNames) {
    EXPECT_EQ(ServerReload::GetName(ServerReload::AAData),             "AA Data");
    EXPECT_EQ(ServerReload::GetName(ServerReload::Loot),               "Loot");
    EXPECT_EQ(ServerReload::GetName(ServerReload::Rules),              "Rules");
    EXPECT_EQ(ServerReload::GetName(ServerReload::Quests),             "Quest");
    EXPECT_EQ(ServerReload::GetName(ServerReload::Tasks),              "Tasks");
    EXPECT_EQ(ServerReload::GetName(ServerReload::Commands),           "Commands");
    EXPECT_EQ(ServerReload::GetName(ServerReload::Logs),               "Logs");
}

TEST(ServerReloadGetNameTest, OutOfRangeReturnsUnknown) {
    EXPECT_EQ(ServerReload::GetName(-1),  "Unknown");
    EXPECT_EQ(ServerReload::GetName(999), "Unknown");
    EXPECT_EQ(ServerReload::GetName(ServerReload::Type::Max), "Unknown");
}

TEST(ServerReloadGetNameTest, MaxEnumIs36) {
    EXPECT_EQ(ServerReload::Type::Max, 36);
}

// ============================================================
// ServerReload::GetNameClean
// ============================================================
TEST(ServerReloadGetNameCleanTest, NoneReturnsNone) {
    EXPECT_EQ(ServerReload::GetNameClean(ServerReload::ReloadTypeNone), "None");
}

TEST(ServerReloadGetNameCleanTest, NoParenthesesUnchanged) {
    EXPECT_EQ(ServerReload::GetNameClean(ServerReload::Loot),    "Loot");
    EXPECT_EQ(ServerReload::GetNameClean(ServerReload::Rules),   "Rules");
    EXPECT_EQ(ServerReload::GetNameClean(ServerReload::Tasks),   "Tasks");
}

TEST(ServerReloadGetNameCleanTest, ParenthesesStripped) {
    // QuestsTimerReset has "(Resets timer events)" in its name
    std::string clean = ServerReload::GetNameClean(ServerReload::QuestsTimerReset);
    EXPECT_EQ(clean.find('('), std::string::npos);
    EXPECT_FALSE(clean.empty());
}

TEST(ServerReloadGetNameCleanTest, OutOfRangeReturnsUnknown) {
    EXPECT_EQ(ServerReload::GetNameClean(-1),  "Unknown");
    EXPECT_EQ(ServerReload::GetNameClean(999), "Unknown");
}

// ============================================================
// ServerReload::GetTypes
// ============================================================
TEST(ServerReloadGetTypesTest, ReturnsNonEmptyVector) {
    auto types = ServerReload::GetTypes();
    EXPECT_FALSE(types.empty());
}

TEST(ServerReloadGetTypesTest, DoesNotIncludeNone) {
    auto types = ServerReload::GetTypes();
    for (auto t : types) {
        EXPECT_NE(t, ServerReload::ReloadTypeNone);
    }
}

TEST(ServerReloadGetTypesTest, DoesNotIncludeMax) {
    auto types = ServerReload::GetTypes();
    for (auto t : types) {
        EXPECT_LT(static_cast<int>(t), ServerReload::Type::Max);
    }
}

TEST(ServerReloadGetTypesTest, SizeIsMaxMinusOne) {
    auto types = ServerReload::GetTypes();
    EXPECT_EQ(types.size(), static_cast<size_t>(ServerReload::Type::Max - 1));
}

TEST(ServerReloadGetTypesTest, AllTypesHaveNonEmptyNames) {
    auto types = ServerReload::GetTypes();
    for (auto t : types) {
        EXPECT_FALSE(ServerReload::GetName(t).empty()) << "Type " << t << " has empty name";
    }
}

// ============================================================
// ptimer enum values
// ============================================================
TEST(PTimerTest, NegativeItemReuseIsNegativeOne) {
    EXPECT_EQ(pTimerNegativeItemReuse, -1);
}

TEST(PTimerTest, EarlyTimerValues) {
    EXPECT_EQ(pTimerStartAdventureTimer, 1);
    EXPECT_EQ(pTimerSurnameChange,       2);
    EXPECT_EQ(pTimerFeignDeath,          3);
    EXPECT_EQ(pTimerSneak,              4);
    EXPECT_EQ(pTimerHide,               5);
    EXPECT_EQ(pTimerTaunt,              6);
}

TEST(PTimerTest, SkillTimerValues) {
    EXPECT_EQ(pTimerFishing,         8);
    EXPECT_EQ(pTimerForaging,        9);
    EXPECT_EQ(pTimerMend,            10);
    EXPECT_EQ(pTimerTracking,        11);
    EXPECT_EQ(pTimerSenseTraps,      12);
    EXPECT_EQ(pTimerDisarmTraps,     13);
}

TEST(PTimerTest, DisciplineRangeValues) {
    EXPECT_EQ(pTimerDisciplineReuseStart, 14);
    EXPECT_EQ(pTimerDisciplineReuseEnd,   24);
    EXPECT_GT(pTimerDisciplineReuseEnd,   pTimerDisciplineReuseStart);
}

TEST(PTimerTest, ClientSyncedTimers) {
    // These are IDs also used by the client — must not change
    EXPECT_EQ(pTimerLayHands,   87);
    EXPECT_EQ(pTimerHarmTouch,  89);
}

TEST(PTimerTest, ItemTimerRange) {
    EXPECT_EQ(pTimerItemStart, 100);
    EXPECT_EQ(pTimerItemEnd,   200);
    EXPECT_GT(pTimerItemEnd, pTimerItemStart);
}

TEST(PTimerTest, MercTimers) {
    EXPECT_EQ(pTimerMercReuse,   901);
    EXPECT_EQ(pTimerMercSuspend, 902);
}

TEST(PTimerTest, AATimerRange) {
    EXPECT_EQ(pTimerAAStart, 1000);
    EXPECT_EQ(pTimerAAEnd,   2999);
    EXPECT_GT(pTimerAAEnd, pTimerAAStart);
}

TEST(PTimerTest, AAEffectTimerRange) {
    EXPECT_EQ(pTimerAAEffectStart, 3001);
    EXPECT_EQ(pTimerAAEffectEnd,   4999);
    EXPECT_GT(pTimerAAEffectEnd, pTimerAAEffectStart);
}

TEST(PTimerTest, SpellStartIs5000) {
    EXPECT_EQ(pTimerSpellStart, 5000);
    // SpellStart must be above AA ranges
    EXPECT_GT(pTimerSpellStart, pTimerAAEffectEnd);
}

TEST(PTimerTest, LinkedSpellRangeValues) {
    EXPECT_EQ(pTimerLinkedSpellReuseStart, 28);
    EXPECT_EQ(pTimerLinkedSpellReuseEnd,   48);
}
