#pragma once

#include "Model/Components/RigidBody.hpp"
#include "Model/Components/Transform.hpp"

/**
 * @author Spencer Shaw 
 * @class RigidbodyManager
 * @brief A encapsulated class for the system to access rigidbodies.
 */
class RigidbodyManager
{
	public:
		RigidbodyManager() = default;

		//~RigidbodyManager();

		/**
	     * @brief Creates and initialises rigidbody component.
	     *
	     * @param rb - The rigidbody component of the object.
	     * @param tf - The transform component of the object.
	     * @return void
	     */
		void add_rigidbody(Component::Rigidbody& rb, const Component::Transform& tf);

		/**
	     * @brief Calculates new position of transform from rigidbody
	     * properties.
		 * 
	     * @param rb - The rigidbody component of the object.
	     * @param tf - The transform component of the object.
	     * @return void
	     */
		void update_rigidbody(Component::Rigidbody& rb, Component::Transform& tf);

		/**
	     * @brief Removes rigidbody component from object.
	     *
	     * @param rb - The rigidbody component of the object.
	     * @return void
	     */
		void delete_rigidbody(Component::Rigidbody& rb);

};