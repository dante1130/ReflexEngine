#include "CollectionsGUI.hpp"
#include <stdexcept>

const std::vector<Collection_Hierarchy>&
CollectionsGUI::get_collection_hierarchy() {
	if (collection_hierarchy.size() == 0) {
		add_collection();
	}
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

void CollectionsGUI::add_collection(std::string name, int parent_id) {
	Collection_Hierarchy col_hir;
	col_hir.name = name;

	if (collection_hierarchy.size() == 0) {
		col_hir.parent_collection_id = -1;
		col_hir.collection_id = collection_id_generator.increment_count();
		collection_hierarchy.insert(col_hir);

		return;
	}

	bool valid_parent_id = false;
	int size = collection_hierarchy.size();
	for (int count = 0; count < size; count++) {
		if (collection_hierarchy[count].collection_id == parent_id) {
			valid_parent_id = true;
		}
	}

	if (valid_parent_id) {
		col_hir.parent_collection_id = parent_id;
	} else {
		col_hir.parent_collection_id = -1;
	}

	col_hir.collection_id = collection_id_generator.increment_count();
	collection_hierarchy.insert(col_hir);
}

void CollectionsGUI::remove_collection(int collection_id) { if (collection_id) }