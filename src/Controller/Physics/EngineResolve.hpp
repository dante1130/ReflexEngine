#pragma once

#include "PhysicBody.hpp"
#include <glm.hpp>

struct Motion_Stats {
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float drag;

	Motion_Stats()
	    : velocity(glm::vec3(0)), acceleration(glm::vec3(0)), drag(0) {}
};

class EngineResolve : public PhysicsBody {
private:
	rp3d::CollisionBody* collision_body_;

	Motion_Stats linear_;
	Motion_Stats angular_;

	float total_mass_ = 0;

	rp3d::BodyType body_type_ = rp3d::BodyType::STATIC;

	bool use_gravity_ = false;
	bool can_sleep_ = false;

public:
	EngineResolve();

	/**
	 * @brief Calculates collison response and applies it to
	 * rigidbody
	 *
	 * @param lambda - The lambda value for the transfer of momentum
	 * @param normal - The collision normal
	 * @param c_type - The collision event type
	 * @return void
	 */
	void resolve(float lambda, glm::vec3 vector_to_collision,
	             glm::vec3 contact_normal, int collision_number) override;

	/**
	 * @brief Returns boolean of if the body is using reactphysics3d
	 * collision resolution or the engines collision resolution
	 *
	 * @return bool
	 */
	bool usingReactResolve() override;

	/**
	 * @brief Applies physics calculations and finds the new
	 * transform properties of the object
	 *
	 * @param delta_time - The delta time
	 * @return void
	 */
	void update(float delta_time) override;

	/**
	 * @brief Intialises rigidbody with axis angle rotation
	 *
	 * @param pos - The desired position
	 * @param rot - The desired axis
	 * @param angle - The desired angle
	 * @return void
	 */
	void initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) override;

	/**
	 * @brief Intialises rigidbody with euler rotation
	 *
	 * @param pos - The desired position
	 * @param rot - The desired rotation
	 * @return void
	 */
	void initialise_body(glm::vec3 pos, glm::vec3 rot) override;

	/**
	 * @brief Removes a the body (CollisionBody/Rigidbody)
	 * of PhysicsBody and its properties
	 *
	 * @return void
	 */
	void delete_body() override;

	/**
	 * @brief Deletes a specified collider form rigidbody
	 *
	 * @param collider - Pointer to collider for deletion
	 * @return void
	 */
	void deleteCollider(rp3d::Collider* collider) override;

	/**
	 * @brief Adds a force to an object's center of mass
	 *
	 * @param force - The size of the force applied
	 * @param type - An enum determining local or world position
	 * @return void
	 */
	void addForce(glm::vec3 force, Apply type) override;

	/**
	 * @brief Adds a force to an object at a given point
	 *
	 * @param force - The size of the force applied
	 * @param point - Position of applied force
	 * @param type - An enum determining relative position to
	 * object
	 * @return void
	 */
	void addForceAtPoint(glm::vec3 force, glm::vec3 point,
	                     ApplyPoint type) override;

	/**
	 * @brief Adds torque to an object
	 *
	 * @param force - The size of the torque applied
	 * @param type - An enum determining relative position to
	 * object
	 * @return void
	 */
	void addTorque(glm::vec3 torque, Apply type) override;

	/**
	 * @brief Adds a drag force to an object
	 *
	 * @param drag - The size of the drag force applied
	 * @return void
	 */
	void addDragForce(float drag) override;

	/**
	 * @brief Adds a torque drag to an object
	 *
	 * @param ang_drag - The size of the torque drag applied
	 * @return void
	 */
	void addDragTorque(float ang_drag) override;

	/**
	 * @brief Sets the total mass of object
	 *
	 * @param mass - The size of the mass
	 * @return void
	 */
	void setMass(float mass) override;

	/**
	 * @brief Sets the center of mass
	 *
	 * @param p - The desired center of mass
	 * @return void
	 */
	void setCenterOfMass(glm::vec3 cOFmass) override;

	/**
	 * @brief Sets the velocity of object
	 *
	 * @param vel - The desired velocity
	 * @return void
	 */
	void setVelocity(glm::vec3 vel) override;

	/**
	 * @brief Sets the angular velocity of object
	 *
	 * @param ang_vel - The desired angular velocity
	 * @return void
	 */
	void setAngVelocity(glm::vec3 ang_vel) override;

	/**
	 * @brief Sets the linear drag on object
	 *
	 * @param drag - The desired linear drag
	 * @return void
	 */
	void setDragForce(float drag) override;

	/**
	 * @brief Sets the angular drag on object
	 *
	 * @param angular_drag - The desired angular drag
	 * @return void
	 */
	void setDragTorque(float ang_drag) override;

	/**
	 * @brief Sets the physics type (Static, Kinematic
	 * or Dynamic)
	 *
	 * @param type - The desired physics type
	 * @return void
	 */
	void setType(rp3d::BodyType type) override;

	/**
	 * @brief Sets the physics type (Static, Kinematic
	 * or Dynamic)
	 *
	 * @param type - The desired physics type as an integer
	 * @return void
	 */
	void setType(int type) override;

	/**
	 * @brief Sets if the object has gravity applied
	 *
	 * @param ean - If the object should have gravity applied
	 * @return void
	 */
	void enableGravity(bool ean) override;

	/**
	 * @brief Sets if the object can sleep
	 *
	 * @param ean - If the object should be able to sleep
	 * @return void
	 */
	void setCanSleep(bool ean) override;

	/**
	 * @brief Gets the total mass of object
	 *
	 * @return float
	 */
	float getMass() override;

	/**
	 * @brief Gets the velocity of object
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getVelocity() override;

	/**
	 * @brief Gets the angular of object
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getAngVelocity() override;

	/**
	 * @brief Gets the linear drag of object
	 *
	 * @return float
	 */
	float getDragForce() override;

	/**
	 * @brief Gets the angular drag of object
	 *
	 * @return float
	 */
	float getDragTorque() override;

	/**
	 * @brief Gets the object type
	 *
	 * @return rp3d::BodyType
	 */
	rp3d::BodyType getType() override;

	/**
	 * @brief Gets if the object has gravity applied
	 *
	 * @return bool
	 */
	bool getIsGravityEnabled() override;

	/**
	 * @brief Gets if the object can sleep
	 *
	 * @return bool
	 */
	bool getCanSleep() override;

	/**
	 * @brief Creates and adds a box collider to object
	 * with no material properties
	 *
	 * @param pos - The desired position
	 * @param size - The desired half extents
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size, float mass,
	                        float epsilon) override;

	/**
	 * @brief Creates and adds a sphere collider to object
	 * with no material properties
	 *
	 * @param pos - The desired position
	 * @param radius - The desired radius
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addSphereCollider(glm::vec3 pos, float radius, float mass,
	                           float epsilon) override;

	/**
	 * @brief Creates and adds a capsule collider to object
	 * with no material properties
	 *
	 * @param pos - The desired position
	 * @param radius - The desired radius
	 * @param height - The desired height
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height,
	                            float mass, float epsilon) override;

	/**
	 * @brief Creates and adds a box collider to object
	 * and links the rigidbody data to it
	 *
	 * @param rb - Pointer to physicsbody for linking
	 * @param pos - The desired position
	 * @param size - The desired half extents
	 * @param bounce - The bounciness property
	 * @param friction - The friction property
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addBoxCollider(PhysicsBody* rb, glm::vec3 pos, glm::vec3 size,
	                        float bounce, float friction, float mass,
	                        float epsilon) override;

	/**
	 * @brief Creates and adds a sphere collider to object
	 * and links the rigidbody data to it
	 *
	 * @param rb - Pointer to physicsbody for linking
	 * @param pos - The desired position
	 * @param radius - The desired radius
	 * @param bounce - The bounciness property
	 * @param friction - The friction property
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addSphereCollider(PhysicsBody* rb, glm::vec3 pos, float radius,
	                           float bounce, float friction, float mass,
	                           float epsilon) override;

	/**
	 * @brief Creates and adds a capsule collider to object
	 * and links the rigidbody data to it
	 *
	 * @param rb - Pointer to physicsbody for linking
	 * @param pos - The desired position
	 * @param radius - The desired radius
	 * @param height - The desired height
	 * @param bounce - The bounciness property
	 * @param friction - The friction property
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos, float radius,
	                            float height, float bounce, float friction,
	                            float mass, float epsilon) override;

	/**
	 * @brief Creates and adds a box collider to object
	 *
	 * @param pos - The desired position
	 * @param size - The desired half extents
	 * @param bounce - The bounciness property
	 * @param friction - The friction property
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce,
	                        float friction, float mass, float epsilon) override;

	/**
	 * @brief Creates and adds a sphere collider to object
	 *
	 * @param pos - The desired position
	 * @param radius - The desired radius
	 * @param bounce - The bounciness property
	 * @param friction - The friction property
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addSphereCollider(glm::vec3 pos, float radius, float bounce,
	                           float friction, float mass,
	                           float epsilon) override;

	/**
	 * @brief Creates and adds a capsule collider to object
	 *
	 * @param pos - The desired position
	 * @param radius - The desired radius
	 * @param height - The desired height
	 * @param bounce - The bounciness property
	 * @param friction - The friction property
	 * @param mass - The mass of the collider
	 * @param epsilon - coefficient of restitution
	 * @return uint32_t
	 */
	uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height,
	                            float bounce, float friction, float mass,
	                            float epsilon) override;

	/**
	 * @brief Calcualtes the inertia tensor for a box
	 *
	 * @param size The size of the box
	 * @param mass THe mass of the box
	 * @return glm::mat3x3
	 */
	static glm::mat3x3 inertia_tensor_box(glm::vec3 size, float mass);

	/**
	 * @brief Calculates the inertia tensor for the sphere
	 *
	 * @param radius The radius of the sphere
	 * @param mass The mass of the sphere
	 * @return glm::mat3x3
	 */
	static glm::mat3x3 inertia_tensor_sphere(float radius, float mass);

	/**
	 * @brief Calculates the inertia tensor for a capsule
	 *
	 * @param radius The radius of the capsule
	 * @param height The height of the capsule
	 * @param mass The mass of the capsule
	 * @return glm::mat3x3
	 */
	static glm::mat3x3 inertia_tensor_capsule(float radius, float height,
	                                          float mass);

	/**
	 * @brief Gets the position of the rigidbody
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getPosition() override;

	/**
	 * @brief Gets the euler rotation of the
	 * rigidbody
	 *
	 * @return glm::vec3
	 */
	glm::vec3 getRotation() override;

	/**
	 * @brief Gets the quanterion orientation of
	 * the rigidbody
	 *
	 * @return glm::vec3
	 */
	glm::quat getOrientation() override;

	/**
	 * @brief Gets the w component of quanternion
	 *
	 * @return glm::vec3
	 */
	float getAngle() override;

	/**
	 * @brief Sets the position of the rigidbody
	 *
	 * @param pos - The desired position
	 * @return void
	 */
	void setPosition(glm::vec3 pos) override;

	/**
	 * @brief Sets the quanterion orientation of
	 * the rigidbody
	 *
	 * @param quat - The desired orientation
	 * @return void
	 */
	void setQuaternion(glm::quat quat) override;

	/**
	 * @brief Sets the euler rotation of
	 * the rigidbody
	 *
	 * @param rot - The desired rotation
	 * @return void
	 */
	void setEulerRotation(glm::vec3 rot) override;

	/**
	 * @brief Sets the x, y, z components of
	 * the qunaternion
	 *
	 * @param rot - The desired x, y, z
	 * @return void
	 */
	void setRotation(glm::vec3 rot) override;

	/**
	 * @brief Sets the w component of quanternion
	 *
	 * @param ang - The desired w
	 * @return void
	 */
	void setAngle(float ang) override;
};