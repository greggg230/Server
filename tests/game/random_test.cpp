/*	EQEmu: EQEmulator

	Copyright (C) 2001-2026 EQEmu Development Team

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.
*/
#include <gtest/gtest.h>
#include "common/random.h"

using EQ::Random;

// ---------------------------------------------------------------------------
// Int — range checks
// ---------------------------------------------------------------------------

TEST(EQRandom, IntStaysInRange) {
	Random rng;
	for (int i = 0; i < 1000; ++i) {
		int v = rng.Int(1, 10);
		EXPECT_GE(v, 1);
		EXPECT_LE(v, 10);
	}
}

TEST(EQRandom, IntSingleValueRange) {
	Random rng;
	for (int i = 0; i < 100; ++i) {
		EXPECT_EQ(rng.Int(5, 5), 5);
	}
}

TEST(EQRandom, IntSwapsWhenLowGtHigh) {
	Random rng;
	// Int(10, 1) should swap internally and behave as Int(1, 10)
	for (int i = 0; i < 200; ++i) {
		int v = rng.Int(10, 1);
		EXPECT_GE(v, 1);
		EXPECT_LE(v, 10);
	}
}

TEST(EQRandom, IntZeroRange) {
	Random rng;
	EXPECT_EQ(rng.Int(0, 0), 0);
}

TEST(EQRandom, IntNegativeRange) {
	Random rng;
	for (int i = 0; i < 200; ++i) {
		int v = rng.Int(-10, -1);
		EXPECT_GE(v, -10);
		EXPECT_LE(v, -1);
	}
}

// ---------------------------------------------------------------------------
// Real — range checks
// ---------------------------------------------------------------------------

TEST(EQRandom, RealStaysInRange) {
	Random rng;
	for (int i = 0; i < 1000; ++i) {
		double v = rng.Real(0.0, 1.0);
		EXPECT_GE(v, 0.0);
		EXPECT_LT(v, 1.0);  // Real is [low, high), not inclusive
	}
}

TEST(EQRandom, RealSwapsWhenLowGtHigh) {
	Random rng;
	for (int i = 0; i < 200; ++i) {
		double v = rng.Real(1.0, 0.0);
		EXPECT_GE(v, 0.0);
		EXPECT_LT(v, 1.0);
	}
}

// ---------------------------------------------------------------------------
// Roll — edge cases
// ---------------------------------------------------------------------------

TEST(EQRandom, Roll100AlwaysTrue) {
	Random rng;
	for (int i = 0; i < 500; ++i) {
		EXPECT_TRUE(rng.Roll(100));
	}
}

TEST(EQRandom, Roll0AlwaysFalse) {
	Random rng;
	for (int i = 0; i < 500; ++i) {
		EXPECT_FALSE(rng.Roll(0));
	}
}

TEST(EQRandom, RollProducesBothOutcomes) {
	// Roll(50) should produce both true and false over enough trials.
	// P(all same after 100 trials) ≈ 2*(0.5^100) ≈ negligible.
	Random rng;
	bool saw_true = false, saw_false = false;
	for (int i = 0; i < 100; ++i) {
		if (rng.Roll(50)) saw_true = true;
		else saw_false = true;
		if (saw_true && saw_false) break;
	}
	EXPECT_TRUE(saw_true);
	EXPECT_TRUE(saw_false);
}

TEST(EQRandom, RollDoubleEdgeCases) {
	Random rng;
	for (int i = 0; i < 200; ++i) {
		EXPECT_TRUE(rng.Roll(1.0));   // 100%
		EXPECT_FALSE(rng.Roll(0.0));  // 0%
	}
}
