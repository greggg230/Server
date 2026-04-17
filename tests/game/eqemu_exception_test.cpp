#include <gtest/gtest.h>
#include "common/eqemu_exception.h"

#include <stdexcept>
#include <string>

// ============================================================
// EQ::Exception construction and accessors
// ============================================================
TEST(EQExceptionTest, NameIsStored) {
    EQ::Exception ex("TestException", "something went wrong", __FILE__, __LINE__);
    EXPECT_EQ(ex.name(), "TestException");
}

TEST(EQExceptionTest, DescriptionIsStored) {
    EQ::Exception ex("E", "my description", __FILE__, __LINE__);
    EXPECT_EQ(ex.description(), "my description");
}

TEST(EQExceptionTest, FileIsStored) {
    const char* f = "test_file.cpp";
    EQ::Exception ex("E", "d", f, 42);
    EXPECT_EQ(ex.file(), f);
}

TEST(EQExceptionTest, LineIsStored) {
    EQ::Exception ex("E", "d", __FILE__, 99);
    EXPECT_EQ(ex.line(), 99L);
}

TEST(EQExceptionTest, FullDescriptionContainsName) {
    EQ::Exception ex("MyException", "desc", __FILE__, 1);
    const std::string& fd = ex.full_description();
    EXPECT_NE(fd.find("MyException"), std::string::npos);
}

TEST(EQExceptionTest, FullDescriptionContainsDescription) {
    EQ::Exception ex("E", "detailed description", __FILE__, 1);
    const std::string& fd = ex.full_description();
    EXPECT_NE(fd.find("detailed description"), std::string::npos);
}

TEST(EQExceptionTest, FullDescriptionContainsLine) {
    EQ::Exception ex("E", "d", __FILE__, 1234);
    const std::string& fd = ex.full_description();
    EXPECT_NE(fd.find("1234"), std::string::npos);
}

TEST(EQExceptionTest, WhatReturnsFullDescription) {
    EQ::Exception ex("E", "desc", __FILE__, 5);
    std::string what_str(ex.what());
    EXPECT_FALSE(what_str.empty());
    EXPECT_EQ(what_str, ex.full_description());
}

// ============================================================
// EQ::Exception — inheritance from std::exception
// ============================================================
TEST(EQExceptionTest, CatchableAsStdException) {
    bool caught = false;
    try {
        throw EQ::Exception("TestEx", "caught as std::exception", __FILE__, __LINE__);
    } catch (const std::exception& e) {
        caught = true;
        EXPECT_NE(std::string(e.what()).find("caught as std::exception"), std::string::npos);
    }
    EXPECT_TRUE(caught);
}

TEST(EQExceptionTest, CatchableAsEQException) {
    bool caught = false;
    try {
        throw EQ::Exception("TestEx", "msg", __FILE__, __LINE__);
    } catch (const EQ::Exception& e) {
        caught = true;
        EXPECT_EQ(e.name(), "TestEx");
    }
    EXPECT_TRUE(caught);
}

// ============================================================
// EQ::Exception — copy constructor
// ============================================================
TEST(EQExceptionCopyTest, CopiedNameMatches) {
    EQ::Exception orig("OrigName", "desc", __FILE__, 10);
    EQ::Exception copy(orig);
    EXPECT_EQ(copy.name(), orig.name());
}

TEST(EQExceptionCopyTest, CopiedDescriptionMatches) {
    EQ::Exception orig("N", "orig desc", __FILE__, 10);
    EQ::Exception copy(orig);
    EXPECT_EQ(copy.description(), orig.description());
}

TEST(EQExceptionCopyTest, CopiedLineMatches) {
    EQ::Exception orig("N", "d", __FILE__, 77);
    EQ::Exception copy(orig);
    EXPECT_EQ(copy.line(), orig.line());
}

// ============================================================
// EQ_EXCEPT macro
// ============================================================
TEST(EQExceptMacroTest, MacroThrowsEQException) {
    EXPECT_THROW(EQ_EXCEPT("MacroTest", "thrown via macro"), EQ::Exception);
}

TEST(EQExceptMacroTest, MacroExceptionHasCorrectName) {
    try {
        EQ_EXCEPT("MacroName", "macro desc");
        FAIL() << "Expected EQ::Exception";
    } catch (const EQ::Exception& e) {
        EXPECT_EQ(e.name(), "MacroName");
        EXPECT_EQ(e.description(), "macro desc");
    }
}
