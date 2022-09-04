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
private:
	/// Stores information about physics object
	PhysicsBody* pb;

public:
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

	/// Linear drag
	float lin_drag;
	/// Angular drag
	float ang_drag;

	bool using_react_start;

	std::string collider_obj_data = "";

	Rigidbody() = default;

	Rigidbody(const Rigidbody&) = default;

	Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot);

	Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot, bool gravity_on,
	          bool can_sleep, bool is_trigger, float linear_drag,
	          float angular_drag);

	void init(bool usingReact, glm::vec3 pos, glm::vec3 rot);

	void setTransform(glm::vec3 pos, glm::vec3 rot);

	void setViewables(bool gravity_on, bool can_sleep, bool is_trigger,
	                  float linear_drag, float angular_drag);

	/// Returns true if physics body is using
	/// reactphysics3d resolution
	bool usingReactResolve();

	bool intialised();

	// update
	void update(float delta_time);

	void deleteBody();
	/// COLLIDERS

	/**
	 * @brief Returns the size of the colliders
	 *
	 * @return size_t - size of colliders vector
	 */
	size_t colliderSize();

	/**
	 * @brief Gets the local or world position center
	 * of the object
	 *
	 * @param size_t - Index of collider
	 * @param Apply - An enum determining local or world position
	 * @return glm::vec3 - The position of collider
	 */
	glm::vec3 getColliderPosition(size_t index, Apply type);

	/**
	 * @brief Gets the bounciness property of a
	 * given colliders
	 *
	 * @param size_t - Index of collider
	 * @return float - The value of bounciness property
	 */
	float getColliderBounce(size_t index);

	/**
	 * @brief Gets the friction property of a
	 * given colliders
	 *
	 * @param size_t - Index of collider
	 * @return float - The value of friction property
	 */
	float getColliderFriction(size_t index);

	/**
	 * @brief Gets the mass density property of a
	 * given colliders
	 *
	 * @param size_t - Index of collider
	 * @return float - The value of mass density property
	 */
	float getColliderMassDesity(size_t index);

	/**
	 * @brief Gets the shape of the collider as
	 * an integer value
	 *
	 * @param size_t - Index of collider
	 * @return int - The collider shape expressed as integer
	 */
	int getColliderType(size_t index);

	/**
	 * @brief Returns a pseduo name containing the
	 * collider type and index of the collider
	 *
	 * @param size_t - Index of collider
	 * @return std::string - The created name
	 */
	std::string getColliderName(size_t index);

	/**
	 * @brief Gets all collider pointers inside
	 * colliders
	 *
	 * @param size_t - Index of collider
	 * @return std::vector<rp3d::Collider*> - colliders
	 */
	std::vector<rp3d::Collider*> getColliders();

	/**
	 * @brief Returns pointer to box collider
	 * if collider at index is a box type
	 *
	 * @param size_t - Index of collider
	 * @return rp3d::BoxShape* - Box collider
	 */
	rp3d::BoxShape* getColliderBox(size_t index);

	/**
	 * @brief Returns pointer to sphere collider
	 * if collider at index is a sphere type
	 *
	 * @param size_t - Index of collider
	 * @return rp3d::SphereShape* - Sphere collider
	 */
	rp3d::SphereShape* getColliderSphere(size_t index);

	/**
	 * @brief Returns pointer to capsule collider
	 * if collider at index is a capsule type
	 *
	 * @param size_t - Index of collider
	 * @return rp3d::CapsuleShape* - Capsule collider
	 */
	rp3d::CapsuleShape* getColliderCapsule(size_t index);

	/**
	 * @brief Adds a material to a collider at
	 * a given index
	 *
	 * @param size_t - Index of collider
	 * @param float - The value of bounciness property
	 * @param float - The value of mass density property
	 * @param size_t - The value of friction property
	 */
	void addMaterialToCollider(size_t index, float bounce, float mass_density,
	                           float friction);

	/**
	 * @brief Remove all colliders in body
	 *
	 */
	void removeAllColliders();

	/**
	 * @brief Removes collider at given index
	 *
	 * @param size_t - Index of collider
	 */
	void removeCollider(size_t index);

	// Gui viewable variables methods

	void setObjectTrigger(bool ean);

	void enableGravity(bool ean);

	void setCanSleep(bool ean);

	bool getIsGravityEnabled();

	bool getCanSleep();

	bool getIsTrigger();

	// Applying interaction methods

	void addForce(glm::vec3 force, Apply type);

	void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type);

	void addTorque(glm::vec3 torque, Apply type);

	void addDragForce(float drag);

	void addDragTorque(float ang_drag);

	// Set methods

	void setMass(float mass);

	void setCenterOfMass(glm::vec3 p);

	void setVelocity(glm::vec3 vel);

	void setAngVelocity(glm::vec3 ang_vel);

	void setDragForce(float drag);

	void setDragTorque(float angular_drag);

	void setType(int type);

	// Get methods

	float getMass();

	glm::vec3 getVelocity();

	glm::vec3 getAngVelocity();

	float getDragForce();

	float getDragTorque();

	int getType();

	// Collider methods

	// void addBoxCollider(glm::vec3 pos, glm::vec3 size) {
	// pb->addBoxCollider(pos, size); }

	// void addSphereCollider(glm::vec3 pos, float radius) {
	// pb->addSphereCollider(pos, radius); }

	// void addCapsuleCollider(glm::vec3 pos, float radius, float height) {
	// pb->addCapsuleCollider(pos, radius, height); }

	uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce,
	                        float friction);

	uint32_t addSphereCollider(glm::vec3 pos, float radius, float bounce,
	                           float friction);

	uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height,
	                            float bounce, float friction);

	// Methods used for transform

	glm::vec3 getPosition();

	glm::vec3 getRotation();

	glm::quat getOrientation();

	void setPosition(glm::vec3 pos);

	void setQuanternion(glm::quat quat);

	void setEulerRotation(glm::vec3 rot);

	glm::vec3 getPreviousPosition();

	void setPreviousPosition(glm::vec3 prev_pos);
};
};  // namespace Component
