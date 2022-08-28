#include <vector>
#include <string>
#include <unordered_map>

#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"

class CollectionsGUI {
public:
	static int get_entity_from_collection(entt::entity &entity);
	static std::string get_collection_name(int unique_id);
	static void draw_add_collection();
	static void remove_collections();

private:
	static std::unordered_map<int, std::string> collections;
	static std::unordered_map<entt::entity, int> entities_place;
};