#include <gtest/gtest.h>
#include "common/additive_lagged_fibonacci_engine.h"

using EQRand = EQ::EQRand;

// ============================================================
// Static constants / template parameters
// ============================================================
TEST(EQRandConstTest, WordSizeIs30) {
    EXPECT_EQ(EQRand::word_size, 30u);
}

TEST(EQRandConstTest, ShortLagIs24) {
    EXPECT_EQ(EQRand::short_lag, 24u);
}

TEST(EQRandConstTest, LongLagIs55) {
    EXPECT_EQ(EQRand::long_lag, 55u);
}

TEST(EQRandConstTest, DefaultSeedIsNonZero) {
    EXPECT_GT(EQRand::default_seed, 0u);
}

TEST(EQRandConstTest, MinIsZero) {
    EXPECT_EQ(EQRand::min(), 0u);
}

TEST(EQRandConstTest, MaxIsPositive) {
    EXPECT_GT(EQRand::max(), 0u);
}

TEST(EQRandConstTest, MaxIsLessThan2Pow30) {
    EXPECT_LT(EQRand::max(), (1u << 30));
}

// ============================================================
// Construction and seeding
// ============================================================
TEST(EQRandConstructTest, DefaultConstructorDoesNotCrash) {
    EXPECT_NO_THROW(EQRand rng);
}

TEST(EQRandConstructTest, SeededConstructorDoesNotCrash) {
    EXPECT_NO_THROW(EQRand rng(12345u));
}

TEST(EQRandConstructTest, SeedMethodDoesNotCrash) {
    EQRand rng;
    EXPECT_NO_THROW(rng.seed(42u));
}

// ============================================================
// Generated values are within [min, max]
// ============================================================
TEST(EQRandRangeTest, GeneratedValueInRange) {
    EQRand rng(1u);
    for (int i = 0; i < 1000; ++i) {
        auto v = rng();
        EXPECT_GE(v, EQRand::min());
        EXPECT_LE(v, EQRand::max());
    }
}

// ============================================================
// Determinism: same seed → same sequence
// ============================================================
TEST(EQRandDeterminismTest, SameSeedSameSequence) {
    EQRand rng1(999u), rng2(999u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(rng1(), rng2());
    }
}

TEST(EQRandDeterminismTest, DifferentSeedsDifferentFirstValue) {
    EQRand rng1(1u), rng2(2u);
    // Sequences from different seeds must diverge somewhere in the first 55 values
    bool found_diff = false;
    for (int i = 0; i < 55; ++i) {
        if (rng1() != rng2()) {
            found_diff = true;
            break;
        }
    }
    EXPECT_TRUE(found_diff);
}

// ============================================================
// discard()
// ============================================================
TEST(EQRandDiscardTest, DiscardEquivalentToManualAdvance) {
    EQRand rng1(7u), rng2(7u);
    rng1.discard(10);
    for (int i = 0; i < 10; ++i) rng2();
    // After discarding 10, both should produce the same next value
    EXPECT_EQ(rng1(), rng2());
}

TEST(EQRandDiscardTest, DiscardZeroNoOp) {
    EQRand rng1(3u), rng2(3u);
    rng1.discard(0);
    EXPECT_EQ(rng1(), rng2());
}

// ============================================================
// operator== and operator!=
// ============================================================
TEST(EQRandEqualityTest, SameSeedEqualAfterConstruct) {
    EQRand rng1(100u), rng2(100u);
    EXPECT_EQ(rng1, rng2);
}

TEST(EQRandEqualityTest, DifferentSeedNotEqual) {
    EQRand rng1(100u), rng2(200u);
    EXPECT_NE(rng1, rng2);
}

TEST(EQRandEqualityTest, AfterOneCallNolongerEqual) {
    EQRand rng1(50u), rng2(50u);
    rng1();
    EXPECT_NE(rng1, rng2);
}

TEST(EQRandEqualityTest, ReseedMakesEqual) {
    EQRand rng1(1u), rng2(2u);
    rng1.seed(42u);
    rng2.seed(42u);
    EXPECT_EQ(rng1, rng2);
}
