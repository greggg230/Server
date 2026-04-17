#include <gtest/gtest.h>
#include <cstring>
#include "common/memory_buffer.h"

// ── Construction / Empty / Size / Capacity ────────────────────────────────────

TEST(MemoryBufferTest, DefaultConstruct_Empty) {
	EQ::MemoryBuffer buf;
	EXPECT_TRUE(buf.Empty());
	EXPECT_EQ(0u, buf.Size());
	EXPECT_EQ(0u, buf.Capacity());
	EXPECT_FALSE(static_cast<bool>(buf));
}

TEST(MemoryBufferTest, SizedConstruct) {
	EQ::MemoryBuffer buf(64);
	EXPECT_FALSE(buf.Empty());
	EXPECT_EQ(64u, buf.Size());
	EXPECT_GE(buf.Capacity(), 64u);
	EXPECT_TRUE(static_cast<bool>(buf));
}

TEST(MemoryBufferTest, CopyConstruct) {
	EQ::MemoryBuffer src(16);
	src[0] = 0xAB;
	src[15] = 0xCD;
	EQ::MemoryBuffer copy(src);
	EXPECT_EQ(src.Size(), copy.Size());
	EXPECT_EQ(0xAB, copy[0]);
	EXPECT_EQ(0xCD, copy[15]);
}

TEST(MemoryBufferTest, MoveConstruct) {
	EQ::MemoryBuffer src(16);
	src[0] = 0x12;
	EQ::MemoryBuffer moved(std::move(src));
	EXPECT_EQ(16u, moved.Size());
	EXPECT_EQ(0x12, moved[0]);
	// src should be cleared after move
	EXPECT_TRUE(src.Empty());
}

TEST(MemoryBufferTest, CopyAssign) {
	EQ::MemoryBuffer a(8);
	a[0] = 0xFF;
	EQ::MemoryBuffer b;
	b = a;
	EXPECT_EQ(8u, b.Size());
	EXPECT_EQ(0xFF, b[0]);
}

TEST(MemoryBufferTest, MoveAssign) {
	EQ::MemoryBuffer a(8);
	a[3] = 0x42;
	EQ::MemoryBuffer b;
	b = std::move(a);
	EXPECT_EQ(8u, b.Size());
	EXPECT_EQ(0x42, b[3]);
	EXPECT_TRUE(a.Empty());
}

// ── Resize ────────────────────────────────────────────────────────────────────

TEST(MemoryBufferTest, Resize_GrowsBuffer) {
	EQ::MemoryBuffer buf(16);
	buf.Resize(64);
	EXPECT_GE(buf.Size(), 64u);
}

TEST(MemoryBufferTest, Resize_ShrinkKeepsData) {
	EQ::MemoryBuffer buf(64);
	buf[0] = 0x5A;
	buf.Resize(8);
	EXPECT_EQ(8u, buf.Size());
	EXPECT_EQ(0x5A, buf[0]);
}

// ── Clear / Zero ──────────────────────────────────────────────────────────────

TEST(MemoryBufferTest, Clear_MakesEmpty) {
	EQ::MemoryBuffer buf(32);
	buf.Clear();
	EXPECT_TRUE(buf.Empty());
	EXPECT_EQ(0u, buf.Size());
}

TEST(MemoryBufferTest, Zero_FillsWithZeroes) {
	EQ::MemoryBuffer buf(16);
	for (size_t i = 0; i < 16; ++i) buf[i] = 0xFF;
	buf.Zero();
	for (size_t i = 0; i < 16; ++i) EXPECT_EQ(0, buf[i]);
}

// ── Read / Write POD types ────────────────────────────────────────────────────

TEST(MemoryBufferTest, WriteRead_Uint32) {
	EQ::MemoryBuffer buf;
	buf.Write<uint32_t>(0xDEADBEEF);
	buf.SetReadPosition(0);
	EXPECT_EQ(0xDEADBEEFu, buf.Read<uint32_t>());
}

TEST(MemoryBufferTest, WriteRead_Float) {
	EQ::MemoryBuffer buf;
	buf.Write<float>(3.14f);
	buf.SetReadPosition(0);
	EXPECT_FLOAT_EQ(3.14f, buf.Read<float>());
}

TEST(MemoryBufferTest, WriteRead_Uint8) {
	EQ::MemoryBuffer buf;
	buf.Write<uint8_t>(0xAB);
	buf.SetReadPosition(0);
	EXPECT_EQ(0xABu, buf.Read<uint8_t>());
}

TEST(MemoryBufferTest, WriteRead_MultipleValues) {
	EQ::MemoryBuffer buf;
	buf.Write<int32_t>(1);
	buf.Write<int32_t>(2);
	buf.Write<int32_t>(3);
	buf.SetReadPosition(0);
	EXPECT_EQ(1, buf.Read<int32_t>());
	EXPECT_EQ(2, buf.Read<int32_t>());
	EXPECT_EQ(3, buf.Read<int32_t>());
}

// ── Read / Write strings ──────────────────────────────────────────────────────

TEST(MemoryBufferTest, WriteRead_StdString) {
	EQ::MemoryBuffer buf;
	buf.Write(std::string("hello"));
	buf.SetReadPosition(0);
	EXPECT_EQ("hello", buf.ReadString());
}

TEST(MemoryBufferTest, WriteRead_CString) {
	EQ::MemoryBuffer buf;
	buf.Write("world");
	buf.SetReadPosition(0);
	EXPECT_EQ("world", buf.ReadString());
}

TEST(MemoryBufferTest, WriteRead_MixedTypes) {
	EQ::MemoryBuffer buf;
	buf.Write<uint16_t>(42);
	buf.Write(std::string("test"));
	buf.Write<float>(1.5f);

	buf.SetReadPosition(0);
	EXPECT_EQ(42u, buf.Read<uint16_t>());
	EXPECT_EQ("test", buf.ReadString());
	EXPECT_FLOAT_EQ(1.5f, buf.Read<float>());
}

// ── operator[] ────────────────────────────────────────────────────────────────

TEST(MemoryBufferTest, OperatorBracket_ReadWrite) {
	EQ::MemoryBuffer buf(4);
	buf[0] = 0x11;
	buf[1] = 0x22;
	EXPECT_EQ(0x11, buf[0]);
	EXPECT_EQ(0x22, buf[1]);
}

// ── operator+= / operator+ ────────────────────────────────────────────────────

TEST(MemoryBufferTest, AppendOperator) {
	EQ::MemoryBuffer a(4), b(4);
	a[0] = 0xAA;
	b[0] = 0xBB;
	a += b;
	EXPECT_GE(a.Size(), 8u);
	EXPECT_EQ(0xAA, a[0]);
}

// ── Write/Read position control ───────────────────────────────────────────────

TEST(MemoryBufferTest, WritePositionAdvances) {
	EQ::MemoryBuffer buf;
	EXPECT_EQ(0u, buf.GetWritePosition());
	buf.Write<uint32_t>(0);
	EXPECT_EQ(4u, buf.GetWritePosition());
}

TEST(MemoryBufferTest, ReadPositionAdvances) {
	EQ::MemoryBuffer buf;
	buf.Write<uint32_t>(0);
	buf.SetReadPosition(0);
	EXPECT_EQ(0u, buf.GetReadPosition());
	buf.Read<uint32_t>();
	EXPECT_EQ(4u, buf.GetReadPosition());
}

TEST(MemoryBufferTest, SkipBytesWrite) {
	EQ::MemoryBuffer buf;
	buf.Write<uint8_t>(0xAA);
	buf.WriteSkipBytes(3);
	buf.Write<uint8_t>(0xBB);
	buf.SetReadPosition(0);
	EXPECT_EQ(0xAAu, buf.Read<uint8_t>());
	buf.ReadSkipBytes(3);
	EXPECT_EQ(0xBBu, buf.Read<uint8_t>());
}

TEST(MemoryBufferTest, SetWritePosition_Overwrite) {
	EQ::MemoryBuffer buf;
	buf.Write<uint32_t>(0x11111111);
	buf.SetWritePosition(0);
	buf.Write<uint32_t>(0x22222222);
	buf.SetReadPosition(0);
	EXPECT_EQ(0x22222222u, buf.Read<uint32_t>());
}
