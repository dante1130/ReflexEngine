#pragma once

#include "ECS.hpp"

/**
 * @class Entity
 * @brief An ECS entity object that is able to store and retrieve components.
 */
class Entity {
public:
	/**
	 * @brief Construct a new Entity object.
	 *
	 * @param entity_id The entity ID.
	 * @param ecs A pointer to the ECS instance.
	 */
	Entity(entt::entity entity_id, ECS* ecs);

	/**
	 * @brief Adds a component to the entity.
	 *
	 * @tparam T The component type.
	 * @tparam Args The component constructor arguments.
	 * @param args The component constructor arguments.
	 * @return T&
	 */
	template <typename T, typename... Args>
	T& add_component(Args&&... args);

	/**
	 * @brief Removes a component from the entity.
	 *
	 * @tparam T The component type.
	 */
	template <typename T>
	void remove_component();

	/**
	 * @brief Get a component from the entity.
	 *
	 * @tparam T The component type.
	 * @return T&
	 */
	template <typename T>
	T& get_component() const;

	/**
	 * @brief Get the entity id object
	 *
	 * @return entt::entity
	 */
	entt::entity get_entity_id() const;

	/**
	 * @brief Get the ECS registry.
	 *
	 * @return entt::registry&
	 */
	entt::registry& get_registry();

private:
	/// The entity ID.
	entt::entity entity_id_ = {entt::null};
	/// A pointer to the ECS instance.
	ECS* ecs_ = nullptr;
};

template <typename T, typename... Args>
T& Entity::add_component(Args&&... args) {
	return ecs_->registry_.emplace<T>(entity_id_, std::forward<Args>(args)...);
}

template <typename T>
void Entity::remove_component() {
	ecs_->registry_.remove<T>(entity_id_);
}

template <typename T>
T& Entity::get_component() const {
	return ecs_->registry_.get<T>(entity_id_);
}