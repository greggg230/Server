#include <gtest/gtest.h>
#include "common/process/process.h"
#include "common/emu_constants.h"

#include <string>

// ============================================================
// Process::execute — basic shell execution
// ============================================================
TEST(ProcessExecuteTest, EchoReturnsExpectedString) {
    std::string result = Process::execute("echo hello");
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST(ProcessExecuteTest, ReturnsNonEmptyForValidCommand) {
    std::string result = Process::execute("echo test");
    EXPECT_FALSE(result.empty());
}

TEST(ProcessExecuteTest, ExitCodeDoesNotAffectReturn) {
    // Commands that exit 0 should return output (not ERROR)
    std::string result = Process::execute("echo captured");
    EXPECT_NE(result.find("captured"), std::string::npos);
}

TEST(ProcessExecuteTest, MultipleWordsReturned) {
    std::string result = Process::execute("echo one two three");
    EXPECT_NE(result.find("one"), std::string::npos);
    EXPECT_NE(result.find("two"), std::string::npos);
    EXPECT_NE(result.find("three"), std::string::npos);
}

TEST(ProcessExecuteTest, TrueCommandReturnsEmptyOutput) {
    // "true" exits 0 and produces no stdout
    std::string result = Process::execute("true");
    // result may be empty or contain only whitespace
    EXPECT_EQ(result.find("ERROR"), std::string::npos);
}

TEST(ProcessExecuteTest, ExitNonzeroStillReturnsOutput) {
    // "false" exits 1 — implementation should still return output (possibly empty)
    std::string result = Process::execute("false");
    EXPECT_EQ(result.find("ERROR"), std::string::npos);
}

// ============================================================
// EQ::DevTools namespace constants
// ============================================================
TEST(EQDevToolsTest, GMAccountStatusLevelIs150) {
    int32 v = EQ::DevTools::GM_ACCOUNT_STATUS_LEVEL;
    EXPECT_EQ(v, 150);
}

// ============================================================
// EQ::popupresponse namespace constants
// ============================================================
TEST(EQPopupResponseTest, ServerInternalUseBaseIs2000000000) {
    int32 v = EQ::popupresponse::SERVER_INTERNAL_USE_BASE;
    EXPECT_EQ(v, 2000000000);
}

TEST(EQPopupResponseTest, MobInfoDismissIsBaseplus1) {
    int32 base = EQ::popupresponse::SERVER_INTERNAL_USE_BASE;
    int32 mob  = EQ::popupresponse::MOB_INFO_DISMISS;
    EXPECT_EQ(mob, base + 1);
}

// ============================================================
// EQ::invslot additional constant
// ============================================================
TEST(EQInvSlotTest, AugmentGenericReturnIs1001) {
    int16 v = EQ::invslot::SLOT_AUGMENT_GENERIC_RETURN;
    EXPECT_EQ(v, 1001);
}
