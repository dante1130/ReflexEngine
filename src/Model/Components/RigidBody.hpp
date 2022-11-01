#pragma once

#include "Controller/Physics/PhysicBody.hpp"
#include "Controller/Physics/ReactResolve.hpp"
#include "Controller/Physics/EngineResolve.hpp"

#include "glm/vec3.hpp"

namespace Component {
/**
 * @author Spencer Shaw
 * @class Rigidbody
 * @brief The rigidbody component gives access to all
 * physics and collision information of an object
 */
struct Rigidbody {
	/// Stores information about physics object
	PhysicsBody* pb;
	/// Whether gravity is enabled
	bool gravity_on;
	/// <summary>
	/// Whether the object is allowed to stop
	/// calculating resolution after a certain
	/// period of time
	/// </summary>
	bool can_sleep;
	/// Whether collision shapes are triggers
	bool is_trigger;

	/// Linear drag applied on object
	float lin_drag;
	/// Angular drag applied on object
	float ang_drag;
	/// Boolean determining resolution system
	bool using_react_start;

	std::string collider_obj_data = "";

	/// Default constructor
	Rigidbody() = default;

	/// Default copy constructor
	Rigidbody(const Rigidbody&) = default;

	Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot);

	Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot, bool gravity_on,
	          bool can_sleep, bool is_trigger, float linear_drag,
	          float angular_drag);

	PhysicsBody* getPhysicsBody() { return pb; }

	void init(bool usingReact, glm::vec3 pos, glm::vec3 rot);

	/**
	 * @brief Sets the transform properties of the rigidbody
	 *
	 * @param pos - Desired position
	 * @param rot - Desired euler rotation
	 * @return void
	 */
	void setTransform(glm::vec3 pos, glm::vec3 rot);

	/**
	 * @brief Sets the properties of the rigidbody that
	 * are visible from the GUI
	 *
	 * @param gravity_on - If gravity is applied to object
	 * @param can_sleep - If the object can sleep
	 * @param is_trigger - If the object is a trigger
	 * @param linear_drag - Linear force applied against objects movement
	 * @param angular_drag - Angular torque applied against objects
	 * rotational movement
	 * @return void
	 */
	void setViewables(bool gravity_on, bool can_sleep, bool is_trigger,
	                  float linear_drag, float angular_drag);

	/**
	 * @brief Returns true if physics body is using
	 * reactphysics3d resolution
	 *
	 * @return bool
	 */
	bool usingReactResolve();

	/**
	 * @brief Returns true if the object has been
	 * properly intialised and set
	 *
	 * @return bool
	 */
	bool intialised();

	/**
	 * @brief Applies physics calculations and finds the new
	 * transform properties of the object
	 *
	 * @param delta_time - The delta time
	 * @return void
	 */
	void update(float delta_time);

	/**
	 * @brief Removes a the body (CollisionBody/Rigidbody)
	 * of PhysicsBody and its properties
	 *
	 * @return void
	 */
	void deleteBody();

	/**
	 * @brief Returns the size of the colliders
	 *
	 * @return size_t
	 */
	size_t colliderSize();

	/**
	 * @brief Gets the local or world position center
	 * of the object
	 *
	 * @param index - Index of collider
	 * @param type - An enum determining local or world position
	 * @return glm::vec3
	 */
	glm::vec3 getColliderPosition(size_t index, Apply type);

	/**
	 * @brief Gets the bounciness property of a
	 * given colliders
	 *
	 * @param index - Index of collider
	 * @return float
	 */
	float getColliderBounce(size_t index);

	/**
	 * @brief Gets the friction property of a
	 * given colliders
	 *
	 * @param index - Index of collider
	 * @return float
	 */
	float getColliderFriction(size_t index);

	/**
	 * @brief Gets the mass density property of a
	 * given colliders
	 *
	 * @param index - Index of collider
	 * @return float
	 */
	float getColliderMassDesity(size_t index);

	/**
	 * @brief Gets the shape of the collider as
	 * an integer value
	 *
	 * @param index - Index of collider
	 * @return int
	 */
	int getColliderType(size_t index);

	/**
	 * @brief Returns a pseduo name containing the
	 * collider type and index of the collider
	 *
	 * @param index - Index of collider
	 * @return std::string
	 */
	std::string getColliderName(size_t index);

	/**
	 * @brief Gets all collider pointers inside
	 * colliders
	 *
	 * @return std::vector<rp3d::Collider*>
	 */
	std::vector<rp3d::Collider*> getColliders();

	/**
	 * @brief Returns pointer to box collider
	 * if collider at index is a box type
	 *
	 * @param index - Index of collider
	 * @return rp3d::BoxShape*
	 */
	rp3d::BoxShape* getColliderBox(size_t index);

	/**
	 * @brief Returns pointer to sphere collider
	 * if collider at index is a sphere type
	 *
	 * @param index - Index of collider
	 * @return rp3d::SphereShape*
	 */
	rp3d::SphereShape* getColliderSphere(size_t index);

	/**
	 * @brief Returns pointer to capsule collider
	 * if collider at index is a capsule type
	 *
	 * @param index - Index of collider
	 * @return rp3d::CapsuleShape*
	 */
	rp3d::CapsuleShape* getColliderCapsule(size_t index);

	/**
	 * @brief Adds a material to a collider at
	 * a given index
	 *
	 * @param index - Index of collider
	 * @param bounce - The value of bounciness property
	 * @param mass_density - The value of mass density property
	 * @param friction - The value of friction property
	 * @return void
	 */
	void addMaterialToCollider(size_t index, float bounce, float mass_density,
	                           float friction);

	/**
	 * @brief Remove all colliders in body
	 *
	 * @return void
	 */
	void removeAllColliders();

	/**
	 * @brief Removes collider at given index
	 *
	 * @param index - Index of collider
	 * @return void
	 */
	void removeCollider(size_t index);

	/**
	 * @brief Sets if the object is a trigger
	 *
	 * @param ean - if the object should be a trigger
	 * @return void
	 */
	void setObjectTrigger(bool ean);

	/**
	 * @brief Sets if the object has gravity applied
	 *
	 * @param ean - if the object should have gravity applied
	 * @return void
	 */
	void enableGravity(bool ean);

	/**
	 * @brief Sets if the object can sleep
	 *
	 * @param ean - if the object should be able to sleep
	 * @return void
	 */
	void setCanSleep(bool ean);

	/**
	 * @brief Gets if the object has gravity applied
	 *
	 * @return bool
	 */
	bool getIsGravityEnabled();

	/**
	 * @brief Gets if the object can sleep
	 *
	 * @return bool
	 */
	bool getCanSleep();

	/**
	 * @brief Gets if the object is a trigger
	 *
	 * @return bool
	 */
	bool getIsTrigger();

	/**
	 * @brief Adds a force to an object's center of mass
	 *
	 * @param force - the size of the force applied
	 * @param type - An enum determining local or world position
	 * @return void
	 */
	void addForce(glm::vec3 force, Apply type);

	/**
	 * @brief Adds a force to an object at a given point
	 *
	 * @param force - the size of the force applied
	 * @param force - position of applied force
	 * @param type - An enum determining relative position to
	 * object
	 * @return void
	 */
	void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type);

	/**
	 * @brief Adds torque to an object
	 *
	 * @param force - the size of the torque applied
	 * @param type - An enum determining relative position to
	 * object
	 * @return void
	 */
	void addTorque(glm::vec3 torque, Apply type);

	/**
	 * @brief Adds a drag force to an object
	 *
	 * @param drag - the size of the drag force applied
	 * @return void
	 */
	void addDragForce(float drag);

	/**
	 * @brief Adds a torque drag to an object
	 *
	 * @param ang_drag - the size of the torque drag applied
	 * @return void
	 */
	void addDragTorque(float ang_drag);

	/**
	 * @brief Sets the total mass of object
	 *
	 * @param mass - the size of the mass
	 * @return void
	 */
	void setMass(float mass);

	/**
	 * @brief Sets the center of mass
	 *
	 * @param mass - the desired center of mass
	 * @return void
	 */
	void setCenterOfMass(glm::vec3 p);

	/**
	 * @brief Sets the velocity of object
	 *
	 * @param vel - the desired velocity
	 * @return void
	 */
	void setVelocity(glm::vec3 vel);

	/**
	 * @brief Sets the angular velocity of object
	 *
	 * @param ang_vel - the desired angular velocity
	 * @return void
	 */
	void setAngVelocity(glm::vec3 ang_vel);

	/**
	 * @brief Sets the linear drag on object
	 *
	 * @param drag - the desired linear drag
	 * @return void
	 */
	void setDragForce(float drag);

	/**
	 * @brief Sets the angular drag on object
	 *
	 * @param angular_drag - the desired angular drag
	 * @return void
	 */
	void setDragTorque(float angular_drag);

	/**
	 * @brief Sets the physics type (Static, Kinematic
	 * or Dynamic)
	 *
	 * @param type - the desired physics type as an integer
	 * @return void
	 */
	void setType(int type);

	/**
	 * @brief Gets the total mass of object
	 *
	 * @return float
	 */
	float getMass();

	/**
	 * @brief Gets the velocity of object
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getVelocity();

	/**
	 * @brief Gets the angular of object
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getAngVelocity();

	/**
	 * @brief Gets the linear drag of object
	 *
	 * @return float
	 */
	float getDragForce();

	/**
	 * @brief Gets the angular drag of object
	 *
	 * @return float
	 */
	float getDragTorque();

	/**
	 * @brief Gets the object type as an integer
	 *
	 * @return int
	 */
	int getType();

	/**
	 * @brief Creates and adds a box collider to object
	 *
	 * @param pos - the desired position
	 * @param rot - the desired rotation
	 * @param size - the desired half extents
	 * @param friction - the friction property
	 * @param epsilone - the coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 rot, glm::vec3 size,
	                        float friction, float mass, float epsilon);

	/**
	 * @brief Creates and adds a sphere collider to object
	 *
	 * @param pos - the desired position
	 * @param rot - the desired rotation
	 * @param radius - the desired radius
	 * @param friction - the friction property
	 * @param epsilone - the coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addSphereCollider(glm::vec3 pos, glm::vec3 rot, float radius,
	                           float friction, float mass, float epsilon);

	/**
	 * @brief Creates and adds a capsule collider to object
	 *
	 * @param pos - the desired position
	 * @param rot - the desired rotation
	 * @param radius - the desired radius
	 * @param height - the desired height
	 * @param friction - the friction property
	 * @param epsilone - the coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addCapsuleCollider(glm::vec3 pos, glm::vec3 rot, float radius,
	                            float height, float friction, float mass,
	                            float epsilon);

	/**
	 * @brief Gets the position of the rigidbody
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getPosition();

	/**
	 * @brief Gets the euler rotation of the
	 * rigidbody
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getRotation();

	/**
	 * @brief Gets the quanterion orientation of
	 * the rigidbody
	 *
	 * @return glm::vec3
	 */
	glm::quat getOrientation();

	/**
	 * @brief Sets the position of the rigidbody
	 *
	 * @param pos - the desired position
	 * @return void
	 */
	void setPosition(glm::vec3 pos);

	/**
	 * @brief Sets the quanterion orientation of
	 * the rigidbody
	 *
	 * @param quat - the desired orientation
	 * @return void
	 */
	void setQuanternion(glm::quat quat);

	/**
	 * @brief Sets the euler rotation of
	 * the rigidbody
	 *
	 * @param rot - the desired rotation
	 * @return void
	 */
	void setEulerRotation(glm::vec3 rot);

	/**
	 * @brief Gets the previous position of
	 * the rigidbody
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getPreviousPosition();

	/**
	 * @brief Sets the previous position of
	 * the rigidbody
	 *
	 * @param prev_pos - the previous position
	 * @return void
	 */
	void setPreviousPosition(glm::vec3 prev_pos);


	bool isSleeping();

	void setIsSleeping(bool ean);
};
};  // namespace Component
