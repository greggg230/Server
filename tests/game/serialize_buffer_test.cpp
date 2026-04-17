#include <gtest/gtest.h>
#include "common/serialize_buffer.h"

#include <cstring>
#include <string>

// ---- Construction ----

TEST(SerializeBufferTest, DefaultConstructEmpty) {
    SerializeBuffer sb;
    EXPECT_EQ(sb.size(), 0u);
    EXPECT_EQ(sb.length(), 0u);
    EXPECT_EQ(sb.capacity(), 0u);
    EXPECT_EQ(sb.buffer(), nullptr);
}

TEST(SerializeBufferTest, SizedConstructPreallocates) {
    SerializeBuffer sb(64);
    EXPECT_EQ(sb.size(), 0u);
    EXPECT_EQ(sb.capacity(), 64u);
    EXPECT_NE(sb.buffer(), nullptr);
}

TEST(SerializeBufferTest, CopyConstructorCopiesData) {
    SerializeBuffer src(16);
    src.WriteUInt32(0xDEADBEEFu);
    SerializeBuffer dst(src);
    EXPECT_EQ(dst.size(), src.size());
    EXPECT_EQ(dst.capacity(), src.capacity());
    EXPECT_EQ(memcmp(dst.buffer(), src.buffer(), src.size()), 0);
    // independent buffers
    EXPECT_NE(dst.buffer(), src.buffer());
}

TEST(SerializeBufferTest, CopyAssignmentCopiesData) {
    SerializeBuffer src(16);
    src.WriteUInt32(42u);
    SerializeBuffer dst(32);
    dst = src;
    EXPECT_EQ(dst.size(), src.size());
    EXPECT_EQ(memcmp(dst.buffer(), src.buffer(), src.size()), 0);
}

TEST(SerializeBufferTest, MoveConstructorEmptiesSource) {
    SerializeBuffer src(16);
    src.WriteUInt32(99u);
    size_t old_size = src.size();
    SerializeBuffer dst(std::move(src));
    EXPECT_EQ(dst.size(), old_size);
    EXPECT_EQ(src.size(), 0u);
    EXPECT_EQ(src.buffer(), nullptr);
}

TEST(SerializeBufferTest, MoveAssignmentEmptiesSource) {
    SerializeBuffer src(16);
    src.WriteUInt8(7u);
    SerializeBuffer dst;
    dst = std::move(src);
    EXPECT_EQ(dst.size(), 1u);
    EXPECT_EQ(src.size(), 0u);
}

// ---- Write + verify buffer bytes ----

TEST(SerializeBufferTest, WriteUInt8StoresByte) {
    SerializeBuffer sb(8);
    sb.WriteUInt8(0xABu);
    EXPECT_EQ(sb.size(), 1u);
    EXPECT_EQ(sb.buffer()[0], 0xABu);
}

TEST(SerializeBufferTest, WriteUInt16StoresTwoBytes) {
    SerializeBuffer sb(8);
    sb.WriteUInt16(0x1234u);
    EXPECT_EQ(sb.size(), 2u);
    uint16_t v;
    memcpy(&v, sb.buffer(), sizeof(v));
    EXPECT_EQ(v, 0x1234u);
}

TEST(SerializeBufferTest, WriteUInt32StoresFourBytes) {
    SerializeBuffer sb(8);
    sb.WriteUInt32(0xDEADBEEFu);
    EXPECT_EQ(sb.size(), 4u);
    uint32_t v;
    memcpy(&v, sb.buffer(), sizeof(v));
    EXPECT_EQ(v, 0xDEADBEEFu);
}

TEST(SerializeBufferTest, WriteUInt64StoresEightBytes) {
    SerializeBuffer sb(16);
    sb.WriteUInt64(0xCAFEBABEDEADBEEFull);
    EXPECT_EQ(sb.size(), 8u);
    uint64_t v;
    memcpy(&v, sb.buffer(), sizeof(v));
    EXPECT_EQ(v, 0xCAFEBABEDEADBEEFull);
}

TEST(SerializeBufferTest, WriteSignedIntegers) {
    SerializeBuffer sb(16);
    sb.WriteInt8(-1);
    sb.WriteInt16(-500);
    sb.WriteInt32(-100000);
    EXPECT_EQ(sb.size(), 1u + 2u + 4u);
    int8_t i8; memcpy(&i8, sb.buffer(), 1);
    EXPECT_EQ(i8, -1);
    int16_t i16; memcpy(&i16, sb.buffer() + 1, 2);
    EXPECT_EQ(i16, -500);
    int32_t i32; memcpy(&i32, sb.buffer() + 3, 4);
    EXPECT_EQ(i32, -100000);
}

TEST(SerializeBufferTest, WriteFloat) {
    SerializeBuffer sb(8);
    sb.WriteFloat(3.14f);
    EXPECT_EQ(sb.size(), sizeof(float));
    float v; memcpy(&v, sb.buffer(), sizeof(float));
    EXPECT_FLOAT_EQ(v, 3.14f);
}

TEST(SerializeBufferTest, WriteDouble) {
    SerializeBuffer sb(16);
    sb.WriteDouble(2.718281828);
    EXPECT_EQ(sb.size(), sizeof(double));
    double v; memcpy(&v, sb.buffer(), sizeof(double));
    EXPECT_DOUBLE_EQ(v, 2.718281828);
}

// ---- String writes ----

TEST(SerializeBufferTest, WriteStringCstrIncludesNullTerminator) {
    SerializeBuffer sb(32);
    sb.WriteString("hello");
    EXPECT_EQ(sb.size(), 6u);  // 5 chars + null
    EXPECT_EQ(memcmp(sb.buffer(), "hello\0", 6), 0);
}

TEST(SerializeBufferTest, WriteStringStdStringIncludesNullTerminator) {
    SerializeBuffer sb(32);
    sb.WriteString(std::string("world"));
    EXPECT_EQ(sb.size(), 6u);
    EXPECT_EQ(memcmp(sb.buffer(), "world\0", 6), 0);
}

TEST(SerializeBufferTest, WriteLengthStringCstrWritesLenThenData) {
    SerializeBuffer sb(32);
    sb.WriteLengthString(5, "hello");
    EXPECT_EQ(sb.size(), 4u + 5u);  // uint32 length + data (no null)
    uint32_t len; memcpy(&len, sb.buffer(), 4);
    EXPECT_EQ(len, 5u);
    EXPECT_EQ(memcmp(sb.buffer() + 4, "hello", 5), 0);
}

TEST(SerializeBufferTest, WriteLengthStringStdStringWritesLenThenData) {
    SerializeBuffer sb(32);
    sb.WriteLengthString(std::string("hi"));
    EXPECT_EQ(sb.size(), 4u + 2u);
    uint32_t len; memcpy(&len, sb.buffer(), 4);
    EXPECT_EQ(len, 2u);
    EXPECT_EQ(memcmp(sb.buffer() + 4, "hi", 2), 0);
}

// ---- Sequential writes ----

TEST(SerializeBufferTest, MultipleWritesSequential) {
    SerializeBuffer sb(32);
    sb.WriteUInt8(1u);
    sb.WriteUInt32(0xAABBCCDDu);
    sb.WriteUInt8(2u);
    EXPECT_EQ(sb.size(), 1u + 4u + 1u);
    EXPECT_EQ(sb.buffer()[0], 1u);
    uint32_t v; memcpy(&v, sb.buffer() + 1, 4);
    EXPECT_EQ(v, 0xAABBCCDDu);
    EXPECT_EQ(sb.buffer()[5], 2u);
}

// ---- Auto-grow ----

TEST(SerializeBufferTest, AutoGrowsWhenCapacityExceeded) {
    SerializeBuffer sb(2);
    // Write more than initial capacity
    sb.WriteUInt32(0x12345678u);
    EXPECT_EQ(sb.size(), 4u);
    EXPECT_GE(sb.capacity(), 4u);
    uint32_t v; memcpy(&v, sb.buffer(), 4);
    EXPECT_EQ(v, 0x12345678u);
}

TEST(SerializeBufferTest, DefaultConstructAutoGrowsOnFirstWrite) {
    SerializeBuffer sb;
    sb.WriteUInt8(42u);
    EXPECT_EQ(sb.size(), 1u);
    EXPECT_GE(sb.capacity(), 1u);
    EXPECT_EQ(sb.buffer()[0], 42u);
}

TEST(SerializeBufferTest, GrowPreservesExistingData) {
    SerializeBuffer sb(4);
    sb.WriteUInt32(0xDEADBEEFu);
    sb.WriteUInt32(0xCAFEBABEu);  // triggers grow
    EXPECT_EQ(sb.size(), 8u);
    uint32_t a, b;
    memcpy(&a, sb.buffer(), 4);
    memcpy(&b, sb.buffer() + 4, 4);
    EXPECT_EQ(a, 0xDEADBEEFu);
    EXPECT_EQ(b, 0xCAFEBABEu);
}
