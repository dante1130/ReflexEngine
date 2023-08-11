#include <catch2/catch_test_macros.hpp>

#include "Controller/GUI/PerformanceLoggerGUI.hpp"
#include <string>

TEST_CASE("Performance Logger tests", "[PERFORMANCELOGGER]") {
	std::vector<Performance_Log> logs;

	SECTION("Able to log performance") {
		PERFORMANCE_LOGGER_PUSH("test");
		PERFORMANCE_LOGGER_POP();

		logs = PerformanceLogger::GetLogs();
		REQUIRE(logs.size() == 1);
		REQUIRE(std::strcmp(logs[0].name.c_str(), "test") == 0);
		REQUIRE(logs[0].time_taken >= 0);
		REQUIRE(logs[0].indent == 0);

		PerformanceLogger::ForceClearLogs();
	}

	SECTION("Able to clear old logs") {
		PERFORMANCE_LOGGER_PUSH("test");
		PERFORMANCE_LOGGER_POP();

		PerformanceLogger::ClearLogs();
		logs = PerformanceLogger::GetLogs();
		REQUIRE(logs.empty());
	}

	SECTION("Able to log multiple performances on same indent") {
		PERFORMANCE_LOGGER_PUSH("test_one");
		PERFORMANCE_LOGGER_POP();
		PERFORMANCE_LOGGER_PUSH("test_two");
		PERFORMANCE_LOGGER_POP();
		PERFORMANCE_LOGGER_PUSH("test_three");
		PERFORMANCE_LOGGER_POP();
		PERFORMANCE_LOGGER_PUSH("test_four");
		PERFORMANCE_LOGGER_POP();

		logs = PerformanceLogger::GetLogs();
		REQUIRE(logs.size() == 4);
		REQUIRE(std::strcmp(logs[0].name.c_str(), "test_one") == 0);
		REQUIRE(logs[0].time_taken >= 0);
		REQUIRE(logs[0].indent == 0);
		REQUIRE(std::strcmp(logs[1].name.c_str(), "test_two") == 0);
		REQUIRE(logs[1].time_taken >= 0);
		REQUIRE(logs[1].indent == 0);
		REQUIRE(std::strcmp(logs[2].name.c_str(), "test_three") == 0);
		REQUIRE(logs[2].time_taken >= 0);
		REQUIRE(logs[2].indent == 0);
		REQUIRE(std::strcmp(logs[3].name.c_str(), "test_four") == 0);
		REQUIRE(logs[3].time_taken >= 0);
		REQUIRE(logs[3].indent == 0);

		PerformanceLogger::ForceClearLogs();
	}

	SECTION("Able to log recursively") {
		PERFORMANCE_LOGGER_PUSH("test_one");
		PERFORMANCE_LOGGER_PUSH("test_two");
		PERFORMANCE_LOGGER_PUSH("test_three");
		PERFORMANCE_LOGGER_POP();
		PERFORMANCE_LOGGER_PUSH("test_four");
		PERFORMANCE_LOGGER_POP();
		PERFORMANCE_LOGGER_POP();
		PERFORMANCE_LOGGER_POP();
		PERFORMANCE_LOGGER_PUSH("test_five");
		PERFORMANCE_LOGGER_POP();

		logs = PerformanceLogger::GetLogs();
		REQUIRE(logs.size() == 5);

		REQUIRE(std::strcmp(logs[0].name.c_str(), "test_one") == 0);
		REQUIRE(logs[0].time_taken >= 0);
		REQUIRE(logs[0].indent == 0);
		REQUIRE(std::strcmp(logs[1].name.c_str(), "test_two") == 0);
		REQUIRE(logs[1].time_taken >= 0);
		REQUIRE(logs[1].indent == 1);
		REQUIRE(std::strcmp(logs[2].name.c_str(), "test_three") == 0);
		REQUIRE(logs[2].time_taken >= 0);
		REQUIRE(logs[2].indent == 2);
		REQUIRE(std::strcmp(logs[3].name.c_str(), "test_four") == 0);
		REQUIRE(logs[3].time_taken >= 0);
		REQUIRE(logs[3].indent == 2);
		REQUIRE(std::strcmp(logs[4].name.c_str(), "test_five") == 0);
		REQUIRE(logs[4].time_taken >= 0);
		REQUIRE(logs[4].indent == 0);

		PerformanceLogger::ForceClearLogs();
	}
}