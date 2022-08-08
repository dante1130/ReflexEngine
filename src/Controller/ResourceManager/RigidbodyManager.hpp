#pragma once

#include <unordered_map>
#include "Model/Components/RigidBody.hpp"
#include "Model/Components/Transform.hpp"
#include "Controller/Physics/Rigidbody.hpp"
#include "Controller/Physics/Physics.hpp"
#include <entt/entt.hpp>

class RigidbodyManager
{
	public:
		RigidbodyManager() = default;

		//~RigidbodyManager();

		void lua_access();

		void add_rigidbody(entt::entity id, const Component::Rigidbody& rb, const Component::Transform& tf);

		void update_rigidbody(entt::entity id, const Component::Rigidbody& rb, Component::Transform& tf);

		void delete_rigidbody(entt::entity id);

		Rigidbody& get_rigidbody(entt::entity id);

	private:

		std::unordered_map<entt::entity, Rigidbody> rigidbodies_;

};