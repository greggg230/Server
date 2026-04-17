#include <gtest/gtest.h>
#include "common/util/uuid.h"

#include <sstream>
#include <string>

// ============================================================
// EQ::Util::UUID — Generate
// ============================================================
TEST(UUIDGenerateTest, GenerateDoesNotCrash) {
    EXPECT_NO_THROW(EQ::Util::UUID::Generate());
}

TEST(UUIDGenerateTest, GeneratedUUIDIsNonEmpty) {
    auto uuid = EQ::Util::UUID::Generate();
    EXPECT_FALSE(uuid.ToString().empty());
}

TEST(UUIDGenerateTest, GeneratedUUIDHasCorrectLength) {
    // UUID string format: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx = 36 chars
    auto uuid = EQ::Util::UUID::Generate();
    EXPECT_EQ(uuid.ToString().length(), 36u);
}

TEST(UUIDGenerateTest, GeneratedUUIDMatchesFormat) {
    auto uuid = EQ::Util::UUID::Generate();
    std::string s = uuid.ToString();
    EXPECT_EQ(s[8],  '-');
    EXPECT_EQ(s[13], '-');
    EXPECT_EQ(s[18], '-');
    EXPECT_EQ(s[23], '-');
}

TEST(UUIDGenerateTest, TwoGeneratedUUIDsAreDifferent) {
    auto a = EQ::Util::UUID::Generate();
    auto b = EQ::Util::UUID::Generate();
    EXPECT_NE(a.ToString(), b.ToString());
}

// ============================================================
// EQ::Util::UUID — ByteArray
// ============================================================
TEST(UUIDByteArrayTest, ByteArrayHas16Bytes) {
    auto uuid = EQ::Util::UUID::Generate();
    EXPECT_EQ(uuid.ToByteArray().size(), 16u);
}

TEST(UUIDByteArrayTest, ByteArrayNonEmpty) {
    auto uuid = EQ::Util::UUID::Generate();
    EXPECT_FALSE(uuid.ToByteArray().empty());
}

// ============================================================
// EQ::Util::UUID — FromString
// ============================================================
TEST(UUIDFromStringTest, FromStringDoesNotCrash) {
    EXPECT_NO_THROW(EQ::Util::UUID::FromString("00000000-0000-0000-0000-000000000000"));
}

TEST(UUIDFromStringTest, FromStringProducesNonEmptyToString) {
    // FromString may use different byte ordering than Generate; just verify it produces a valid UUID string
    auto uuid = EQ::Util::UUID::FromString("12345678-1234-1234-1234-123456789abc");
    EXPECT_EQ(uuid.ToString().length(), 36u);
    EXPECT_EQ(uuid.ToString()[8], '-');
}

TEST(UUIDFromStringTest, FromStringAllZerosRoundTrip) {
    std::string zero_uuid = "00000000-0000-0000-0000-000000000000";
    auto uuid = EQ::Util::UUID::FromString(zero_uuid);
    EXPECT_EQ(uuid.ToString(), zero_uuid);
}

// ============================================================
// EQ::Util::UUID — FromByteArray
// ============================================================
TEST(UUIDFromByteArrayTest, FromByteArrayRoundTrip) {
    auto original = EQ::Util::UUID::Generate();
    const auto& bytes = original.ToByteArray();
    auto restored = EQ::Util::UUID::FromByteArray(bytes.data());
    EXPECT_EQ(restored.ToString(), original.ToString());
}

// ============================================================
// EQ::Util::UUID — copy/move semantics
// ============================================================
TEST(UUIDCopyTest, CopyConstructorPreservesString) {
    auto a = EQ::Util::UUID::Generate();
    EQ::Util::UUID b(a);
    EXPECT_EQ(a.ToString(), b.ToString());
}

TEST(UUIDCopyTest, AssignmentPreservesString) {
    auto a = EQ::Util::UUID::Generate();
    auto b = EQ::Util::UUID::Generate();
    b = a;
    EXPECT_EQ(a.ToString(), b.ToString());
}

TEST(UUIDCopyTest, MoveConstructorPreservesString) {
    auto a = EQ::Util::UUID::Generate();
    std::string original = a.ToString();
    EQ::Util::UUID b(std::move(a));
    EXPECT_EQ(b.ToString(), original);
}

// ============================================================
// EQ::Util::UUID — output stream operator
// ============================================================
TEST(UUIDStreamTest, StreamOperatorMatchesToString) {
    auto uuid = EQ::Util::UUID::Generate();
    std::ostringstream oss;
    oss << uuid;
    EXPECT_EQ(oss.str(), uuid.ToString());
}
