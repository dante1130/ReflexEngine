#pragma once

#include "ECS.hpp"

namespace Reflex {
/**
 * @class Entity
 * @brief An ECS entity object that is able to store and retrieve components.
 */
class Entity {
public:
	Entity() = default;

	/**
	 * @brief Construct a new Entity object.
	 *
	 * @param name The name of the entity.
	 * @param entity_id The entity ID.
	 * @param ecs A pointer to the ECS instance.
	 */
	Entity(const std::string& name, entt::entity entity_id, ECS* ecs);

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
	 * @brief Returns true if the entity any of the components.
	 *
	 * @tparam T The component types.
	 * @return bool
	 */
	template <typename... T>
	bool any_component() const;

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

	/**
	 * @brief Get the name.
	 *
	 * @return std::string&
	 */
	std::string& get_name();

private:
	/// The name of the entity.
	std::string name_;
	/// The entity ID.
	entt::entity entity_id_ = {entt::null};
	/// A pointer to the ECS instance.
	ECS* ecs_ = nullptr;
};
};  // namespace Reflex

template <typename T, typename... Args>
T& Reflex::Entity::add_component(Args&&... args) {
	return ecs_->registry_.emplace<T>(entity_id_, std::forward<Args>(args)...);
}

template <typename T>
void Reflex::Entity::remove_component() {
	ecs_->registry_.remove<T>(entity_id_);
}

template <typename T>
T& Reflex::Entity::get_component() const {
	return ecs_->registry_.get<T>(entity_id_);
}

template <typename... T>
bool Reflex::Entity::any_component() const {
	return ecs_->registry_.any_of<T...>(entity_id_);
}
