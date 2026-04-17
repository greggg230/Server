#include <gtest/gtest.h>
#include "common/md5.h"

#include <cstring>
#include <string>

// Helper: run MD5::Generate and return hex string
static std::string md5hex(const char* s) {
    uint8 digest[16] = {};
    MD5::Generate(reinterpret_cast<const uint8*>(s), static_cast<uint32>(strlen(s)), digest);
    char hex[33];
    for (int i = 0; i < 16; ++i)
        snprintf(hex + i * 2, 3, "%02x", digest[i]);
    return std::string(hex);
}

// ============================================================
// MD5::Generate (static) — RFC 1321 known test vectors
// ============================================================
TEST(MD5GenerateTest, EmptyStringDigest) {
    EXPECT_EQ(md5hex(""), "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(MD5GenerateTest, SingleCharA) {
    EXPECT_EQ(md5hex("a"), "0cc175b9c0f1b6a831c399e269772661");
}

TEST(MD5GenerateTest, Abc) {
    EXPECT_EQ(md5hex("abc"), "900150983cd24fb0d6963f7d28e17f72");
}

TEST(MD5GenerateTest, QuickBrownFox) {
    EXPECT_EQ(md5hex("The quick brown fox jumps over the lazy dog"),
              "9e107d9d372bb6826bd81d3542a419d6");
}

TEST(MD5GenerateTest, DifferentInputsDifferentDigests) {
    EXPECT_NE(md5hex("hello"), md5hex("world"));
}

TEST(MD5GenerateTest, CaseSensitive) {
    EXPECT_NE(md5hex("abc"), md5hex("ABC"));
}

// ============================================================
// MD5::Init + Update + Final — incremental API
// ============================================================
TEST(MD5IncrementalTest, WholeBufferMatchesGenerate) {
    const char* s = "abcdef";
    uint8 digest_gen[16] = {};
    MD5::Generate(reinterpret_cast<const uint8*>(s), 6, digest_gen);

    MD5::MD5Context ctx{};
    uint8 digest_inc[16] = {};
    MD5::Init(&ctx);
    MD5::Update(&ctx, reinterpret_cast<const uint8*>(s), 6);
    MD5::Final(digest_inc, &ctx);

    EXPECT_EQ(memcmp(digest_gen, digest_inc, 16), 0);
}

TEST(MD5IncrementalTest, SplitUpdatesMatchSingleCall) {
    const char* s = "The quick brown fox";
    uint8 digest_full[16] = {};
    MD5::Generate(reinterpret_cast<const uint8*>(s), 19, digest_full);

    MD5::MD5Context ctx{};
    uint8 digest_split[16] = {};
    MD5::Init(&ctx);
    MD5::Update(&ctx, reinterpret_cast<const uint8*>(s),      10);
    MD5::Update(&ctx, reinterpret_cast<const uint8*>(s) + 10, 9);
    MD5::Final(digest_split, &ctx);

    EXPECT_EQ(memcmp(digest_full, digest_split, 16), 0);
}

// ============================================================
// MD5 object — constructor & operator==
// ============================================================
TEST(MD5ObjectTest, ConstructFromStringMatchesGenerate) {
    const char* s = "hello";
    uint8 digest[16] = {};
    MD5::Generate(reinterpret_cast<const uint8*>(s), 5, digest);

    MD5 obj(reinterpret_cast<const uint8*>(s), 5);
    EXPECT_TRUE(obj == digest);
}

TEST(MD5ObjectTest, TwoSameInputsAreEqual) {
    MD5 a(reinterpret_cast<const uint8*>("test"), 4);
    MD5 b(reinterpret_cast<const uint8*>("test"), 4);
    EXPECT_TRUE(a == b);
}

TEST(MD5ObjectTest, DifferentInputsNotEqual) {
    MD5 a(reinterpret_cast<const uint8*>("foo"), 3);
    MD5 b(reinterpret_cast<const uint8*>("bar"), 3);
    EXPECT_FALSE(a == b);
}

TEST(MD5ObjectTest, ConstructFromDigestMatchesOriginal) {
    uint8 digest[16] = {};
    MD5::Generate(reinterpret_cast<const uint8*>("abc"), 3, digest);
    MD5 obj(digest);
    EXPECT_TRUE(obj == digest);
}

TEST(MD5ObjectTest, SetFromStringRoundTrips) {
    MD5 obj(reinterpret_cast<const uint8*>("abc"), 3);
    const char* hex = static_cast<const char*>(obj);
    MD5 obj2(hex);
    EXPECT_TRUE(obj == obj2);
}

TEST(MD5ObjectTest, CastToCharReturns32CharHex) {
    MD5 obj(reinterpret_cast<const uint8*>("abc"), 3);
    const char* hex = static_cast<const char*>(obj);
    EXPECT_EQ(strlen(hex), 32u);
    // Verify it's the known MD5 of "abc"
    EXPECT_STREQ(hex, "900150983cd24fb0d6963f7d28e17f72");
}

TEST(MD5ObjectTest, GenerateMemberFunctionMatchesStatic) {
    uint8 digest_static[16] = {};
    MD5::Generate(reinterpret_cast<const uint8*>("world"), 5, digest_static);

    MD5 obj;
    obj.Generate(reinterpret_cast<const uint8*>("world"), 5);
    EXPECT_TRUE(obj == digest_static);
}
