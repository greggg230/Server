cmake_minimum_required(VERSION 3.20)

find_package(GTest REQUIRED)

set(game_tests_sources
	npc_ai_util_test.cpp
	seperator_test.cpp
	random_test.cpp
	checksum_test.cpp
	compression_test.cpp
	strings_test.cpp
	npc_spell_decider_test.cpp
	legacy_strings_test.cpp
	math_util_test.cpp
	eqtime_test.cpp
	fixed_hash_set_test.cpp
	memory_buffer_test.cpp
	eqrand_test.cpp
	ip_util_test.cpp
	class_util_test.cpp
	bodytype_deity_test.cpp
	light_source_test.cpp
	races_test.cpp
	fixed_var_hash_set_test.cpp
	serialize_buffer_test.cpp
	queue_test.cpp
	skills_test.cpp
	linked_list_test.cpp
	misc_test.cpp
	timer_test.cpp
	eq_coord_test.cpp
	data_util_test.cpp
	inventory_slot_test.cpp
	classes_test.cpp
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
