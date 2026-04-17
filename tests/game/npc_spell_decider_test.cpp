#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "common/npc_spell_decider.h"

using ::testing::Return;

// ── Mock ─────────────────────────────────────────────────────────────────────

class MockSpellDataQuery : public ISpellDataQuery {
public:
	MOCK_METHOD(SpellTargetType, GetTargetType, (uint16 spell_id), (const, override));
	MOCK_METHOD(int32,           GetManaCost,   (uint16 spell_id), (const, override));
	MOCK_METHOD(uint32,          GetCastTime,   (uint16 spell_id), (const, override));
};

// ── ShouldSkipStackCheck ──────────────────────────────────────────────────────

TEST(NPCSpellDeciderTest, AECaster_SkipsStackCheck) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetTargetType(36)).WillOnce(Return(ST_AECaster));
	NPCSpellDecider d(mock);
	AISpellEntry e{36, SpellType_Nuke, -1, 0, 0};
	EXPECT_TRUE(d.ShouldSkipStackCheck(e));
}

TEST(NPCSpellDeciderTest, AETargetHateList_SkipsStackCheck) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetTargetType(100)).WillOnce(Return(ST_AETargetHateList));
	NPCSpellDecider d(mock);
	AISpellEntry e{100, SpellType_DOT, -1, 0, 0};
	EXPECT_TRUE(d.ShouldSkipStackCheck(e));
}

TEST(NPCSpellDeciderTest, HateList_SkipsStackCheck) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetTargetType(200)).WillOnce(Return(ST_HateList));
	NPCSpellDecider d(mock);
	AISpellEntry e{200, SpellType_Debuff, -1, 0, 0};
	EXPECT_TRUE(d.ShouldSkipStackCheck(e));
}

TEST(NPCSpellDeciderTest, AEBard_SkipsStackCheck) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetTargetType(55)).WillOnce(Return(ST_AEBard));
	NPCSpellDecider d(mock);
	AISpellEntry e{55, SpellType_Buff, -1, 0, 0};
	EXPECT_TRUE(d.ShouldSkipStackCheck(e));
}

TEST(NPCSpellDeciderTest, SingleTarget_DoesNotSkipStackCheck) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetTargetType(10)).WillOnce(Return(ST_Target));
	NPCSpellDecider d(mock);
	AISpellEntry e{10, SpellType_DOT, -1, 0, 0};
	EXPECT_FALSE(d.ShouldSkipStackCheck(e));
}

TEST(NPCSpellDeciderTest, SelfTarget_DoesNotSkipStackCheck) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetTargetType(5)).WillOnce(Return(ST_Self));
	NPCSpellDecider d(mock);
	AISpellEntry e{5, SpellType_Buff, -1, 0, 0};
	EXPECT_FALSE(d.ShouldSkipStackCheck(e));
}

// ── PassesHPFilter ────────────────────────────────────────────────────────────

TEST(NPCSpellDeciderTest, NoHPFilter_AlwaysPasses) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	AISpellEntry e{36, SpellType_Escape, -1, 0, 0};
	EXPECT_TRUE(d.PassesHPFilter(e, 50.0f));
	EXPECT_TRUE(d.PassesHPFilter(e, 1.0f));
	EXPECT_TRUE(d.PassesHPFilter(e, 100.0f));
}

TEST(NPCSpellDeciderTest, MaxHPFilter_BlocksAboveThreshold) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	// Only cast when HP <= 20%
	AISpellEntry e{36, SpellType_Escape, -1, 0, 20};
	EXPECT_TRUE(d.PassesHPFilter(e, 20.0f));
	EXPECT_TRUE(d.PassesHPFilter(e, 10.0f));
	EXPECT_FALSE(d.PassesHPFilter(e, 21.0f));
	EXPECT_FALSE(d.PassesHPFilter(e, 100.0f));
}

TEST(NPCSpellDeciderTest, MinHPFilter_BlocksBelowThreshold) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	// Only cast when HP >= 50%
	AISpellEntry e{1343, SpellType_Heal, -1, 50, 0};
	EXPECT_TRUE(d.PassesHPFilter(e, 50.0f));
	EXPECT_TRUE(d.PassesHPFilter(e, 100.0f));
	EXPECT_FALSE(d.PassesHPFilter(e, 49.0f));
}

TEST(NPCSpellDeciderTest, HPWindowFilter) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	// Only cast when 30% <= HP <= 70%
	AISpellEntry e{50, SpellType_Buff, -1, 30, 70};
	EXPECT_TRUE(d.PassesHPFilter(e, 50.0f));
	EXPECT_FALSE(d.PassesHPFilter(e, 29.0f));
	EXPECT_FALSE(d.PassesHPFilter(e, 71.0f));
}

// ── PassesManaFilter ──────────────────────────────────────────────────────────

TEST(NPCSpellDeciderTest, InlineMana_SufficientMana) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	AISpellEntry e{36, SpellType_Nuke, 100, 0, 0};
	EXPECT_TRUE(d.PassesManaFilter(e, 500, 500));
	EXPECT_TRUE(d.PassesManaFilter(e, 100, 500));
}

TEST(NPCSpellDeciderTest, InlineMana_InsufficientMana) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	AISpellEntry e{36, SpellType_Nuke, 200, 0, 0};
	EXPECT_FALSE(d.PassesManaFilter(e, 100, 500));
}

TEST(NPCSpellDeciderTest, FullManaBypassesCheck) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	// current == max means "at full mana" — always allowed regardless of cost
	AISpellEntry e{36, SpellType_Nuke, 9999, 0, 0};
	EXPECT_TRUE(d.PassesManaFilter(e, 100, 100));
}

TEST(NPCSpellDeciderTest, DelegatesToQueryWhenManaCostIsNegativeOne) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetManaCost(36)).WillRepeatedly(Return(50));
	NPCSpellDecider d(mock);
	AISpellEntry e{36, SpellType_Nuke, -1, 0, 0};
	EXPECT_TRUE(d.PassesManaFilter(e, 50, 200));
	EXPECT_FALSE(d.PassesManaFilter(e, 49, 200));
}

// ── IsCastable (combined) ─────────────────────────────────────────────────────

TEST(NPCSpellDeciderTest, IsCastable_GateAtLowHP) {
	MockSpellDataQuery mock;
	EXPECT_CALL(mock, GetManaCost(36)).WillRepeatedly(Return(0));
	NPCSpellDecider d(mock);
	AISpellEntry gate{36, SpellType_Escape, -1, 0, 20};
	EXPECT_TRUE(d.IsCastable(gate, 15.0f, 100, 500));
	EXPECT_FALSE(d.IsCastable(gate, 50.0f, 100, 500));
}

TEST(NPCSpellDeciderTest, IsCastable_NotEnoughMana) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	AISpellEntry e{100, SpellType_Nuke, 300, 0, 0};
	EXPECT_FALSE(d.IsCastable(e, 80.0f, 100, 500));
}

TEST(NPCSpellDeciderTest, IsCastable_FullManaAlwaysCasts) {
	MockSpellDataQuery mock;
	NPCSpellDecider d(mock);
	AISpellEntry e{100, SpellType_Heal, 9999, 0, 0};
	EXPECT_TRUE(d.IsCastable(e, 80.0f, 500, 500));
}
