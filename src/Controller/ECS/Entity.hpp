#pragma once

#include "ECS.hpp"

class Entity {
public:
	Entity(entt::entity entity_id, ECS* ecs);

	Entity(const Entity& other) = default;
	Entity(Entity&& other) = default;
	Entity& operator=(const Entity& other) = default;
	Entity& operator=(Entity&& other) = default;

	template <typename T, typename... Args>
	T& add_component(Args&&... args);

	template <typename T>
	void remove_component();

	template <typename T>
	T& get_component() const;

	template <typename T>
	bool has_component() const;

	entt::entity get_entity_id() const;

private:
	entt::entity entity_id_ = {entt::null};
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

template <typename T>
bool Entity::has_component() const {
	return ecs_->registry_.has<T>(entity_id_);
}