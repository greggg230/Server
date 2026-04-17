#include <gtest/gtest.h>
#include "common/util/uuid.h"

#include <regex>
#include <string>

using EQ::Util::UUID;

// ============================================================
// UUID format (Generate / ToString)
// ============================================================
static bool IsValidUUIDFormat(const std::string& s) {
    // xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx (36 chars, lowercase hex + dashes)
    static const std::regex uuid_re(
        "[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}");
    return std::regex_match(s, uuid_re);
}

TEST(UUIDTest, GeneratedLengthIs36) {
    UUID id = UUID::Generate();
    EXPECT_EQ(id.ToString().size(), 36u);
}

TEST(UUIDTest, GeneratedHasDashesAtCorrectPositions) {
    std::string s = UUID::Generate().ToString();
    EXPECT_EQ(s[8],  '-');
    EXPECT_EQ(s[13], '-');
    EXPECT_EQ(s[18], '-');
    EXPECT_EQ(s[23], '-');
}

TEST(UUIDTest, GeneratedMatchesUUIDRegex) {
    std::string s = UUID::Generate().ToString();
    EXPECT_TRUE(IsValidUUIDFormat(s)) << "Generated UUID '" << s << "' is not valid UUID format";
}

TEST(UUIDTest, TwoGeneratedUUIDsAreDifferent) {
    UUID a = UUID::Generate();
    UUID b = UUID::Generate();
    EXPECT_NE(a.ToString(), b.ToString());
}

TEST(UUIDTest, ToStringHas32HexDigitsBeyondDashes) {
    std::string s = UUID::Generate().ToString();
    std::string digits;
    for (char c : s) {
        if (c != '-') digits += c;
    }
    EXPECT_EQ(digits.size(), 32u);
    for (char c : digits) {
        EXPECT_TRUE((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))
            << "Non-lowercase-hex char: " << c;
    }
}

// ============================================================
// FromString round-trip with all-same-nibble strings
// (FromString has overlapping-pair reads so only trivial
//  inputs like all-zeros survive a round-trip)
// ============================================================
TEST(UUIDTest, FromStringAllZerosRoundTrip) {
    const std::string zeros = "00000000-0000-0000-0000-000000000000";
    UUID id = UUID::FromString(zeros);
    EXPECT_EQ(id.ToString(), zeros);
}

// ============================================================
// FromByteArray / ToByteArray
// ============================================================
TEST(UUIDTest, FromByteArrayProduces16BytesInToByteArray) {
    const unsigned char ubytes[16] = {
        0x55, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78,
        0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44
    };
    UUID id = UUID::FromByteArray(reinterpret_cast<const char*>(ubytes));
    EXPECT_EQ(id.ToByteArray().size(), 16u);
}

TEST(UUIDTest, FromByteArrayBytesMatchToByteArray) {
    const unsigned char ubytes[16] = {
        0x55, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78,
        0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44
    };
    UUID id = UUID::FromByteArray(reinterpret_cast<const char*>(ubytes));
    const std::vector<char>& ba = id.ToByteArray();
    ASSERT_EQ(ba.size(), 16u);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ((unsigned char)ba[i], ubytes[i]) << "Byte mismatch at index " << i;
    }
}

TEST(UUIDTest, ToByteArrayHas16Bytes) {
    UUID id = UUID::FromString("00000000-0000-0000-0000-000000000000");
    EXPECT_EQ(id.ToByteArray().size(), 16u);
}

TEST(UUIDTest, GenerateToByteArrayHas16Bytes) {
    UUID id = UUID::Generate();
    EXPECT_EQ(id.ToByteArray().size(), 16u);
}

TEST(UUIDTest, FromByteArrayRoundTripViaToByteArray) {
    const unsigned char ubytes[16] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
    };
    UUID a = UUID::FromByteArray(reinterpret_cast<const char*>(ubytes));
    const std::vector<char>& ba = a.ToByteArray();
    UUID b = UUID::FromByteArray(ba.data());
    EXPECT_EQ(a.ToByteArray(), b.ToByteArray());
}

// ============================================================
// Copy and move semantics
// ============================================================
TEST(UUIDTest, CopyConstructorPreservesValue) {
    UUID a = UUID::Generate();
    UUID b(a);
    EXPECT_EQ(a.ToString(), b.ToString());
}

TEST(UUIDTest, AssignmentPreservesValue) {
    UUID a = UUID::Generate();
    UUID b = UUID::Generate();
    b = a;
    EXPECT_EQ(a.ToString(), b.ToString());
}

TEST(UUIDTest, MoveConstructorTransfersValue) {
    UUID a = UUID::Generate();
    std::string s = a.ToString();
    UUID b(std::move(a));
    EXPECT_EQ(b.ToString(), s);
}

TEST(UUIDTest, CopiedUUIDIsIndependent) {
    UUID a = UUID::Generate();
    UUID b(a);
    // Modifying a's string representation doesn't change b
    std::string sa = a.ToString();
    std::string sb = b.ToString();
    EXPECT_EQ(sa, sb);
}

// ============================================================
// Multiple Generate calls
// ============================================================
TEST(UUIDTest, TenGeneratedUUIDsAllValid) {
    for (int i = 0; i < 10; ++i) {
        std::string s = UUID::Generate().ToString();
        EXPECT_TRUE(IsValidUUIDFormat(s)) << "UUID #" << i << " invalid: " << s;
    }
}

TEST(UUIDTest, TenGeneratedUUIDsAllUnique) {
    std::vector<std::string> uuids;
    for (int i = 0; i < 10; ++i) {
        uuids.push_back(UUID::Generate().ToString());
    }
    for (size_t i = 0; i < uuids.size(); ++i) {
        for (size_t j = i + 1; j < uuids.size(); ++j) {
            EXPECT_NE(uuids[i], uuids[j]) << "UUIDs " << i << " and " << j << " collided";
        }
    }
}
