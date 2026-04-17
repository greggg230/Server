#include <gtest/gtest.h>
#include <vector>
#include "common/fixed_memory_hash_set.h"

// Helper: allocate a properly-sized buffer for the hash set
static std::vector<uint8_t> MakeBuffer(uint32 element_count, uint32 max_key) {
	size_t sz = EQ::FixedMemoryHashSet<int>::estimated_size(element_count, max_key);
	return std::vector<uint8_t>(sz, 0);
}

// ── estimated_size ────────────────────────────────────────────────────────────

TEST(FixedMemoryHashSetTest, EstimatedSize_NonZero) {
	EXPECT_GT(EQ::FixedMemoryHashSet<int>::estimated_size(10, 100), 0u);
}

TEST(FixedMemoryHashSetTest, EstimatedSize_GrowsWithElements) {
	size_t s1 = EQ::FixedMemoryHashSet<int>::estimated_size(10, 100);
	size_t s2 = EQ::FixedMemoryHashSet<int>::estimated_size(20, 100);
	EXPECT_GT(s2, s1);
}

TEST(FixedMemoryHashSetTest, EstimatedSize_GrowsWithMaxKey) {
	size_t s1 = EQ::FixedMemoryHashSet<int>::estimated_size(10, 100);
	size_t s2 = EQ::FixedMemoryHashSet<int>::estimated_size(10, 200);
	EXPECT_GT(s2, s1);
}

// ── Construction and empty/size ───────────────────────────────────────────────

TEST(FixedMemoryHashSetTest, StartsEmpty) {
	auto buf = MakeBuffer(10, 100);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 10, 100);
	EXPECT_TRUE(hs.empty());
	EXPECT_EQ(0u, hs.size());
}

TEST(FixedMemoryHashSetTest, MaxSizeAndMaxKey) {
	auto buf = MakeBuffer(10, 100);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 10, 100);
	EXPECT_EQ(10u, hs.max_size());
	EXPECT_EQ(100u, hs.max_key());
}

// ── insert / exists / operator[] ─────────────────────────────────────────────

TEST(FixedMemoryHashSetTest, InsertAndExists) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);

	hs.insert(10, 42);
	EXPECT_TRUE(hs.exists(10));
	EXPECT_EQ(1u, hs.size());
	EXPECT_FALSE(hs.empty());
}

TEST(FixedMemoryHashSetTest, NotExistsByDefault) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	EXPECT_FALSE(hs.exists(10));
	EXPECT_FALSE(hs.exists(0));
}

TEST(FixedMemoryHashSetTest, InsertRetrieveValue) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	hs.insert(7, 999);
	EXPECT_EQ(999, hs[7]);
}

TEST(FixedMemoryHashSetTest, InsertMultipleKeys) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	hs.insert(1,  100);
	hs.insert(10, 200);
	hs.insert(50, 300);
	EXPECT_EQ(3u, hs.size());
	EXPECT_EQ(100, hs[1]);
	EXPECT_EQ(200, hs[10]);
	EXPECT_EQ(300, hs[50]);
}

TEST(FixedMemoryHashSetTest, UpdateExistingKey) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	hs.insert(5, 111);
	hs.insert(5, 222); // overwrite
	EXPECT_EQ(1u, hs.size()); // still only one element
	EXPECT_EQ(222, hs[5]);
}

TEST(FixedMemoryHashSetTest, AtMatchesOperator) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	hs.insert(3, 777);
	EXPECT_EQ(hs[3], hs.at(3));
}

TEST(FixedMemoryHashSetTest, ExistsReturnsFalseForOutOfRangeKey) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	EXPECT_FALSE(hs.exists(51)); // max_key is 50
	EXPECT_FALSE(hs.exists(9999));
}

// ── Exception cases ───────────────────────────────────────────────────────────

TEST(FixedMemoryHashSetTest, OperatorBracket_OutOfRange_Throws) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	EXPECT_THROW(hs[51], EQ::Exception);
}

TEST(FixedMemoryHashSetTest, OperatorBracket_NotFound_Throws) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	EXPECT_THROW(hs[10], EQ::Exception); // never inserted
}

TEST(FixedMemoryHashSetTest, Insert_OutOfRange_Throws) {
	auto buf = MakeBuffer(5, 50);
	EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
	EXPECT_THROW(hs.insert(51, 1), EQ::Exception);
}

// ── Struct values ─────────────────────────────────────────────────────────────

struct TestRecord { int id; float value; char name[8]; };

TEST(FixedMemoryHashSetTest, WorksWithStructs) {
	auto buf = MakeBuffer(3, 20);
	EQ::FixedMemoryHashSet<TestRecord> hs(buf.data(), buf.size(), 3, 20);
	TestRecord r{42, 3.14f, "hello"};
	hs.insert(7, r);
	EXPECT_TRUE(hs.exists(7));
	EXPECT_EQ(42,    hs[7].id);
	EXPECT_FLOAT_EQ(3.14f, hs[7].value);
	EXPECT_STREQ("hello", hs[7].name);
}

// ── Reconstruct from existing data ───────────────────────────────────────────

TEST(FixedMemoryHashSetTest, ReconstructFromBuffer) {
	auto buf = MakeBuffer(5, 50);
	// First pass: initialize and insert
	{
		EQ::FixedMemoryHashSet<int> hs(buf.data(), buf.size(), 5, 50);
		hs.insert(10, 100);
		hs.insert(20, 200);
	}
	// Second pass: reconstruct without init
	{
		EQ::FixedMemoryHashSet<int> hs2(buf.data(), buf.size());
		EXPECT_EQ(2u, hs2.size());
		EXPECT_EQ(100, hs2[10]);
		EXPECT_EQ(200, hs2[20]);
	}
}
