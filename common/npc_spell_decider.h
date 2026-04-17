#pragma once

#include "common/spdat.h"
#include "common/types.h"

// Interface for querying spell data -- allows mocking in tests without
// touching the global spells[] array.
class ISpellDataQuery {
public:
	virtual ~ISpellDataQuery() = default;
	virtual SpellTargetType GetTargetType(uint16 spell_id) const = 0;
	virtual int32           GetManaCost(uint16 spell_id) const   = 0;
	virtual uint32          GetCastTime(uint16 spell_id) const   = 0;
};

// Lightweight representation of a single entry in npc_spells_entries.
struct AISpellEntry {
	uint16 spell_id;
	uint32 spell_type;   // SpellTypes bitmask
	int32  mana_cost;    // -1 = use spell's own cost
	int32  min_hp;       // 0 = no minimum
	int32  max_hp;       // 0 = no maximum
};

// Pure decision logic extracted from mob_ai.cpp; depends only on ISpellDataQuery.
// This class owns no mutable state — all methods are const.
class NPCSpellDecider {
public:
	explicit NPCSpellDecider(const ISpellDataQuery& query) : m_query(query) {}

	// True if the spell targets an area/hate-list type and therefore should bypass
	// per-target buff-stack checks (Nuke/Debuff/DOT handlers in mob_ai.cpp).
	bool ShouldSkipStackCheck(const AISpellEntry& entry) const {
		SpellTargetType tt = m_query.GetTargetType(entry.spell_id);
		return NPCAITargetIsAE(tt);
	}

	// True if current HP% falls within the entry's HP filter window.
	// min_hp/max_hp of 0 means "no restriction on that bound".
	bool PassesHPFilter(const AISpellEntry& entry, float hp_pct) const {
		if (entry.min_hp > 0 && hp_pct < static_cast<float>(entry.min_hp)) return false;
		if (entry.max_hp > 0 && hp_pct > static_cast<float>(entry.max_hp)) return false;
		return true;
	}

	// True if the NPC has enough mana (or is at full mana, which bypasses the check).
	bool PassesManaFilter(const AISpellEntry& entry, int32 current_mana, int32 max_mana) const {
		int32 cost = (entry.mana_cost == -1)
		             ? m_query.GetManaCost(entry.spell_id)
		             : entry.mana_cost;
		return current_mana >= cost || current_mana == max_mana;
	}

	// Combination: entry is castable given current NPC state.
	bool IsCastable(const AISpellEntry& entry, float hp_pct, int32 mana, int32 max_mana) const {
		return PassesHPFilter(entry, hp_pct) && PassesManaFilter(entry, mana, max_mana);
	}

private:
	// Mirrors NPCAIUtil::IsAETargetType without depending on that header directly.
	static bool NPCAITargetIsAE(SpellTargetType tt) {
		switch (tt) {
			case ST_AETargetHateList:
			case ST_HateList:
			case ST_AECaster:
			case ST_AEClientV1:
			case ST_AETarget:
			case ST_AEBard:
			case ST_UndeadAE:
			case ST_SummonedAE:
			case ST_AreaClientOnly:
			case ST_AreaNPCOnly:
			case ST_Beam:
			case ST_Ring:
			case ST_Directional:
			case ST_TargetAETap:
			case ST_TargetAENoPlayersPets:
				return true;
			default:
				return false;
		}
	}

	const ISpellDataQuery& m_query;
};
