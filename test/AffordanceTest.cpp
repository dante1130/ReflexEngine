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
		REQUIRE(affordance->is_composite() == false);
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
		REQUIRE(affordance->is_composite() == true);

		const auto& children = affordance->get_affordances();

		REQUIRE(children.size() == 1);

		auto leaf_child =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(children[0]);

		std::string result = leaf_child->get_function()();

		REQUIRE(leaf_child->get_name() == "test");
		REQUIRE(leaf_child->get_properties() == Affordance::Properties{"test"});
		REQUIRE(leaf_child->is_composite() == false);
		REQUIRE(result == "hello");
	}

	SECTION("Creating a nested affordance") {
		auto& lua = LuaManager::get_instance().get_state();

		sol::optional<sol::error> maybe_error =
		    lua.safe_script(R"(
			function sit() 
				return "sitting"
			end

			function sit_crosslegged()
				return sit() .. " crosslegged"
			end

			function sit_straight()
				return sit() .. " straight"
			end

			function stand()
				return "standing"
			end

			sitting_affordance = AffordanceComposite.new("Sitting", {"Sitting"}, {
				AffordanceLeaf.new("Sit default", {}, sit),
				AffordanceComposite.new("Human", {"Human"}, {
					AffordanceLeaf.new("Crossleg", {"Crossleg"}, sit_crosslegged),
					AffordanceLeaf.new("Straight", {"Straight"}, sit_straight)
				})
			})

			sitting_affordance:add_affordance(AffordanceLeaf.new("Stand", {"Stand"}, stand))
		)",
		                    sol::script_pass_on_error);

		if (maybe_error) {
			FAIL(maybe_error.value().what());
		}

		std::shared_ptr<Affordance::AffordanceComposite> sitting_affordance =
		    lua["sitting_affordance"];

		REQUIRE(sitting_affordance->get_name() == "Sitting");
		REQUIRE(sitting_affordance->get_properties() ==
		        Affordance::Properties{"Sitting"});
		REQUIRE(sitting_affordance->is_composite() == true);

		const auto& chair_children = sitting_affordance->get_affordances();
		REQUIRE(chair_children.size() == 3);

		auto sit_default_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(
		        chair_children[0]);

		REQUIRE(sit_default_affordance->get_name() == "Sit default");
		REQUIRE(sit_default_affordance->get_properties().empty());
		REQUIRE(sit_default_affordance->is_composite() == false);

		std::string sitting_result = sit_default_affordance->get_function()();
		REQUIRE(sitting_result == "sitting");

		auto human_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceComposite>(
		        chair_children[1]);

		REQUIRE(human_affordance->get_name() == "Human");
		REQUIRE(human_affordance->get_properties() ==
		        Affordance::Properties{"Human"});
		REQUIRE(human_affordance->is_composite() == true);

		const auto& human_children = human_affordance->get_affordances();

		REQUIRE(human_children.size() == 2);

		auto crossleg_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(
		        human_children[0]);

		REQUIRE(crossleg_affordance->get_name() == "Crossleg");
		REQUIRE(crossleg_affordance->get_properties() ==
		        Affordance::Properties{"Crossleg"});
		REQUIRE(crossleg_affordance->is_composite() == false);

		std::string crossleg_result = crossleg_affordance->get_function()();
		REQUIRE(crossleg_result == "sitting crosslegged");

		auto straight_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(
		        human_children[1]);

		REQUIRE(straight_affordance->get_name() == "Straight");
		REQUIRE(straight_affordance->get_properties() ==
		        Affordance::Properties{"Straight"});
		REQUIRE(straight_affordance->is_composite() == false);

		std::string straight_result = straight_affordance->get_function()();
		REQUIRE(straight_result == "sitting straight");

		auto stand_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(
		        chair_children[2]);

		REQUIRE(stand_affordance->get_name() == "Stand");
		REQUIRE(stand_affordance->get_properties() ==
		        Affordance::Properties{"Stand"});
		REQUIRE(stand_affordance->is_composite() == false);

		std::string stand_result = stand_affordance->get_function()();
		REQUIRE(stand_result == "standing");
	}

	SECTION("Storing an affordance in the AffordanceSystem") {
		auto& lua = LuaManager::get_instance().get_state();

		sol::optional<sol::error> maybe_error =
		    lua.safe_script(R"(
			function sit() 
				return "sitting"
			end

			function sit_crosslegged()
				return sit() .. " crosslegged"
			end

			function sit_straight()
				return sit() .. " straight"
			end

			function stand()
				return "standing"
			end

			sitting_affordance = AffordanceComposite.new("Sitting", {"Sitting"}, {
				AffordanceLeaf.new("Sit default", {}, sit),
				AffordanceComposite.new("Human", {"Human"}, {
					AffordanceLeaf.new("Crossleg", {"Crossleg"}, sit_crosslegged),
					AffordanceLeaf.new("Straight", {"Straight"}, sit_straight)
				})
			})

			sitting_affordance:add_affordance(AffordanceLeaf.new("Stand", {"Stand"}, stand))

			AffordanceSystem.set_affordance("chair", sitting_affordance);
		)",
		                    sol::script_pass_on_error);

		if (maybe_error) {
			FAIL(maybe_error.value().what());
		}
	}
}
