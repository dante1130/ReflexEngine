#include <catch2/catch_test_macros.hpp>

#include "Controller/LuaManager.hpp"
#include "Controller/Affordance/AffordanceSystem.hpp"

TEST_CASE("Affordance system tests", "[AffordanceSystem]") {
	auto& affordance_system = Affordance::AffordanceSystem::get_instance();
	affordance_system.lua_access();

	SECTION("Creating an affordance") {
		auto& lua = LuaManager::get_instance().get_state();

		lua.script(R"(
			function print_hello()
				print("Hello")
			end

			print_hello()
			local affordance = AffordanceLeaf.new("test", {"test"}, print_hello)
			print_hello()
		)");
	}
}