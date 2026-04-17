#include <gtest/gtest.h>
#include <unordered_set>
#include <vector>
#include "common/additive_lagged_fibonacci_engine.h"

using EQRandEngine = EQ::EQRand;
// EQRand = additive_lagged_fibonacci_engine<uint32_t, 30, 24, 55>
// min() = 0, max() = ((1 << 30) - 1) >> 6 = 16777215

// ── Static properties ─────────────────────────────────────────────────────────

TEST(EQRandTest, MinIsZero) {
	EXPECT_EQ(0u, EQRandEngine::min());
}

TEST(EQRandTest, MaxValue) {
	EXPECT_EQ(16777215u, EQRandEngine::max());
}

TEST(EQRandTest, WordSizeLagParams) {
	EXPECT_EQ(30u, EQRandEngine::word_size);
	EXPECT_EQ(24u, EQRandEngine::short_lag);
	EXPECT_EQ(55u, EQRandEngine::long_lag);
}

// ── Output range ──────────────────────────────────────────────────────────────

TEST(EQRandTest, OutputWithinRange) {
	EQRandEngine rng;
	for (int i = 0; i < 1000; ++i) {
		uint32_t v = rng();
		EXPECT_GE(v, EQRandEngine::min());
		EXPECT_LE(v, EQRandEngine::max());
	}
}

// ── Determinism ───────────────────────────────────────────────────────────────

TEST(EQRandTest, SameSeed_SameSequence) {
	EQRandEngine a(12345), b(12345);
	for (int i = 0; i < 100; ++i)
		EXPECT_EQ(a(), b());
}

TEST(EQRandTest, DifferentSeed_DifferentSequence) {
	EQRandEngine a(1), b(2);
	bool any_differ = false;
	for (int i = 0; i < 20; ++i)
		if (a() != b()) { any_differ = true; break; }
	EXPECT_TRUE(any_differ);
}

TEST(EQRandTest, DefaultSeed_Deterministic) {
	EQRandEngine a, b; // both use default_seed
	for (int i = 0; i < 50; ++i)
		EXPECT_EQ(a(), b());
}

// ── seed() resets state ───────────────────────────────────────────────────────

TEST(EQRandTest, Reseed_ResetsSequence) {
	EQRandEngine rng(42);
	std::vector<uint32_t> first;
	for (int i = 0; i < 20; ++i) first.push_back(rng());

	rng.seed(42);
	for (int i = 0; i < 20; ++i)
		EXPECT_EQ(first[i], rng());
}

// ── discard ───────────────────────────────────────────────────────────────────

TEST(EQRandTest, Discard_EquivalentToAdvancing) {
	EQRandEngine a(99), b(99);
	// advance a by 10 manually
	for (int i = 0; i < 10; ++i) a();
	// advance b by 10 via discard
	b.discard(10);
	// they should now produce the same next value
	EXPECT_EQ(a(), b());
}

TEST(EQRandTest, Discard_Zero_NoChange) {
	EQRandEngine a(77), b(77);
	b.discard(0);
	EXPECT_EQ(a(), b());
}

// ── operator== / operator!= ───────────────────────────────────────────────────

TEST(EQRandTest, EqualAfterSameSeed) {
	EQRandEngine a(100), b(100);
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST(EQRandTest, NotEqualAfterAdvance) {
	EQRandEngine a(100), b(100);
	a();
	EXPECT_FALSE(a == b);
	EXPECT_TRUE(a != b);
}

TEST(EQRandTest, EqualAfterSameAdvance) {
	EQRandEngine a(100), b(100);
	a.discard(50);
	b.discard(50);
	EXPECT_TRUE(a == b);
}

// ── Diversity ─────────────────────────────────────────────────────────────────

TEST(EQRandTest, ProducesDistinctValues) {
	EQRandEngine rng;
	std::unordered_set<uint32_t> seen;
	for (int i = 0; i < 200; ++i) seen.insert(rng());
	// A good RNG should produce many distinct values in 200 draws
	EXPECT_GT(seen.size(), 150u);
}
