#include <catch2/catch_test_macros.hpp>

#include "Controller/LuaManager.hpp"
#include "Controller/Affordance/AffordanceSystem.hpp"
#include "Controller/Affordance/AffordanceHelper.hpp"

auto lua_script(const std::string& script) -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto result = lua.safe_script(script, sol::script_pass_on_error);
	if (!result.valid()) {
		FAIL(result.get<sol::error>().what());
	}
}

TEST_CASE("Affordance composite tests", "[AffordanceComposite]") {
	auto& affordance_system = Affordance::AffordanceSystem::get_instance();
	affordance_system.lua_access();

	SECTION("Creating an affordance leaf") {
		auto& lua = LuaManager::get_instance().get_state();

		lua_script(R"(
			function hello()
				return "hello"
			end

			affordance = AffordanceLeaf.new("test", {"test"}, hello)
		)");

		std::shared_ptr<Affordance::AffordanceLeaf>& affordance =
		    lua["affordance"];

		std::string result = affordance->get_function()();

		REQUIRE(affordance.use_count() == 1);
		REQUIRE(affordance->get_name() == "test");
		REQUIRE(affordance->get_properties() == Affordance::Properties{"test"});
		REQUIRE(affordance->is_composite() == false);
		REQUIRE(result == "hello");
	}

	SECTION("Creating an affordance composite") {
		auto& lua = LuaManager::get_instance().get_state();

		lua_script(R"(
			function hello()
				return "hello"
			end

			affordance = AffordanceComposite.new("test", {"test"}, {AffordanceLeaf.new("test", {"test"}, hello)})
		)");

		std::shared_ptr<Affordance::AffordanceComposite>& affordance =
		    lua["affordance"];

		REQUIRE(affordance.use_count() == 1);
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

		lua_script(R"(
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
		)");

		std::shared_ptr<Affordance::AffordanceComposite>& sitting_affordance =
		    lua["sitting_affordance"];

		REQUIRE(sitting_affordance.use_count() == 1);

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
		lua_script(R"(
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

			local sitting_affordance = AffordanceComposite.new("Sitting", {"Sitting"}, {
				AffordanceLeaf.new("Sit default", {}, sit),
				AffordanceComposite.new("Human", {"Human"}, {
					AffordanceLeaf.new("Crossleg", {"Crossleg"}, sit_crosslegged),
					AffordanceLeaf.new("Straight", {"Straight"}, sit_straight)
				})
			})

			local chair_affordance = AffordanceComposite.new("Chair", {}, {
				sitting_affordance,
				AffordanceLeaf.new("Stand", {"Stand"}, stand)
			})

			AffordanceSystem.set_affordance("chair", chair_affordance);

			chair_affordance = nil
			sitting_affordance = nil
			collectgarbage()
		)");

		auto chair = std::dynamic_pointer_cast<Affordance::AffordanceComposite>(
		    affordance_system.get_affordance("chair"));

		REQUIRE(chair.use_count() == 2);
		REQUIRE(chair->get_name() == "Chair");
		REQUIRE(chair->get_properties().empty());
		REQUIRE(chair->is_composite() == true);

		auto sitting_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceComposite>(
		        chair->get_affordances()[0]);

		REQUIRE(sitting_affordance.use_count() == 2);
		REQUIRE(sitting_affordance->get_name() == "Sitting");
		REQUIRE(sitting_affordance->get_properties() ==
		        Affordance::Properties{"Sitting"});
		REQUIRE(sitting_affordance->is_composite() == true);

		auto stand_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(
		        chair->get_affordances()[1]);

		REQUIRE(stand_affordance.use_count() == 2);
		REQUIRE(stand_affordance->get_name() == "Stand");
		REQUIRE(stand_affordance->get_properties() ==
		        Affordance::Properties{"Stand"});
		REQUIRE(stand_affordance->is_composite() == false);

		std::string stand_result = stand_affordance->get_function()();
		REQUIRE(stand_result == "standing");

		affordance_system.clear_affordances();
	}

	SECTION("Finding an object with given properties") {
		lua_script(R"(
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

			local sitting_affordance = AffordanceComposite.new("Sitting", {"Sitting"}, {
				AffordanceLeaf.new("Sit default", {}, sit),
				AffordanceComposite.new("Human", {"Human"}, {
					AffordanceLeaf.new("Crossleg", {"Crossleg"}, sit_crosslegged),
					AffordanceLeaf.new("Straight", {"Straight"}, sit_straight)
				})
			})

			local chair_affordance = AffordanceComposite.new("Chair", {}, {
				sitting_affordance,
				AffordanceLeaf.new("Stand", {"Stand"}, stand)
			})

			AffordanceSystem.set_affordance("chair", chair_affordance);

			chair_affordance = nil
			sitting_affordance = nil
			collectgarbage()
		)");

		auto objects = affordance_system.find_objects({"Stand"});

		REQUIRE(objects.size() == 1);
		REQUIRE(objects[0]->is_composite() == true);

		auto chair = std::dynamic_pointer_cast<Affordance::AffordanceComposite>(
		    objects[0]);

		REQUIRE(chair->get_name() == "Chair");
		REQUIRE(chair->get_properties().empty());
		REQUIRE(chair->is_composite() == true);

		auto stand_affordance =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(
		        chair->get_affordances()[1]);

		REQUIRE(stand_affordance->get_name() == "Stand");
		REQUIRE(stand_affordance->get_properties() ==
		        Affordance::Properties{"Stand"});
		REQUIRE(stand_affordance->is_composite() == false);

		std::string stand_result = stand_affordance->get_function()();
		REQUIRE(stand_result == "standing");
	}
}

TEST_CASE("Affordance helper functions test", "[AffordanceHelper]") {
	auto& affordance_system = Affordance::AffordanceSystem::get_instance();
	affordance_system.lua_access();

	SECTION("Finding affordances given properties") {
		lua_script(R"(
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

			local sitting_affordance = AffordanceComposite.new("Sitting", {"Sitting"}, {
				AffordanceLeaf.new("Sit default", {}, sit),
				AffordanceComposite.new("Human", {"Human"}, {
					AffordanceLeaf.new("Crossleg", {"Crossleg"}, sit_crosslegged),
					AffordanceLeaf.new("Straight", {"Straight"}, sit_straight)
				})
			})

			local chair_affordance = AffordanceComposite.new("Chair", {}, {
				sitting_affordance,
				AffordanceLeaf.new("Stand", {"Stand"}, stand)
			})

			AffordanceSystem.set_affordance("chair", chair_affordance);

			chair_affordance = nil
			sitting_affordance = nil
			collectgarbage()
		)");

		auto affordance = Affordance::find_affordance(
		    affordance_system.get_affordance("chair"),
		    {"Sitting", "Human", "Crossleg"}, {});

		REQUIRE(affordance->is_composite() == false);
		auto affordance_leaf =
		    std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(affordance);

		REQUIRE(affordance_leaf->get_name() == "Sit default");
		REQUIRE(affordance_leaf->get_properties() == Affordance::Properties{});

		std::string affordance_result = affordance_leaf->get_function()();
		REQUIRE(affordance_result == "sitting");

		auto chair = std::dynamic_pointer_cast<Affordance::AffordanceComposite>(
		    affordance_system.get_affordance("chair"));

		REQUIRE(chair->is_composite());
		REQUIRE(chair->get_properties().empty());
		REQUIRE(chair->get_affordances().size() == 2);

		affordance_system.clear_affordances();
	}

	SECTION("Finding a composite with no children") {
		lua_script(R"(
			function sit() 
				return "sitting"
			end

			function sit_crosslegged()
				return sit() .. " crosslegged"
			end

			function sit_straight()
				return sit() .. " straight"
			end

			local sitting_affordance = AffordanceComposite.new("Sitting", {"Sitting"}, {
				AffordanceLeaf.new("Sit default", {}, sit),
				AffordanceComposite.new("Human", {"Human"}, {
					AffordanceLeaf.new("Crossleg", {"Crossleg"}, sit_crosslegged),
					AffordanceLeaf.new("Straight", {"Straight"}, sit_straight)
				})
			})

			local chair_affordance = AffordanceComposite.new("Chair", {}, {
				sitting_affordance,
				AffordanceComposite.new("Alien", {"Alien"}, {})
			})

			AffordanceSystem.set_affordance("chair", chair_affordance);

			chair_affordance = nil
			sitting_affordance = nil
			collectgarbage()
		)");

		auto affordance = Affordance::find_affordance(
		    affordance_system.get_affordance("chair"), {"Alien"}, {});

		REQUIRE(affordance->is_composite() == true);
		auto affordance_composite =
		    std::dynamic_pointer_cast<Affordance::AffordanceComposite>(
		        affordance);

		REQUIRE(affordance_composite->get_name() == "Alien");
		REQUIRE(affordance_composite->get_properties() ==
		        Affordance::Properties{"Alien"});
		REQUIRE(affordance_composite->get_affordances().empty());

		affordance_system.clear_affordances();
	}
}
