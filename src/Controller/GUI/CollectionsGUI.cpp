#include "CollectionsGUI.hpp"
#include "Controller/GUI/DebugLogger.hpp"
#include <imgui/misc/cpp/imgui_stdlib.h>
#include "Controller/LuaManager.hpp"

std::unordered_map<entt::entity, int> CollectionsGUI::collection_relationships =
    std::unordered_map<entt::entity, int>();
std::vector<Collection> CollectionsGUI::collection_hierarchy =
    std::vector<Collection>();
Counter CollectionsGUI::collection_id_generator = Counter();

std::vector<Collection>& CollectionsGUI::get_collection_hierarchy() {
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
	int size = collection_hierarchy.size();
	for (int count = 0; count < size; ++count) {
		if (collection_hierarchy[count].collection_id == collection_id) {
			return collection_hierarchy[count];
		}
	}
	Collection col;
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

	bool valid_parent_id = false;
	int size = collection_hierarchy.size();
	for (int count = 0; count < size; count++) {
		if (collection_hierarchy[count].collection_id == parent_id) {
			valid_parent_id = true;
			collection_hierarchy[count].child_ids.push_back(
			    col_hir.collection_id);
		}
	}

	if (valid_parent_id) {
		col_hir.parent_collection_id = parent_id;
	} else {
		col_hir.parent_collection_id = -1;
	}

	collection_hierarchy.push_back(col_hir);

	return col_hir.collection_id;
}

void CollectionsGUI::remove_collection(int collection_id) {
	Collection temp_collection;
	int remove_index = -1;
	int size = collection_hierarchy.size();

	for (int count = 0; count < size; ++count) {
		if (collection_hierarchy[count].collection_id == collection_id) {
			remove_index = count;
			break;
		}
	}

	if (remove_index == -1) {
		DebugLogger::log("CollectionsGUI", "collection id not found");
		return;
	}
	temp_collection = collection_hierarchy[remove_index];

	int number_of_childs = 0;
	// Remove child index from parent collection and collections children to
	// parent collection
	for (int count = 0; count < size; ++count) {
		// If parent has been found
		if (collection_hierarchy[count].collection_id ==
		    temp_collection.parent_collection_id) {
			// For all the child collections in the parent
			number_of_childs = collection_hierarchy[count].child_ids.size();
			for (int innerCount = 0; innerCount < number_of_childs;
			     ++innerCount) {
				DebugLogger::log(
				    "Collections children",
				    std::to_string(
				        collection_hierarchy[count].child_ids[innerCount])
				        .c_str());
				if (temp_collection.collection_id ==
				    collection_hierarchy[count].child_ids[innerCount]) {
					collection_hierarchy[count].child_ids.erase(
					    collection_hierarchy[count].child_ids.begin() +
					    innerCount);
					DebugLogger::log(
					    "Collections RM child",
					    std::to_string(temp_collection.collection_id).c_str());
					break;
				}
			}

			// Add children to parent collection
			number_of_childs = temp_collection.child_ids.size();
			for (int innerCount = 0; innerCount < number_of_childs;
			     ++innerCount) {
				collection_hierarchy[count].child_ids.push_back(
				    temp_collection.child_ids[innerCount]);
			}

			break;
		}
	}

	// Set new parents on child indexes
	size = collection_hierarchy.size();
	number_of_childs = temp_collection.child_ids.size();
	for (int count = 0; count < size; ++count) {
		for (int innerCount = 0; innerCount < number_of_childs; ++innerCount) {
			if (collection_hierarchy[count].collection_id ==
			    temp_collection.child_ids[innerCount]) {
				collection_hierarchy[count].parent_collection_id =
				    temp_collection.parent_collection_id;
				innerCount = number_of_childs;
				DebugLogger::log(
				    "Set collection parent id",
				    std::to_string(temp_collection.parent_collection_id)
				        .c_str());
			}
		}
	}

	DebugLogger::log("Collection remove",
	                 collection_hierarchy[remove_index].name.c_str());
	collection_hierarchy.erase(collection_hierarchy.begin() + remove_index);
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

void CollectionsGUI::drag_drop_entities_to_collections_target(int index) {
	if (ImGui::BeginDragDropTarget()) {
		ImGuiDragDropFlags target_flags = 0;
		target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
		if (const ImGuiPayload* payload =
		        ImGui::AcceptDragDropPayload("COLLECTION_MOVE", target_flags)) {
			DebugLogger::log("Drag move", "Something was moved");
			CollectionsGUI::set_entity_collection(
			    *(entt::entity*)payload->Data,
			    collection_hierarchy[index].collection_id);
		}
		ImGui::EndDragDropTarget();
	}
}

void CollectionsGUI::drag_drop_collections_to_collections_target(int index) {
	if (ImGui::BeginDragDropTarget()) {
		ImGuiDragDropFlags target_flags = 0;
		target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(
		        "COLLECTION_COLLECTION_MOVE", target_flags)) {
			DebugLogger::log("Drag move", "Collection was moved");
			CollectionsGUI::set_collection_collection(*(int*)payload->Data,
			                                          index);
		}
		ImGui::EndDragDropTarget();
	}
}

void CollectionsGUI::set_collection_collection(int selected_collection,
                                               int target_collection) {
	if (selected_collection == target_collection) {
		return;
	}

	int number_of_children =
	    collection_hierarchy[selected_collection].child_ids.size();
	int number_of_collections = collection_hierarchy.size();
	for (int count = 0; count < number_of_children; ++count) {
		for (int innerCount = 0; innerCount < number_of_collections;
		     ++innerCount) {
			// Set all children collections to parent collection of collection
			if (collection_hierarchy[innerCount].collection_id ==
			    collection_hierarchy[selected_collection].child_ids[count]) {
				collection_hierarchy[innerCount].parent_collection_id =
				    collection_hierarchy[selected_collection]
				        .parent_collection_id;
			}
		}
	}

	// Loop through collections to get parent collection to remove child id from
	// parent
	for (int count = 0; count < number_of_collections; count++) {
		// if found parent collection
		if (collection_hierarchy[selected_collection].parent_collection_id ==
		    collection_hierarchy[count].collection_id) {
			int size = collection_hierarchy[count].child_ids.size();
			// For all children in parent
			for (int innerCount = 0; innerCount < size; ++innerCount) {
				// If your collection is found remove it from parent
				if (collection_hierarchy[count].child_ids[innerCount] ==
				    collection_hierarchy[selected_collection].collection_id) {
					collection_hierarchy[count].child_ids.erase(
					    collection_hierarchy[count].child_ids.begin() +
					    innerCount);
					break;
				}
			}
			break;
		}
	}

	// Set the new parent collection id
	collection_hierarchy[selected_collection].parent_collection_id =
	    collection_hierarchy[target_collection].collection_id;
	// set parent's new child
	collection_hierarchy[target_collection].child_ids.push_back(
	    collection_hierarchy[selected_collection].collection_id);
	// Remove children from collection
	collection_hierarchy[selected_collection].child_ids.clear();
}

bool CollectionsGUI::drag_drop_collections_to_collections_source(
    const std::string& name, int index) {
	ImGuiDragDropFlags src_flags = 0;
	src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;
	src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
	// src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip;

	if (ImGui::BeginDragDropSource(src_flags)) {
		ImGui::Text(name.c_str());
		ImGui::SetDragDropPayload("COLLECTION_COLLECTION_MOVE", &index,
		                          sizeof(int));
		ImGui::EndDragDropSource();
		return true;
	}
	return false;
}

void CollectionsGUI::rename_collection(const std::string& new_name,
                                       int collection_id) {
	if (new_name.empty()) {
		return;
	}

	int number_of_collections = collection_hierarchy.size();
	for (int count = 0; count < number_of_collections; ++count) {
		if (collection_hierarchy[count].collection_id == collection_id) {
			collection_hierarchy[count].name = new_name;
		}
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