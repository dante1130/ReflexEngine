#include <catch2/catch_test_macros.hpp>

#include "Controller/GUI/CollectionsGUI.hpp"
#include <unordered_map>
#include <string>
#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"

TEST_CASE("Collection tests", "[COLLECTIONS]") {
	CollectionsGUI::clear_collections();
	std::unordered_map<int, Collection> collections;
	Collection temp_collection;
	std::unordered_map<int, Collection>::iterator col_itr;
	std::string warning_rm = "na";
	ECS ecs;

	SECTION("Add collection") {
		CollectionsGUI::add_collection("test", -1);    // id 0
		CollectionsGUI::add_collection("testTwo", 1);  // id 1
		collections = CollectionsGUI::get_collection_hierarchy();

		col_itr = collections.find(0);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("test", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
		}

		col_itr = collections.find(1);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("testTwo", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
		}

		CollectionsGUI::clear_collections();
	}

	SECTION("Rename collection") {
		CollectionsGUI::add_collection("test", -1);  // id 0
		CollectionsGUI::rename_collection("new_name", 0);
		collections = CollectionsGUI::get_collection_hierarchy();

		col_itr = collections.find(0);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("new_name", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
		}

		CollectionsGUI::clear_collections();
	}

	SECTION("Collection simple recursion") {
		CollectionsGUI::add_collection("parent", -1);  // id 0
		CollectionsGUI::add_collection("child", 0);    // id 1
		collections = CollectionsGUI::get_collection_hierarchy();

		col_itr = collections.find(0);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("parent", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
			if (col_itr->second.child_ids.empty()) {
				REQUIRE(std::strcmp("Collection has zero children",
				                    warning_rm.c_str()) != 0);
			} else {
				REQUIRE(col_itr->second.child_ids[0] == 1);
			}
		}

		col_itr = collections.find(1);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("child", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == 0);
			REQUIRE(col_itr->second.child_ids.empty());
		}

		CollectionsGUI::clear_collections();
	}

	SECTION("Collection recursion") {
		CollectionsGUI::add_collection("parent", -1);            // id 0
		CollectionsGUI::add_collection("child", 0);              // id 1
		CollectionsGUI::add_collection("child_child", 1);        // id 2
		CollectionsGUI::add_collection("child_two", 0);          // id 3
		CollectionsGUI::add_collection("child_child_child", 2);  // id 4
		collections = CollectionsGUI::get_collection_hierarchy();

		col_itr = collections.find(0);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("parent", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
			if (col_itr->second.child_ids.size() == 2) {
				REQUIRE(col_itr->second.child_ids[0] == 1);
				REQUIRE(col_itr->second.child_ids[1] == 3);
			} else {
				REQUIRE(std::strcmp("Collection has incorrect num of children",
				                    warning_rm.c_str()) != 0);
			}
		}

		col_itr = collections.find(1);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("child", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == 0);
			if (col_itr->second.child_ids.size() != 1) {
				REQUIRE(std::strcmp("Collection has incorrect num of children",
				                    warning_rm.c_str()) != 0);
			} else {
				REQUIRE(col_itr->second.child_ids[0] == 2);
			}
		}

		col_itr = collections.find(2);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("child_child", col_itr->second.name.c_str()) ==
			        0);
			REQUIRE(col_itr->second.parent_collection_id == 1);
			if (col_itr->second.child_ids.size() != 1) {
				REQUIRE(std::strcmp("Collection has incorrect num of children",
				                    warning_rm.c_str()) != 0);
			} else {
				REQUIRE(col_itr->second.child_ids[0] == 4);
			}
		}

		col_itr = collections.find(4);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("child_child_child",
			                    col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == 2);
			REQUIRE(col_itr->second.child_ids.empty());
		}

		CollectionsGUI::clear_collections();
	}

	SECTION("Entities belonging to collections") {
		CollectionsGUI::add_collection("test", -1);    // id 0
		CollectionsGUI::add_collection("testTwo", 0);  // id 1
		auto entity1 = ecs.create_entity("ent1");
		auto entity2 = ecs.create_entity("ent2");
		auto entity3 = ecs.create_entity("ent3");
		auto entity4 = ecs.create_entity("ent4");

		CollectionsGUI::add_entity_to_collection(entity1.get_entity_id(), 0);
		CollectionsGUI::add_entity_to_collection(entity2.get_entity_id(), 1);
		CollectionsGUI::add_entity_to_collection(entity3.get_entity_id(), 2);
		CollectionsGUI::add_entity_to_collection(entity4.get_entity_id(), -1);

		REQUIRE(CollectionsGUI::get_entity_collection_id(
		            entity1.get_entity_id()) == 0);
		REQUIRE(CollectionsGUI::get_entity_collection_id(
		            entity2.get_entity_id()) == 1);
		REQUIRE(CollectionsGUI::get_entity_collection_id(
		            entity3.get_entity_id()) == -1);
		REQUIRE(CollectionsGUI::get_entity_collection_id(
		            entity4.get_entity_id()) == -1);

		CollectionsGUI::clear_collections();
	}

	SECTION("Remove collection") {
		CollectionsGUI::add_collection("parent", -1);      // id 0
		CollectionsGUI::add_collection("child", 0);        // id 1
		CollectionsGUI::add_collection("child_child", 1);  // id 2
		CollectionsGUI::add_collection("child_two", 0);    // id 3

		CollectionsGUI::remove_collection(1);
		collections = CollectionsGUI::get_collection_hierarchy();
		REQUIRE(collections.size() == 3);

		col_itr = collections.find(0);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("parent", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
			if (col_itr->second.child_ids.size() == 2) {
				REQUIRE(col_itr->second.child_ids[0] == 3);
				REQUIRE(col_itr->second.child_ids[1] == 2);
			} else {
				REQUIRE(std::strcmp("Collection has incorrect num of children",
				                    warning_rm.c_str()) != 0);
			}
		}

		col_itr = collections.find(2);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("child_child", col_itr->second.name.c_str()) ==
			        0);
			REQUIRE(col_itr->second.parent_collection_id == 0);
			REQUIRE(col_itr->second.child_ids.empty());
		}

		CollectionsGUI::clear_collections();
	}

	SECTION("Move collection to another collection") {
		CollectionsGUI::add_collection("parent", -1);      // id 0
		CollectionsGUI::add_collection("child", 0);        // id 1
		CollectionsGUI::add_collection("child_child", 1);  // id 2
		CollectionsGUI::add_collection("parent_two", -1);  // id 3
		CollectionsGUI::set_collection_collection(
		    1, 3);  // move collection 1 from 0 to 3
		collections = CollectionsGUI::get_collection_hierarchy();
		REQUIRE(collections.size() == 4);

		col_itr = collections.find(0);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("parent", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
			if (col_itr->second.child_ids.size() == 1) {
				REQUIRE(col_itr->second.child_ids[0] == 2);
			} else {
				REQUIRE(std::strcmp("Collection has incorrect num of children",
				                    warning_rm.c_str()) != 0);
			}
		}

		col_itr = collections.find(3);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("parent_two", col_itr->second.name.c_str()) ==
			        0);
			REQUIRE(col_itr->second.parent_collection_id == -1);
			if (col_itr->second.child_ids.size() == 1) {
				REQUIRE(col_itr->second.child_ids[0] == 1);
			} else {
				REQUIRE(std::strcmp("Collection has incorrect num of children",
				                    warning_rm.c_str()) != 0);
			}
		}

		col_itr = collections.find(1);
		if (col_itr == collections.end()) {
			REQUIRE(std::strcmp("Collection not found", warning_rm.c_str()) !=
			        0);
		} else {
			REQUIRE(std::strcmp("child", col_itr->second.name.c_str()) == 0);
			REQUIRE(col_itr->second.parent_collection_id == 3);
			REQUIRE(col_itr->second.child_ids.empty());
		}

		CollectionsGUI::clear_collections();
	}
}