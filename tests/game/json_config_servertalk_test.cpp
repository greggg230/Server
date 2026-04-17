#include <gtest/gtest.h>
#include "common/json_config.h"
#include "common/net/servertalk_common.h"

#include "common/json/json.h"

#include <string>

// ============================================================
// Helper: build a Json::Value with known structure
// ============================================================
static Json::Value MakeTestRoot() {
    Json::Value root;
    root["section"]["str_key"]  = "hello";
    root["section"]["int_key"]  = 42;
    root["section"]["bool_key"] = true;
    root["section"]["dbl_key"]  = 3.14;
    return root;
}

// ============================================================
// JsonConfigFile — default constructor
// ============================================================
TEST(JsonConfigFileTest, DefaultConstructDoesNotCrash) {
    EXPECT_NO_THROW(EQ::JsonConfigFile cfg);
}

TEST(JsonConfigFileTest, DefaultReturnsDefaultForString) {
    EQ::JsonConfigFile cfg;
    EXPECT_EQ(cfg.GetVariableString("missing", "key", "default"), "default");
}

TEST(JsonConfigFileTest, DefaultReturnsDefaultForInt) {
    EQ::JsonConfigFile cfg;
    EXPECT_EQ(cfg.GetVariableInt("missing", "key", 99), 99);
}

TEST(JsonConfigFileTest, DefaultReturnsDefaultForBool) {
    EQ::JsonConfigFile cfg;
    EXPECT_EQ(cfg.GetVariableBool("missing", "key", true), true);
}

TEST(JsonConfigFileTest, DefaultReturnsDefaultForDouble) {
    EQ::JsonConfigFile cfg;
    EXPECT_DOUBLE_EQ(cfg.GetVariableDouble("missing", "key", 1.5), 1.5);
}

// ============================================================
// JsonConfigFile — value constructor (populated root)
// ============================================================
TEST(JsonConfigFileValueTest, GetExistingString) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_EQ(cfg.GetVariableString("section", "str_key", "fallback"), "hello");
}

TEST(JsonConfigFileValueTest, GetExistingInt) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_EQ(cfg.GetVariableInt("section", "int_key", 0), 42);
}

TEST(JsonConfigFileValueTest, GetExistingBool) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_TRUE(cfg.GetVariableBool("section", "bool_key", false));
}

TEST(JsonConfigFileValueTest, GetExistingDouble) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_NEAR(cfg.GetVariableDouble("section", "dbl_key", 0.0), 3.14, 0.001);
}

TEST(JsonConfigFileValueTest, MissingSectionReturnsDefault) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_EQ(cfg.GetVariableString("no_section", "str_key", "fallback"), "fallback");
}

TEST(JsonConfigFileValueTest, MissingKeyReturnsDefault) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_EQ(cfg.GetVariableString("section", "no_key", "fallback"), "fallback");
}

TEST(JsonConfigFileValueTest, GetIntFallbackWhenKeyMissing) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_EQ(cfg.GetVariableInt("section", "no_key", -1), -1);
}

TEST(JsonConfigFileValueTest, GetBoolFallbackWhenKeyMissing) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_EQ(cfg.GetVariableBool("section", "no_key", false), false);
}

TEST(JsonConfigFileValueTest, GetDoubleFallbackWhenKeyMissing) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_DOUBLE_EQ(cfg.GetVariableDouble("section", "no_key", -9.9), -9.9);
}

// ============================================================
// JsonConfigFile — RawHandle access
// ============================================================
TEST(JsonConfigFileRawTest, RawHandleReturnsRoot) {
    EQ::JsonConfigFile cfg(MakeTestRoot());
    EXPECT_TRUE(cfg.RawHandle().isMember("section"));
}

TEST(JsonConfigFileRawTest, DefaultRawHandleIsEmpty) {
    EQ::JsonConfigFile cfg;
    EXPECT_TRUE(cfg.RawHandle().empty());
}

// ============================================================
// JsonConfigFile — Load from non-existent file returns empty
// ============================================================
TEST(JsonConfigFileLoadTest, NonexistentFileReturnsEmpty) {
    auto cfg = EQ::JsonConfigFile::Load("/tmp/__eqemu_no_such_file__.json");
    EXPECT_EQ(cfg.GetVariableString("any", "key", "default"), "default");
}

// ============================================================
// net/servertalk_common.h — ServertalkPacketType enum
// ============================================================
TEST(ServertalkPacketTypeTest, ClientHelloIsOne) {
    EXPECT_EQ(EQ::Net::ServertalkPacketType::ServertalkClientHello, 1);
}

TEST(ServertalkPacketTypeTest, ServerHelloIsTwo) {
    EXPECT_EQ(EQ::Net::ServertalkPacketType::ServertalkServerHello, 2);
}

TEST(ServertalkPacketTypeTest, ClientHandshakeIsThree) {
    EXPECT_EQ(EQ::Net::ServertalkPacketType::ServertalkClientHandshake, 3);
}

TEST(ServertalkPacketTypeTest, DowngradeHandshakeIsFour) {
    EXPECT_EQ(EQ::Net::ServertalkPacketType::ServertalkClientDowngradeSecurityHandshake, 4);
}

TEST(ServertalkPacketTypeTest, MessageIsFive) {
    EXPECT_EQ(EQ::Net::ServertalkPacketType::ServertalkMessage, 5);
}

TEST(ServertalkPacketTypeTest, AllDistinct) {
    EXPECT_NE(EQ::Net::ServertalkClientHello,    EQ::Net::ServertalkServerHello);
    EXPECT_NE(EQ::Net::ServertalkServerHello,    EQ::Net::ServertalkClientHandshake);
    EXPECT_NE(EQ::Net::ServertalkClientHandshake, EQ::Net::ServertalkMessage);
}
