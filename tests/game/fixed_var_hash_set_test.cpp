#include <gtest/gtest.h>
#include "common/fixed_memory_variable_hash_set.h"
#include "common/eqemu_exception.h"

#include <cstring>
#include <string>
#include <vector>

// Buffer layout: 3 uint32 header + (max_key+1) uint32 offsets + element_capacity bytes
static std::vector<uint8_t> MakeVarBuffer(uint32_t max_key, uint32_t element_capacity) {
    size_t total = sizeof(uint32_t) * 3
                 + sizeof(uint32_t) * (max_key + 1)
                 + element_capacity;
    return std::vector<uint8_t>(total, 0);
}

// ---- size / capacity ----

TEST(FixedVarHashSetTest, MaxKeyReturnsCorrectValue) {
    auto buf = MakeVarBuffer(9, 512);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 9);
    EXPECT_EQ(hs.max_key(), 9u);
}

TEST(FixedVarHashSetTest, SizeStartsAtHeader) {
    // size() = total_size - remaining_size; initially remaining_size = element_capacity
    // so size() should equal header + offsets area = sizeof(uint32)*3 + sizeof(uint32)*(max_key+1)
    auto buf = MakeVarBuffer(4, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 4);
    uint32_t expected = sizeof(uint32_t) * 3 + sizeof(uint32_t) * 5;  // max_key=4 → offset_count=5
    EXPECT_EQ(hs.size(), expected);
}

// ---- exists ----

TEST(FixedVarHashSetTest, AllSlotsFalseAfterInit) {
    auto buf = MakeVarBuffer(5, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 5);
    for (uint32_t i = 0; i <= 5; ++i) {
        EXPECT_FALSE(hs.exists(i)) << "key=" << i;
    }
}

TEST(FixedVarHashSetTest, ExistsReturnsFalseForOutOfRange) {
    auto buf = MakeVarBuffer(3, 128);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 3);
    EXPECT_FALSE(hs.exists(4));
    EXPECT_FALSE(hs.exists(100));
}

// ---- insert + read ----

TEST(FixedVarHashSetTest, InsertAndExists) {
    auto buf = MakeVarBuffer(9, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 9);
    uint32_t val = 42u;
    hs.insert(0, reinterpret_cast<uint8_t*>(&val), sizeof(val));
    EXPECT_TRUE(hs.exists(0));
    EXPECT_FALSE(hs.exists(1));
}

TEST(FixedVarHashSetTest, InsertAndRetrieveValue) {
    auto buf = MakeVarBuffer(9, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 9);
    uint32_t val = 0xDEADBEEFu;
    hs.insert(3, reinterpret_cast<uint8_t*>(&val), sizeof(val));
    EXPECT_EQ(hs[3], 0xDEADBEEFu);
}

TEST(FixedVarHashSetTest, AtMatchesBracketOperator) {
    auto buf = MakeVarBuffer(9, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 9);
    uint32_t val = 99u;
    hs.insert(2, reinterpret_cast<uint8_t*>(&val), sizeof(val));
    EXPECT_EQ(hs.at(2), hs[2]);
}

TEST(FixedVarHashSetTest, InsertMultipleKeys) {
    auto buf = MakeVarBuffer(9, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 9);
    uint32_t a = 1u, b = 2u, c = 3u;
    hs.insert(0, reinterpret_cast<uint8_t*>(&a), sizeof(a));
    hs.insert(5, reinterpret_cast<uint8_t*>(&b), sizeof(b));
    hs.insert(9, reinterpret_cast<uint8_t*>(&c), sizeof(c));
    EXPECT_EQ(hs[0], 1u);
    EXPECT_EQ(hs[5], 2u);
    EXPECT_EQ(hs[9], 3u);
    EXPECT_FALSE(hs.exists(1));
    EXPECT_FALSE(hs.exists(4));
}

TEST(FixedVarHashSetTest, SizeGrowsAfterInserts) {
    auto buf = MakeVarBuffer(4, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 4);
    size_t initial_size = hs.size();
    uint32_t val = 7u;
    hs.insert(0, reinterpret_cast<uint8_t*>(&val), sizeof(val));
    EXPECT_GT(hs.size(), initial_size);
}

// ---- struct value support ----

struct TestRecord {
    int id;
    float score;
};

TEST(FixedVarHashSetTest, WorksWithStructValues) {
    auto buf = MakeVarBuffer(5, 512);
    EQ::FixedMemoryVariableHashSet<TestRecord> hs(buf.data(), buf.size(), 5);
    TestRecord rec = {42, 3.14f};
    hs.insert(1, reinterpret_cast<uint8_t*>(&rec), sizeof(rec));
    EXPECT_TRUE(hs.exists(1));
    EXPECT_EQ(hs[1].id, 42);
    EXPECT_FLOAT_EQ(hs[1].score, 3.14f);
}

// ---- exception cases ----

TEST(FixedVarHashSetTest, BracketOutOfRangeThrows) {
    auto buf = MakeVarBuffer(3, 128);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 3);
    EXPECT_THROW(hs[4], EQ::Exception);
}

TEST(FixedVarHashSetTest, BracketNotFoundThrows) {
    auto buf = MakeVarBuffer(3, 128);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 3);
    EXPECT_THROW(hs[0], EQ::Exception);
}

TEST(FixedVarHashSetTest, AtOutOfRangeThrows) {
    auto buf = MakeVarBuffer(3, 128);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 3);
    EXPECT_THROW(hs.at(10), EQ::Exception);
}

TEST(FixedVarHashSetTest, InsertOutOfRangeThrows) {
    auto buf = MakeVarBuffer(3, 128);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 3);
    uint32_t val = 0u;
    EXPECT_THROW(hs.insert(4, reinterpret_cast<uint8_t*>(&val), sizeof(val)), EQ::Exception);
}

TEST(FixedVarHashSetTest, InsertDuplicateThrows) {
    auto buf = MakeVarBuffer(3, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 3);
    uint32_t val = 5u;
    hs.insert(0, reinterpret_cast<uint8_t*>(&val), sizeof(val));
    EXPECT_THROW(hs.insert(0, reinterpret_cast<uint8_t*>(&val), sizeof(val)), EQ::Exception);
}

// ---- reconstruct from existing buffer ----

TEST(FixedVarHashSetTest, ReconstructFromBuffer) {
    auto buf = MakeVarBuffer(9, 512);
    {
        EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 9);
        uint32_t v1 = 111u, v2 = 222u;
        hs.insert(2, reinterpret_cast<uint8_t*>(&v1), sizeof(v1));
        hs.insert(7, reinterpret_cast<uint8_t*>(&v2), sizeof(v2));
    }
    // Second constructor reads existing data from buffer
    EQ::FixedMemoryVariableHashSet<uint32_t> hs2(buf.data(), buf.size());
    EXPECT_TRUE(hs2.exists(2));
    EXPECT_TRUE(hs2.exists(7));
    EXPECT_FALSE(hs2.exists(0));
    EXPECT_EQ(hs2[2], 111u);
    EXPECT_EQ(hs2[7], 222u);
}

// ---- copy constructor ----

TEST(FixedVarHashSetTest, CopyConstructorSharesData) {
    auto buf = MakeVarBuffer(4, 256);
    EQ::FixedMemoryVariableHashSet<uint32_t> hs(buf.data(), buf.size(), 4);
    uint32_t val = 77u;
    hs.insert(1, reinterpret_cast<uint8_t*>(&val), sizeof(val));

    EQ::FixedMemoryVariableHashSet<uint32_t> hs2(hs);
    EXPECT_TRUE(hs2.exists(1));
    EXPECT_EQ(hs2[1], 77u);
}
