#include <catch2/catch_test_macros.hpp>

#include "Controller/LuaManager.hpp"
#include "Controller/Affordance/AffordanceSystem.hpp"

TEST_CASE("Affordance system tests", "[AffordanceSystem]") {
	SECTION("Creating an affordance") {
		auto& lua = LuaManager::get_instance().get_state();
	}
}