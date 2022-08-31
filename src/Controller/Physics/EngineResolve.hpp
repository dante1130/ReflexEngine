#pragma once

#include "PhysicBody.hpp"

struct bool3 {
	bool lock_x, lock_y, lock_z;

	bool3() = default;

	bool3(bool x, bool y, bool z): 
		lock_x(x), lock_y(y), lock_z(z) {}
};

class EngineResolve : public PhysicsBody {

private:

	rp3d::CollisionBody* cb;

protected:

	glm::vec3 lin_velocity_; 
	glm::vec3 lin_accelaration_;

	glm::vec3 force_;

	float lin_drag;

	float mass_;

	rp3d::BodyType type_;

	glm::vec3 gravity_;

	bool use_gravity_;
	bool can_sleep_;

	glm::vec3 collision_axes;

	bool3 lock_axes_back;
	bool3 lock_axes_front;

public:

	EngineResolve();

	void update(float delta_time) override;

	void stop(glm::vec3 normal, CollisionEvent c_type) override;

	// using engine stuff
	bool usingReactResolve() override;

	// init setup
	void initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) override;
	void initialise_body(glm::vec3 pos, glm::vec3 rot) override;

	void delete_body() override;

	//Change movement properties
	void addForce(glm::vec3 force, Apply type) override;
	void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type) override;
	void addTorque(glm::vec3 torque, Apply type) override;

	void addDragForce(float drag) override;
	void addDragTorque(float ang_drag) override;

	//Set properties
	void setMass(float mass) override;
	void setCenterOfMass(glm::vec3 p) override;
	void setVelocity(glm::vec3 vel) override;
	void setAngVelocity(glm::vec3 ang_vel) override;
	void setDragForce(float drag) override;
	void setDragTorque(float ang_drag) override;

	void setType(rp3d::BodyType type) override;
	void setType(int type) override;
	void enableGravity(bool ean) override;
	void setCanSleep(bool ean) override;

	// Get properties
	float getMass() override;
	glm::vec3 getVelocity() override;
	glm::vec3 getAngVelocity() override;

	float getDragForce() override;
	float getDragTorque() override;

	rp3d::BodyType getType() override;
	bool getIsGravityEnabled() override;
	bool getCanSleep() override;

	// Add colliders
	uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size) override;
	uint32_t addSphereCollider(glm::vec3 pos, float radius) override;
	uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height) override;

	uint32_t addBoxCollider(PhysicsBody* rb, glm::vec3 pos, glm::vec3 size,
	                        float bounce, float friction) override;
	uint32_t addSphereCollider(PhysicsBody* rb, glm::vec3 pos, float radius,
	                           float bounce,
	                           float friction) override;
	uint32_t addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos, float radius,
	                            float height,
	                            float bounce, float friction) override;

	uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size,
	                        float bounce, float friction) override;
	uint32_t addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction) override;
	uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction) override;

	void deleteCollider(rp3d::Collider* collider) override;

	// returns for GameObject position and rotation
	glm::vec3 getPosition() override;
	glm::vec3 getRotation() override;
	glm::quat getOrientation() override;
	float getAngle() override;

	void setPosition(glm::vec3 pos) override;
	void setQuaternion(glm::quat quat) override;
	void setEulerRotation(glm::vec3 rot) override;
	void setRotation(glm::vec3 rot) override;
	void setAngle(float ang) override;
};