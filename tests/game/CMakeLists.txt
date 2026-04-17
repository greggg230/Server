cmake_minimum_required(VERSION 3.20)

find_package(GTest REQUIRED)

set(game_tests_sources
	npc_ai_util_test.cpp
)

add_executable(game_tests ${game_tests_sources})

target_include_directories(game_tests PRIVATE
	${CMAKE_SOURCE_DIR}
)

target_link_libraries(game_tests
	GTest::gtest
	GTest::gtest_main
	GTest::gmock
	common
)

if(UNIX)
	target_link_libraries(game_tests pthread dl z m)
	if(NOT DARWIN)
		target_link_libraries(game_tests rt)
	endif()
endif()

include(GoogleTest)
gtest_discover_tests(game_tests)
