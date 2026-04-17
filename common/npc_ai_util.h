/*	EQEmu: EQEmulator

	Copyright (C) 2001-2026 EQEmu Development Team

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "common/spdat.h"

// Pure utility functions extracted from NPC AI logic so they can be unit-tested
// without requiring a live zone, database, or Mob/NPC object.

namespace NPCAIUtil {

// Returns true if the given spell target type represents an area-effect spell.
// AE spells should not be blocked from casting just because the current target
// already has the effect — they hit every mob in range, not only the target.
inline bool IsAETargetType(SpellTargetType target_type)
{
	switch (target_type) {
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

// Returns true if the NPC can afford to cast a spell with the given mana cost.
// An NPC at full mana is always considered able to cast (handles edge case where
// the mana pool briefly reads as full during tick boundaries).
inline bool CanAffordSpell(int32_t mana_cost, int32_t current_mana, int32_t max_mana)
{
	return mana_cost <= current_mana || current_mana == max_mana;
}

// Returns true if the NPC should attempt to gate at the given HP ratio.
// gate_percent is the server rule value (default 20 = gate at <=20% HP).
inline bool ShouldAttemptGate(float hp_ratio, int gate_percent)
{
	return hp_ratio <= static_cast<float>(gate_percent);
}

// Returns true if the NPC is close enough to its spawn point that gating is
// suppressed. distance_sq is the squared distance to spawn; bind_distance is
// the raw distance threshold (NPCGateDistanceBind rule, default 75).
inline bool IsTooCloseToGate(float distance_sq, float bind_distance)
{
	return distance_sq < (bind_distance * bind_distance);
}

} // namespace NPCAIUtil
