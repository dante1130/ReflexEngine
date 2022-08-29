#include "CollectionsGUI.hpp"
#include "Controller/GUI/DebugLogger.hpp"
#include <imgui/misc/cpp/imgui_stdlib.h>

std::unordered_map<entt::entity, int> CollectionsGUI::collection_relationships =
    std::unordered_map<entt::entity, int>();
std::vector<Collection> CollectionsGUI::collection_hierarchy =
    std::vector<Collection>();
Counter CollectionsGUI::collection_id_generator = Counter();

std::vector<Collection>& CollectionsGUI::get_collection_hierarchy() {
	return collection_hierarchy;
}

int CollectionsGUI::get_entity_collection_id(entt::entity& entity) {
	int collection_id = -1;
	auto search = collection_relationships.find(entity);
	if (search != collection_relationships.end()) {
		collection_id = search->second;
	}

	return collection_id;
}

void CollectionsGUI::draw_add_collection() {}

void CollectionsGUI::add_collection(const std::string& name, int parent_id) {
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
	int temp_collection_size = temp_collection.child_ids.size();
	for (int count = 0; count < size; ++count) {
		for (int innerCount = 0; innerCount < temp_collection_size;
		     ++innerCount) {
			if (collection_hierarchy[count].collection_id ==
			    temp_collection.child_ids[innerCount]) {
				collection_hierarchy[count].parent_collection_id =
				    temp_collection.parent_collection_id;
				innerCount = temp_collection_size;
			}
		}
	}

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

void CollectionsGUI::drag_drop_collections_target(int index) {
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