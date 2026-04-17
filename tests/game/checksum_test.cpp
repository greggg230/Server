#include <gtest/gtest.h>
#include <cstring>
#include "common/crc32.h"
#include "common/crc16.h"
#include "common/md5.h"

// ── CRC32 ────────────────────────────────────────────────────────────────────

TEST(CRC32Test, EmptyBuffer) {
	// CRC32 of zero bytes = 0x00000000
	uint8 buf[] = {};
	EXPECT_EQ(0x00000000u, CRC32::Generate(buf, 0));
}

TEST(CRC32Test, KnownVector_123456789) {
	// Standard CRC32 check value for "123456789"
	const uint8* buf = reinterpret_cast<const uint8*>("123456789");
	EXPECT_EQ(0xCBF43926u, CRC32::Generate(buf, 9));
}

TEST(CRC32Test, SingleByte_A) {
	const uint8 buf[] = { 'A' };
	uint32 result = CRC32::Generate(buf, 1);
	EXPECT_NE(0u, result);
	// Round-trip: same input always yields same output
	EXPECT_EQ(result, CRC32::Generate(buf, 1));
}

TEST(CRC32Test, GenerateNoFlipDiffersFromGenerate) {
	const uint8* buf = reinterpret_cast<const uint8*>("test");
	uint32 flipped = CRC32::Generate(buf, 4);
	uint32 noFlip  = CRC32::GenerateNoFlip(buf, 4);
	EXPECT_EQ(flipped, ~noFlip);
}

TEST(CRC32Test, IncrementalMatchesSingleCall) {
	const uint8* data = reinterpret_cast<const uint8*>("helloworld");
	uint32 oneShotCRC = CRC32::Generate(data, 10);

	// Same data split into two chunks
	uint32 crc = CRC32::Update(data,     5);      // "hello"
	crc        = CRC32::Update(data + 5, 5, crc); // "world"
	crc        = CRC32::Finish(crc);
	EXPECT_EQ(oneShotCRC, crc);
}

TEST(CRC32Test, FinishInvertsBits) {
	uint32 raw = 0xDEADBEEF;
	EXPECT_EQ(~raw, CRC32::Finish(raw));
}

TEST(CRC32Test, FinishPointerVariant) {
	uint32 val = 0x12345678;
	CRC32::Finish(&val);
	EXPECT_EQ(~static_cast<uint32>(0x12345678), val);
}

TEST(CRC32Test, DifferentInputsDifferentCRC) {
	const uint8* a = reinterpret_cast<const uint8*>("abc");
	const uint8* b = reinterpret_cast<const uint8*>("abd");
	EXPECT_NE(CRC32::Generate(a, 3), CRC32::Generate(b, 3));
}

// ── CRC16 ────────────────────────────────────────────────────────────────────

TEST(CRC16Test, Deterministic) {
	const unsigned char* buf = reinterpret_cast<const unsigned char*>("hello");
	uint16 a = CRC16(buf, 5, 12345);
	uint16 b = CRC16(buf, 5, 12345);
	EXPECT_EQ(a, b);
}

TEST(CRC16Test, KeyChangesResult) {
	const unsigned char* buf = reinterpret_cast<const unsigned char*>("hello");
	uint16 r1 = CRC16(buf, 5, 0);
	uint16 r2 = CRC16(buf, 5, 1);
	EXPECT_NE(r1, r2);
}

TEST(CRC16Test, DataChangesResult) {
	const unsigned char* a = reinterpret_cast<const unsigned char*>("hello");
	const unsigned char* b = reinterpret_cast<const unsigned char*>("world");
	EXPECT_NE(CRC16(a, 5, 0), CRC16(b, 5, 0));
}

TEST(CRC16Test, ResultFitsIn16Bits) {
	const unsigned char* buf = reinterpret_cast<const unsigned char*>("123456789");
	uint16 result = CRC16(buf, 9, 0);
	EXPECT_EQ(result, result & 0xFFFF);
}

// ── MD5 ──────────────────────────────────────────────────────────────────────

TEST(MD5Test, EmptyString) {
	MD5 digest;
	digest.Generate((const uint8*)"", 0u);
	EXPECT_STREQ("d41d8cd98f00b204e9800998ecf8427e", static_cast<const char*>(digest));
}

TEST(MD5Test, HelloWorld) {
	MD5 digest((const uint8*)"hello world", 11);
	EXPECT_STREQ("5eb63bbbe01eeed093cb22bb8f5acdc3", static_cast<const char*>(digest));
}

TEST(MD5Test, QuickBrownFox) {
	const char* s = "The quick brown fox jumps over the lazy dog";
	MD5 digest((const uint8*)s, static_cast<uint32>(strlen(s)));
	EXPECT_STREQ("9e107d9d372bb6826bd81d3542a419d6", static_cast<const char*>(digest));
}

TEST(MD5Test, ConstructFromStringAndGenerate_Agree) {
	const uint8* buf = reinterpret_cast<const uint8*>("eqemu");
	MD5 a(buf, 5);
	MD5 b;
	b.Generate(buf, 5);
	EXPECT_TRUE(a == b);
}

TEST(MD5Test, SetFromByteArray) {
	uint8 raw[16] = {0x5e,0xb6,0x3b,0xbb,0xe0,0x1e,0xee,0xd0,
	                 0x93,0xcb,0x22,0xbb,0x8f,0x5a,0xcd,0xc3};
	MD5 a;
	a.Set(raw);
	MD5 b((const uint8*)"hello world", 11);
	EXPECT_TRUE(a == b);
}

TEST(MD5Test, SetFromHexString) {
	MD5 a;
	EXPECT_TRUE(a.Set("5eb63bbbe01eeed093cb22bb8f5acdc3"));
	MD5 b((const uint8*)"hello world", 11);
	EXPECT_TRUE(a == b);
}

TEST(MD5Test, EqualityOperatorWithRawBytes) {
	uint8 raw[16] = {0xd4,0x1d,0x8c,0xd9,0x8f,0x00,0xb2,0x04,
	                 0xe9,0x80,0x09,0x98,0xec,0xf8,0x42,0x7e};
	MD5 digest;
	digest.Generate((const uint8*)"", 0u);
	EXPECT_TRUE(digest == raw);
}

TEST(MD5Test, DifferentInputsDifferentDigests) {
	MD5 a((const uint8*)"abc", 3);
	MD5 b((const uint8*)"abd", 3);
	EXPECT_FALSE(a == b);
}

TEST(MD5Test, SetInvalidHexStringReturnsFalse) {
	MD5 m;
	// Too short
	EXPECT_FALSE(m.Set("5eb63bbbe01eeed093cb22bb8f5acd"));
}
