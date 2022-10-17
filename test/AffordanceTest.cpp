#include <catch2/catch_test_macros.hpp>

#include "Controller/LuaManager.hpp"
#include "Controller/Affordance/AffordanceSystem.hpp"

TEST_CASE("Affordance system tests", "[AffordanceSystem]") {
	auto& affordance_system = Affordance::AffordanceSystem::get_instance();
	affordance_system.lua_access();

	SECTION("Creating an affordance leaf") {
		auto& lua = LuaManager::get_instance().get_state();

		lua.script(R"(
			function hello()
				return "hello"
			end

			affordance = AffordanceLeaf.new("test", {"test"}, hello)
		)");

		Affordance::AffordanceLeaf affordance = lua["affordance"];
		std::string result = affordance.get_function()();

		REQUIRE(affordance.get_name() == "test");
		REQUIRE(affordance.get_properties() == Affordance::Properties{"test"});
		REQUIRE(result == "hello");
	}

	SECTION("Creating an affordance composite") {
		auto& lua = LuaManager::get_instance().get_state();

		lua.script(R"(
			function hello()
				return "hello"
			end

			affordance = AffordanceComposite.new("test", {"test"})
			affordance:add_affordance(AffordanceLeaf.new("test", {"test"}, hello))
		)");

		Affordance::AffordanceComposite affordance = lua["affordance"];

		REQUIRE(affordance.get_name() == "test");
		REQUIRE(affordance.get_properties() == Affordance::Properties{"test"});
	}
}
