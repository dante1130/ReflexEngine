#pragma once

#include <sol/sol.hpp>

#include "Controller/LuaManager.hpp"
#include "Model/GameObject/GameObject.hpp"
#include "Model/GameObject/Item.hpp"
#include "Model/GameObject/Water.hpp"
#include "Model/GameObject/Body.hpp"
#include "Model/GameObject/BodyRigid.hpp"
#include "Model/GameObject/Player.hpp"
#include "Model/GameObject/PhysicsObject.hpp"
#include "Model/GameObject/ScriptableObject.hpp"
#include "Model/GameObject/TerrainObject.hpp"
#include "TexturedTerrain.hpp"

/**
 * @class GameAssetFactory
 * @brief A parameterized factory singleton for creating GameObjects.
 */
class GameAssetFactory {
public:
	/**
	 * @brief	Parameterised factory method pattern for created game objects
	 * @param	fileName	- The name of the lua file for object creation
	 * @return	*GameObject - A child game object
	 *
	 * @pre		type/file exists
	 * @post	Game object created
	 */
	static GameObject* create(std::string fileName);

private:
	/**
	 * @brief	Checks if it is a lua script
	 * @param	luaScript	- The lua script to check
	 * @return	bool		- True if lua script
	 *
	 * @pre	type/file exists
	 * @post	Game object created
	 */
	static bool isLuaScript(std::string luaScript);

	/**
	 * @brief	Gets the type of game object
	 * @param	luaScript	- The lua script to check
	 * @return	std::string	- Name of object type
	 *
	 * @pre	type/file exists
	 * @post	Game object created
	 */
	static std::string getObjectType(std::string luaScript);

	/**
	 * @brief	Loads in the base objects position from a lua state
	 * @param	lua			- The lua state
	 * @return	glm::vec3	- A vector 3 of the position of the base object
	 *
	 * @pre		Position varaible exists
	 * @post	Position stored
	 */
	static glm::vec3 loadBasePos(sol::state& lua);

	/**
	 * @brief	Loads in the base objects rotaiton axis from a lua state
	 * @param	lua			- The lua state
	 * @return	glm::vec3	- A vector 3 of the rotation axis of the base object
	 *
	 * @pre		Rotation axis varaible exists
	 * @post	Rotation axis stored
	 */
	static glm::vec3 loadBaseRotation(sol::state& lua);

	/**
	 * @brief	Loads in the base objects angle of rotation from a lua state
	 * @param	lua			- The lua state
	 * @return	float		- The angle of rotation
	 *
	 * @pre		angle of rotation varaible exists
	 * @post	angle of rotation stored
	 */
	static float loadBaseAngle(sol::state& lua);

	/**
	 * @brief	Loads in the base objects scale from a lua state
	 * @param	lua			- The lua state
	 * @return	glm::vec3	- A vector 3 of the scale of the base object
	 *
	 * @pre		scale varaible exists
	 * @post	scale stored
	 */
	static glm::vec3 loadBaseScale(sol::state& lua);

	/**
	 * @brief	Loads in an item object from a lua script
	 * @param	luaScript	- The lua script to load the item data from
	 * @return	*Item		- Created item object
	 *
	 * @pre		item varaible exists
	 * @post	Item stored
	 */
	static Item* loadItem(std::string luaScript);

	/**
	 * @brief	Loads in a water object from a lua script
	 * @param	luaScript	- The lua script to load the water data from
	 * @return	*Water		- Created water object
	 *
	 * @pre		water varaible exists
	 * @post	water stored
	 */
	static Water* loadWater(std::string luaScript);

	/**
	 * @brief	Loads in a body object from a lua script
	 * @param	luaScript	- The lua script to load the body data from
	 * @return	*body		- Created body object
	 *
	 * @pre		body varaible exists
	 * @post	body stored
	 */
	static Body* loadBody(std::string luaScript);

	/**
	 * @brief Loads in a player object from a lua script.
	 *
	 * @param lua_script
	 * @return Player*
	 */
	static Player* load_player(std::string lua_script);

	/**
	 * @brief	Loads in a physics object object from a lua script
	 * @param	luaScript	- The lua script to load the physics object data
	 * from
	 * @return	*PhysicsObject		- Created physics object object
	 *
	 * @pre		physics object varaible exists
	 * @post	physics object stored
	 */
	static PhysicsObject* loadPhysicsObject(std::string luaScript);

	/**
	 * @brief	Loads in extra physics object data from a lua script
	 * @param	po	- physic object to store the data to
	 * @param	lua	- Lua state
	 *
	 * @pre		extra physics data exists
	 * @post	extra physics data stored
	 */
	static void loadExtraPhysicObjectSettings(PhysicsObject* po,
	                                          sol::state& lua);

	/**
	 * @brief	Loads in a box collider from a lua script
	 * @param	count	- Which collider to get
	 * @param	po		- physic object to add the collider to
	 * @param	lua		- Lua state
	 *
	 * @pre		box collider exists
	 * @post	box collider added
	 */
	static void loadBoxCollider(int count, PhysicsObject* po, sol::state& lua);

	/**
	 * @brief	Loads in a sphere collider from a lua script
	 * @param	count	- Which collider to get
	 * @param	po		- physic object to add the collider to
	 * @param	lua		- Lua state
	 *
	 * @pre		sphere collider exists
	 * @post	sphere collider added
	 */
	static void loadSphereCollider(int count, PhysicsObject* po,
	                               sol::state& lua);

	/**
	 * @brief	Loads in a capsule collider from a lua script
	 * @param	count	- Which collider to get
	 * @param	po		- physic object to add the collider to
	 * @param	lua		- Lua state
	 *
	 * @pre		capsule collider exists
	 * @post	capsule collider added
	 */
	static void loadCapsuleCollider(int count, PhysicsObject* po,
	                                sol::state& lua);

	/**
	 * @brief	Loads in a scriptable object object from a lua script
	 * @param	luaScript	- The lua script to load the scriptale object data
	 * from
	 * @return	*ScriptableObject		- Created scriptable object object
	 *
	 * @pre		scriptable object object varaible exists
	 * @post	scriptable object object stored
	 */
	static ScriptableObject* loadScriptableObject(std::string luaScript);

	static TerrainObject* loadTerrainObject(std::string luaScript);
};