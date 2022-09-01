#include <vector>
#include <string>
#include <unordered_map>

#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"
#include "Controller/AI/Counter.hpp"

/**
 * @author Daniel Rodic
 * @brief Stores basic data required for a collection
 */
struct Collection {
	std::string name = "";
	int collection_id = -1;
	int parent_collection_id = -1;
	std::vector<int> child_ids = std::vector<int>();
};

/**
 * @author Daniel Rodic
 * @brief Hanldes the collections GUI
 */
class CollectionsGUI {
public:
	/**
	 * @brief Provides access to lua
	 *
	 */
	static void lua_access();

	/**
	 * @brief Get the collection hierarchy object
	 *
	 * @return std::vector<Collection>&
	 */
	static std::unordered_map<int, Collection>& get_collection_hierarchy();

	/**
	 * @brief Get the collection object
	 *
	 * @param collection_id the id of the collection you want to get
	 * @return Collection
	 */
	static Collection get_collection(int collection_id);

	/**
	 * @brief Get the which collection the entity belongs to
	 *
	 * @param entity the entity you are interested in
	 * @return int the collection id
	 */
	static int get_entity_collection_id(const entt::entity& entity);

	/**
	 * @brief Adds a new collection to the scene
	 *
	 * @param name the name of the new collection
	 * @param parent_id the parent id of the new collection (-1 for no parent)
	 * @return int the collection id of the new collection
	 */
	static int add_collection(const std::string& name, int parent_id);

	/**
	 * @brief Removes a collection
	 *
	 * @param collection_id of the collection you want to remove
	 */
	static void remove_collection(int collection_id);

	/**
	 * @brief Set the entity collection object
	 *
	 * @param entity
	 * @param new_collection
	 */
	static void set_entity_collection(const entt::entity& entity,
	                                  int new_collection);

	/**
	 * @brief Renames a collection
	 *
	 * @param new_name the new name
	 * @param collection_id the collection to rename
	 */
	static void rename_collection(const std::string& new_name,
	                              int collection_id);

	/**
	 * @brief Adds an entity to a collection
	 *
	 * @param entity the entity to add
	 * @param collection_id the collection to add the entity too
	 */
	static void add_entity_to_collection(const entt::entity& entity,
	                                     int collection_id);

	/**
	 * @brief Set the collection collection object
	 *
	 * @param selected_collection the collection you have moved
	 * @param target_collection the new parent of the collection you have moved
	 */
	static void set_collection_collection(int selected_collection,
	                                      int target_collection);

	/**
	 * @brief Clears the collections
	 *
	 */
	static void clear_collections();

private:
	/// Stores the relationships between collections and entities
	static std::unordered_map<entt::entity, int> collection_relationships;
	/// Stores all the collections
	static std::unordered_map<int, Collection> collection_hierarchy;
	/// Generates the collection ids
	static Counter collection_id_generator;
};
