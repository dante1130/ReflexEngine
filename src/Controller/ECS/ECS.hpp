#pragma once

#include <unordered_map>
#include <memory>

#include <entt/entt.hpp>

class Entity;

class ECS {
public:
	ECS() = default;

	Entity& create_entity();

	void update(float delta_time);

	void fixed_update(float delta_time);

	void draw();

	void destroy_entity(entt::entity entity_id);

	Entity& get_entity(entt::entity entity_id) const;

private:
	entt::registry registry_ = {};
	std::unordered_map<entt::entity, std::unique_ptr<Entity>> entities_ = {};
	friend Entity;
};