#include <gtest/gtest.h>
#include <stdexcept>
#include "common/eqemu_exception.h"
#include "common/emu_constants.h"

// ============================================================
// EQ::Exception
// ============================================================
TEST(ExceptionTest, ConstructorStoresName) {
    EQ::Exception e("TestException", "Something went wrong", __FILE__, __LINE__);
    EXPECT_EQ(e.name(), "TestException");
}

TEST(ExceptionTest, ConstructorStoresDescription) {
    EQ::Exception e("TestException", "detailed message", __FILE__, __LINE__);
    EXPECT_EQ(e.description(), "detailed message");
}

TEST(ExceptionTest, ConstructorStoresFile) {
    const char* file = "myfile.cpp";
    EQ::Exception e("E", "d", file, 42);
    EXPECT_EQ(e.file(), file);
}

TEST(ExceptionTest, ConstructorStoresLine) {
    EQ::Exception e("E", "d", __FILE__, 99);
    EXPECT_EQ(e.line(), 99L);
}

TEST(ExceptionTest, FullDescriptionContainsNameAndDescription) {
    EQ::Exception e("MyError", "bad thing happened", "foo.cpp", 7);
    const std::string& fd = e.full_description();
    EXPECT_NE(fd.find("MyError"), std::string::npos);
    EXPECT_NE(fd.find("bad thing happened"), std::string::npos);
}

TEST(ExceptionTest, WhatReturnsCString) {
    EQ::Exception e("MyError", "desc", "file.cpp", 1);
    const char* w = e.what();
    EXPECT_NE(w, nullptr);
    EXPECT_GT(strlen(w), 0u);
}

TEST(ExceptionTest, InheritsFromStdException) {
    bool caught = false;
    try {
        throw EQ::Exception("Test", "message", __FILE__, __LINE__);
    } catch (const std::exception&) {
        caught = true;
    }
    EXPECT_TRUE(caught);
}

TEST(ExceptionTest, CopyConstructorPreservesFields) {
    EQ::Exception orig("OrigName", "OrigDesc", "orig.cpp", 55);
    EQ::Exception copy(orig);
    EXPECT_EQ(copy.name(), "OrigName");
    EXPECT_EQ(copy.description(), "OrigDesc");
    EXPECT_EQ(copy.file(), "orig.cpp");
    EXPECT_EQ(copy.line(), 55L);
}

TEST(ExceptionTest, EQ_EXCEPT_MacroThrows) {
    EXPECT_THROW(EQ_EXCEPT("TestError", "triggered via macro"), EQ::Exception);
}

// ============================================================
// SpecialAbility::GetName / IsValid
// ============================================================
TEST(SpecialAbilityTest, IsValidKnownAbilities) {
    EXPECT_TRUE(SpecialAbility::IsValid(SpecialAbility::Summon));
    EXPECT_TRUE(SpecialAbility::IsValid(SpecialAbility::Enrage));
    EXPECT_TRUE(SpecialAbility::IsValid(SpecialAbility::Rampage));
    EXPECT_TRUE(SpecialAbility::IsValid(SpecialAbility::Flurry));
}

TEST(SpecialAbilityTest, IsValidUnknown) {
    EXPECT_FALSE(SpecialAbility::IsValid(-1));
    EXPECT_FALSE(SpecialAbility::IsValid(999));
}

TEST(SpecialAbilityTest, GetNameKnownAbilities) {
    EXPECT_EQ(SpecialAbility::GetName(SpecialAbility::Summon),   "Summon");
    EXPECT_EQ(SpecialAbility::GetName(SpecialAbility::Enrage),   "Enrage");
    EXPECT_EQ(SpecialAbility::GetName(SpecialAbility::Rampage),  "Rampage");
    EXPECT_EQ(SpecialAbility::GetName(SpecialAbility::Flurry),   "Flurry");
}

TEST(SpecialAbilityTest, GetNameUnknownReturnsDefault) {
    EXPECT_EQ(SpecialAbility::GetName(999), "UNKNOWN SPECIAL ABILITY");
}

// ============================================================
// PetCommand::GetName / IsValid
// ============================================================
TEST(PetCommandTest, IsValidKnownCommands) {
    EXPECT_TRUE(PetCommand::IsValid(PetCommand::Attack));
    EXPECT_TRUE(PetCommand::IsValid(PetCommand::FollowMe));
    EXPECT_TRUE(PetCommand::IsValid(PetCommand::GetLost));
    EXPECT_TRUE(PetCommand::IsValid(PetCommand::Taunt));
}

TEST(PetCommandTest, IsValidUnknown) {
    EXPECT_FALSE(PetCommand::IsValid(200));
}

TEST(PetCommandTest, GetNameKnownCommands) {
    EXPECT_EQ(PetCommand::GetName(PetCommand::Attack),   "Attack");
    EXPECT_EQ(PetCommand::GetName(PetCommand::FollowMe), "Follow Me");
    EXPECT_EQ(PetCommand::GetName(PetCommand::GetLost),  "Get Lost");
    EXPECT_EQ(PetCommand::GetName(PetCommand::Taunt),    "Taunt");
    EXPECT_EQ(PetCommand::GetName(PetCommand::Sit),      "Sit");
}

TEST(PetCommandTest, GetNameUnknownReturnsDefault) {
    EXPECT_EQ(PetCommand::GetName(200), "UNKNOWN PET COMMAND");
}

// ============================================================
// EQ::constants::GetConsiderColorName
// ============================================================
TEST(ConsiderColorNameTest, KnownColors) {
    EXPECT_EQ(EQ::constants::GetConsiderColorName(ConsiderColor::Green),    "Green");
    EXPECT_EQ(EQ::constants::GetConsiderColorName(ConsiderColor::Red),      "Red");
    EXPECT_EQ(EQ::constants::GetConsiderColorName(ConsiderColor::Yellow),   "Yellow");
    EXPECT_EQ(EQ::constants::GetConsiderColorName(ConsiderColor::LightBlue),"Light Blue");
}

TEST(ConsiderColorNameTest, UnknownColorReturnsEmpty) {
    EXPECT_EQ(EQ::constants::GetConsiderColorName(999), "");
}

// ============================================================
// EQ::constants::GetEmoteEventTypeName / GetEmoteTypeName
// ============================================================
TEST(EmoteTypeNameTest, EmoteEventTypes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetEmoteEventTypeName(EmoteEventTypes::LeaveCombat), "Leave Combat");
    EXPECT_EQ(GetEmoteEventTypeName(EmoteEventTypes::EnterCombat), "Enter Combat");
    EXPECT_EQ(GetEmoteEventTypeName(EmoteEventTypes::OnDeath),     "On Death");
    EXPECT_EQ(GetEmoteEventTypeName(EmoteEventTypes::Hailed),      "Hailed");
}

TEST(EmoteTypeNameTest, EmoteEventTypeOutOfRange) {
    EXPECT_EQ(EQ::constants::GetEmoteEventTypeName(99), "");
}

TEST(EmoteTypeNameTest, EmoteTypes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetEmoteTypeName(EmoteTypes::Say),       "Say");
    EXPECT_EQ(GetEmoteTypeName(EmoteTypes::Emote),     "Emote");
    EXPECT_EQ(GetEmoteTypeName(EmoteTypes::Shout),     "Shout");
    EXPECT_EQ(GetEmoteTypeName(EmoteTypes::Proximity), "Proximity");
}

TEST(EmoteTypeNameTest, EmoteTypeOutOfRange) {
    EXPECT_EQ(EQ::constants::GetEmoteTypeName(99), "");
}
