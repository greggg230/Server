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
	emu_constants_test.cpp
	emu_constants2_test.cpp
	emu_versions_test.cpp
	uuid_test.cpp
	strings_misc_test.cpp
	dz_lockout_test.cpp
	strings2_test.cpp
	eq_constants_test.cpp
	eq_constants2_test.cpp
	server_reload_ptimer_test.cpp
	memory_stream_guild_test.cpp
	textures_test.cpp
	faction_test.cpp
	platform_limits_test.cpp
	logsys_md5_test.cpp
	endian_loot_evolving_test.cpp
	net_crc32_cron_test.cpp
	item_data_test.cpp
	argh_misc_test.cpp
	dynamic_zone_types_test.cpp
	event_sub_player_event_test.cpp
	bodytypes_test.cpp
	platform_emulimits_test.cpp
	eqemu_exception_test.cpp
	data_verification_version_test.cpp
	lagged_fibonacci_test.cpp
	opcodes_misc_float_test.cpp
	packet_functions_test.cpp
	emu_opcodes_structs_test.cpp
	exception_constants_test.cpp
	net_util_test.cpp
	file_util_test.cpp
	profanity_rdtsc_test.cpp
	serverinfo_timeoutmgr_test.cpp
	packet_dump_packetfile_test.cpp
	json_config_servertalk_test.cpp
	rof2_limits_test.cpp
	rof_limits_test.cpp
	sod_limits_test.cpp
	uf_limits_test.cpp
	sof_limits_test.cpp
	titanium_limits_test.cpp
	net_packet_test.cpp
	uuid_test.cpp
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
