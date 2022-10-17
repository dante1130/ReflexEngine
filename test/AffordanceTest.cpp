#include <catch2/catch_test_macros.hpp>

#include "Controller/LuaManager.hpp"
#include "Controller/Affordance/AffordanceSystem.hpp"

TEST_CASE("Affordance system tests", "[AffordanceSystem]") {
	auto& affordance_system = Affordance::AffordanceSystem::get_instance();
	affordance_system.lua_access();

	SECTION("Creating an affordance leaf") {
		auto& lua = LuaManager::get_instance().get_state();

		sol::optional<sol::error> maybe_error =
		    lua.safe_script(R"(
			function hello()
				return "hello"
			end

			affordance = AffordanceLeaf.new("test", {"test"}, hello)
		)",
		                    sol::script_pass_on_error);

		if (maybe_error) {
			FAIL(maybe_error.value().what());
		}

		std::shared_ptr<Affordance::AffordanceLeaf> affordance =
		    lua["affordance"];
		std::string result = affordance->get_function()();

		REQUIRE(affordance->get_name() == "test");
		REQUIRE(affordance->get_properties() == Affordance::Properties{"test"});
		REQUIRE(result == "hello");
	}

	SECTION("Creating an affordance composite") {
		auto& lua = LuaManager::get_instance().get_state();

		sol::optional<sol::error> maybe_error =
		    lua.safe_script(R"(
			function hello()
				return "hello"
			end

			affordance = AffordanceComposite.new("test", {"test"}, {AffordanceLeaf.new("test", {"test"}, hello)})
		)",
		                    sol::script_pass_on_error);

		if (maybe_error) {
			FAIL(maybe_error.value().what());
		}

		std::shared_ptr<Affordance::AffordanceComposite> affordance =
		    lua["affordance"];

		REQUIRE(affordance->get_name() == "test");
		REQUIRE(affordance->get_properties() == Affordance::Properties{"test"});

		const auto& children = affordance->get_affordances();

		REQUIRE(children.size() == 1);
	}
}
