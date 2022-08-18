#pragma once

#include "PhysicBody.hpp"

class EngineResolve : public PhysicsBody {

private:

	rp3d::CollisionBody* cb;

	//This is going to be physics properties
	// - velocity, ang_velocity
	// - accelaration, ang_accelaration
	// - mass, material properties (maybe)

public:

	EngineResolve();

	// using engine stuff
	bool usingReactResolve() override;

	// init setup
	void init(glm::vec3 pos, glm::vec3 rot, float angle) override;
	void init(glm::vec3 pos, glm::vec3 rot) override;

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
	void addBoxCollider(glm::vec3 pos, glm::vec3 size) override;
	void addSphereCollider(glm::vec3 pos, float radius) override;
	void addCapsuleCollider(glm::vec3 pos, float radius, float height) override;

	void addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) override;
	void addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction) override;
	void addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction) override;

	// returns for GameObject position and rotation
	glm::vec3 getPosition() override;
	glm::vec3 getRotation() override;
	glm::quat getOrientation() override;
	float getAngle() override;

	void setPosition(glm::vec3 pos) override;
	void setQuanternion(glm::quat quat) override;
	void setEulerRotation(glm::vec3 rot) override;
	void setRotation(glm::vec3 rot) override;
	void setAngle(float ang) override;
};