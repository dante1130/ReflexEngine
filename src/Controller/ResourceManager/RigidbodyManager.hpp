#pragma once

#include "Model/Components/RigidBody.hpp"
#include "Model/Components/Transform.hpp"

class RigidbodyManager
{
	public:
		RigidbodyManager() = default;

		//~RigidbodyManager();

		void add_rigidbody(Component::Rigidbody& rb, const Component::Transform& tf);

		void update_rigidbody(Component::Rigidbody& rb, Component::Transform& tf);

	private:

		glm::vec3 prev_position;
};