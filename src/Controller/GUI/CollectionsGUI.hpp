#include <vector>
#include <string>
#include <unordered_map>

#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"
#include "Controller/AI/Counter.hpp"

struct Collection {
	std::string name = "";
	int collection_id = -1;
	int parent_collection_id = -1;
	std::vector<int> child_ids = std::vector<int>();
};

class CollectionsGUI {
public:
	static std::vector<Collection>& get_collection_hierarchy();
	static int get_entity_collection_id(entt::entity& entity);
	static void draw_add_collection();
	static void add_collection(const std::string& name, int parent_id);
	static void remove_collection(int collection_id);
	static void set_entity_collection(const entt::entity& entity,
	                                  int new_collection);
	static void drag_drop_collections_target(int index);

private:
	static std::unordered_map<entt::entity, int> collection_relationships;
	static std::vector<Collection> collection_hierarchy;
	static Counter collection_id_generator;
};
