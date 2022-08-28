#include "CollectionsGUI.hpp"

int CollectionsGUI::get_entity_from_collection(entt::entity &entity) {
	int collection_id = -1;
	auto search = entities_place.find(entity);
	if (search != entities_place.end()) {
		collection_id = search->second;
	} else {
		entities_place.insert(std::pair<entt::entity, int>(entity, -1));
	}
	return collection_id;
}
std::string CollectionsGUI::get_collection_name(int unique_id) {
	std::string name = "";
	auto search = collections.find(unique_id);
	if (search != collections.end()) {
		name = search->second;
	}
	return name;
}
void CollectionsGUI::draw_add_collection() {}
void CollectionsGUI::remove_collections() {}