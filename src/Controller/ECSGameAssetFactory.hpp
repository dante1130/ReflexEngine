#pragma once

#include <string>

#include <sol/sol.hpp>

#include "ECS/ECS.hpp"
#include "ECS/Entity.hpp"

/**
 * @author Andrew Ho
 * @class ECSGameAssetFactory
 * @brief A factory to register entities and its components from a lua file.
 */
class ECSGameAssetFactory {
public:
	/**
	 * @brief Creates a new entity from a lua file.
	 *
	 * @param ecs The ECS object.
	 * @param lua_script The lua script.
	 */
	static void create(ECS& ecs, const std::string& lua_script);

private:
	/**
	 * @brief Loads all the components into the entity.
	 *
	 * @param entity The entity to load the components into.
	 * @param entity_table The table of the entity.
	 */
	static void load_components(ECS& ecs, Reflex::Entity& entity,
	                            const sol::table& entity_table);

	/**
	 * @brief Loads a transform component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param transform_table The table of the transform component.
	 */
	static void load_transform(Reflex::Entity& entity,
	                           const sol::table& transform_table);

	/**
	 * @brief Loads a script component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param script_table The table of the script component.
	 */
	static void load_script(ECS& ecs, Reflex::Entity& entity,
	                        const sol::table& script_table);

	/**
	 * @brief Loads a mesh component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param mesh_table The table of the mesh component.
	 */
	static void load_mesh(Reflex::Entity& entity, const sol::table& mesh_table);

	/**
	 * @brief Loads a model component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param model_table The table of the model component.
	 */
	static void load_model(Reflex::Entity& entity,
	                       const sol::table& model_table);

	/**
	 * @brief Loads a md2 animation component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param md2_table The table of the md2 animation component.
	 */
	static void load_md2_animation(Reflex::Entity& entity,
	                               const sol::table& md2_table);

	/**
	 * @brief Loads a terrain component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param terrain_table The table of the terrain component.
	 */
	static void load_terrain(Reflex::Entity& entity,
	                         const sol::table& terrain_table);

	/**
	 * @brief Loads a directional light component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param light_table The table of the light component.
	 */
	static void load_directional_light(Reflex::Entity& entity,
	                                   const sol::table& light_table);

	/**
	 * @brief Loads a point light component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param light_table The table of the light component.
	 */
	static void load_point_light(Reflex::Entity& entity,
	                             const sol::table& light_table);

	/**
	 * @brief Loads a spot light component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param light_table The table of the light component.
	 */
	static void load_spot_light(Reflex::Entity& entity,
	                            const sol::table& light_table);
	/**
	 * @brief Loads a statemachine component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param statemachine_table The table fo the statemachine component
	 */
	static void load_statemachine(Reflex::Entity& entity,
	                              const sol::table& statemachine_table);

	/**
	 * @brief Loads an affordance agent component into the entity.
	 *
	 * @param entity The entity to load the component into.
	 * @param affordance_table The table of the affordance agent component.
	 */
	static auto load_affordance_agent(Reflex::Entity& entity,
	                                  const sol::table& affordance_agent_table)
	    -> void;

	/**
	 * @brief Checks the string if it is a valid lua file.
	 *
	 * @param lua_script The string to check.
	 * @return boolean
	 */
	static bool is_lua_script(const std::string& lua_script);

	/**
	 * @brief Loads a rigidbody component into the entity
	 *
	 * @param entity - The entity to load the component into
	 * @param rigidbody_table - The table fo the statemachine component
	 * @return void
	 */
	static void load_rigidbody(Reflex::Entity& entity,
	                           const sol::table& rigidbody_table);
};
