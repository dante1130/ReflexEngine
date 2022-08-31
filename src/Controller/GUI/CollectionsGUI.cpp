#include "CollectionsGUI.hpp"
#include "Controller/GUI/DebugLogger.hpp"
#include <imgui/misc/cpp/imgui_stdlib.h>
#include "Controller/LuaManager.hpp"

std::unordered_map<entt::entity, int> CollectionsGUI::collection_relationships =
    std::unordered_map<entt::entity, int>();
std::unordered_map<int, Collection> CollectionsGUI::collection_hierarchy =
    std::unordered_map<int, Collection>();
Counter CollectionsGUI::collection_id_generator = Counter();

std::unordered_map<int, Collection>&
CollectionsGUI::get_collection_hierarchy() {
	return collection_hierarchy;
}

void CollectionsGUI::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto collection = lua.create_named_table("Collections");

	collection.set_function("add_collection", &CollectionsGUI::add_collection);
	collection.set_function("clear_collections",
	                        &CollectionsGUI::clear_collections);

	// Add collection
}

Collection CollectionsGUI::get_collection(int collection_id) {
	Collection col;
	auto search = collection_hierarchy.find(collection_id);
	if (search != collection_hierarchy.end()) {
		col = search->second;
	}

	return col;
}

int CollectionsGUI::get_entity_collection_id(entt::entity& entity) {
	int collection_id = -1;
	auto search = collection_relationships.find(entity);
	if (search != collection_relationships.end()) {
		collection_id = search->second;
	}

	return collection_id;
}

int CollectionsGUI::add_collection(const std::string& name, int parent_id) {
	Collection col_hir;
	col_hir.name = name;
	col_hir.collection_id = collection_id_generator.increment_count();

	auto search = collection_hierarchy.find(parent_id);
	if (search != collection_hierarchy.end()) {
		col_hir.parent_collection_id = parent_id;
		search->second.child_ids.push_back(col_hir.collection_id);
	} else {
		col_hir.parent_collection_id = -1;
	}

	collection_hierarchy.insert(
	    std::pair<int, Collection>(col_hir.collection_id, col_hir));

	return col_hir.collection_id;
}

void CollectionsGUI::remove_collection(int collection_id) {
	Collection temp_collection;

	auto search = collection_hierarchy.find(collection_id);
	if (search == collection_hierarchy.end()) {
		DebugLogger::log("CollectionsGUI", "collection id not found");
		return;
	}
	temp_collection = search->second;

	int number_of_childs = 0;
	// Remove child index from parent collection and collections children to
	// parent collection

	auto search_parent =
	    collection_hierarchy.find(temp_collection.parent_collection_id);
	if (search_parent != collection_hierarchy.end()) {
		number_of_childs = search_parent->second.child_ids.size();
		for (int count = 0; count < number_of_childs; ++count) {
			// Remove collection from parents list of children
			if (temp_collection.collection_id ==
			    search_parent->second.child_ids[count]) {
				search_parent->second.child_ids.erase(
				    search_parent->second.child_ids.begin() + count);
				count = number_of_childs;
			}
		}

		// Add children of collection to become children of parent collection
		number_of_childs = temp_collection.child_ids.size();
		for (int count = 0; count < number_of_childs; ++count) {
			search_parent->second.child_ids.push_back(
			    temp_collection.child_ids[count]);
		}
	}

	// Set new parents on child indexes
	// auto search_child;
	std::unordered_map<int, Collection>::iterator search_child;
	number_of_childs = temp_collection.child_ids.size();
	for (int count = 0; count < number_of_childs; ++count) {
		search_child =
		    collection_hierarchy.find(temp_collection.child_ids[count]);
		if (search_child != collection_hierarchy.end()) {
			search_child->second.parent_collection_id =
			    temp_collection.parent_collection_id;
		}
	}

	DebugLogger::log("Collection remove", temp_collection.name);
	collection_hierarchy.erase(temp_collection.collection_id);
}

void CollectionsGUI::set_entity_collection(const entt::entity& entity,
                                           int new_collection) {
	auto search = collection_relationships.find(entity);
	if (search != collection_relationships.end()) {
		search->second = new_collection;
	} else {
		collection_relationships.insert(
		    std::pair<entt::entity, int>(entity, new_collection));
	}
}

void CollectionsGUI::set_collection_collection(int selected_collection,
                                               int target_collection) {
	if (selected_collection == target_collection) {
		return;
	}

	auto search = collection_hierarchy.find(selected_collection);
	if (search == collection_hierarchy.end()) {
		return;
	}
	Collection temp_collection = search->second;
	int number_of_children = temp_collection.child_ids.size();
	std::unordered_map<int, Collection>::iterator search_child;
	// Set children's parent id to collections parent id
	for (int count = 0; count < number_of_children; ++count) {
		search_child =
		    collection_hierarchy.find(temp_collection.child_ids[count]);
		if (search_child != collection_hierarchy.end()) {
			search_child->second.parent_collection_id =
			    temp_collection.parent_collection_id;
		}
	}

	auto search_parent =
	    collection_hierarchy.find(temp_collection.parent_collection_id);
	if (search_parent != collection_hierarchy.end()) {
		Collection parent_collection = search_parent->second;
		number_of_children = parent_collection.child_ids.size();
		// Remove collection from parent collection children
		for (int count = 0; count < number_of_children; ++count) {
			if (parent_collection.child_ids[count] ==
			    temp_collection.collection_id) {
				search_parent->second.child_ids.erase(
				    search_parent->second.child_ids.begin() + count);
				DebugLogger::log("Removed collections parent child",
				                 std::to_string(temp_collection.collection_id));
				break;
			}
		}
		// Add collection's children to parent collection
		number_of_children = temp_collection.child_ids.size();
		for (int count = 0; count < number_of_children; ++count) {
			search_parent->second.child_ids.push_back(
			    temp_collection.child_ids[count]);
		}
	}

	auto search_target = collection_hierarchy.find(target_collection);
	if (search_target != collection_hierarchy.end()) {
		search->second.parent_collection_id =
		    search_target->second.collection_id;
		search_target->second.child_ids.push_back(
		    temp_collection.collection_id);
	} else {
		search->second.parent_collection_id = -1;
	}
	// Remove children from collection
	search->second.child_ids.clear();
}

void CollectionsGUI::rename_collection(const std::string& new_name,
                                       int collection_id) {
	if (new_name.empty()) {
		return;
	}

	auto search = collection_hierarchy.find(collection_id);
	if (search != collection_hierarchy.end()) {
		search->second.name = new_name;
	}
}

void CollectionsGUI::add_entity_to_collection(const entt::entity& entity,
                                              int collection_id) {
	Collection temp = CollectionsGUI::get_collection(collection_id);
	if (temp.collection_id == -1) {
		collection_relationships.insert(
		    std::pair<entt::entity, int>(entity, -1));
	} else {
		collection_relationships.insert(
		    std::pair<entt::entity, int>(entity, collection_id));
	}
}

void CollectionsGUI::clear_collections() {
	collection_hierarchy.clear();
	collection_relationships.clear();
	collection_id_generator.reset_count();
}