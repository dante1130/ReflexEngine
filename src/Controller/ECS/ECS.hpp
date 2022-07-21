#pragma once

#include <unordered_map>
#include <memory>

#include <entt/entt.hpp>

class Entity;

/**
 * @class ECS
 * @brief The ECS class is a facade of the EnTT registry. It is used to
 * create, destroy, update and retrieve entities.
 */
class ECS {
public:
	ECS() = default;

	/**
	 * @brief Create an entity.
	 *
	 * @return Entity&
	 */
	Entity& create_entity();

	/**
	 * @brief Updates the ECS components.
	 *
	 * @param delta_time The time between the last and the current frame.
	 */
	void update(double delta_time);

	/**
	 * @brief Updates the ECS components with a fixed timestep.
	 *
	 * @param delta_time The time between the last and the current timestep.
	 */
	void fixed_update(double delta_time);

	/**
	 * @brief Draws the drawable ECS components.
	 */
	void draw();

	/**
	 * @brief Destroy an entity.
	 *
	 * @param entity_id The entity ID.
	 */
	void destroy_entity(entt::entity entity_id);

	/**
	 * @brief Get the entity object
	 *
	 * @param entity_id The entity ID.
	 * @return Entity&
	 */
	Entity& get_entity(entt::entity entity_id);

	/**
	 * @brief Get the registry.
	 *
	 * @return entt::registry&
	 */
	entt::registry& get_registry();

	/**
	 * @brief Destroy all entities.
	 */
	void clear_entities();

private:
	/// The EnTT registry.
	entt::registry registry_;
	/// The hashmap of key value pairs of entity ID and entity object.
	std::unordered_map<entt::entity, std::unique_ptr<Entity>> entities_;

	// An entity is made a friend to allow it to access the ECS private members,
	// this is done because Entity has a pointer to the ECS instance.
	friend Entity;
};  // namespace ECS