#include <vector>
#include <string>
#include <unordered_map>

#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"
#include "Controller/AI/Counter.hpp"

struct Collection_Hierarchy {
	std::string name = "";
	int collection_id = -1;
	int parent_collection_id = 0;
	std::vector<int> child_ids = std::vector<int>();
};

class CollectionsGUI {
public:
	static const std::vector<Collection_Hierarchy>& get_collection_hierarchy();
	static int get_entity_collection_id(entt::entity& entity);
	static void draw_add_collection();
	static void add_collection(std::string name, int parent_id);
	static void remove_collection(int collection_id);

private:
	static std::unordered_map<entt::entity, int> collection_relationships;
	static std::vector<Collection_Hierarchy> collection_hierarchy;
	static Counter collection_id_generator;
};