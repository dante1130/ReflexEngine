#pragma once

#include "Controller/Physics/Physics.hpp"
#include "Controller/Physics/PhysicBody.hpp"
#include "Controller/Physics/EngineResolve.hpp"
#include "Controller/Physics/ReactResolve.hpp"

class Rigidbody{
public:

	void init(bool usingReact, glm::vec3 pos, glm::vec3 rot);

	Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot);

	Rigidbody() = default;

	/**
	 * @brief	default destructor
	 */
	~Rigidbody() = default;

	//****************************
	// FUNCTIONS FOR PHYSICS STUFF
	//****************************

	int colliderSize();
	glm::vec3 getColliderPosition(int index, Apply type);
	glm::vec4 getColliderOrientation(int index, Apply type);

	float getColliderBounce(int index);
	float getColliderFriction(int index);
	float getColliderMassDesity(int index);

	int getColliderType(int index);

	const BoxShape* getColliderBox(int index);
	const SphereShape* getColliderSphere(int index);
	const CapsuleShape* getColliderCapsule(int index);

	void addMaterialToCollider(int index, float bounce, float mass_density, float friction);

	void removeAllColliders();

	void setObjectTrigger(bool ean);

	bool usingReactResolve();

	void addForce(glm::vec3 force, Apply type);
	void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type);
	void addTorque(glm::vec3 torque, Apply type);

	void addDragForce(float drag);
	void addDragTorque(float ang_drag);

	void setMass(float mass);
	void setCenterOfMass(glm::vec3 p);
	void setVelocity(glm::vec3 vel);
	void setAngVelocity(glm::vec3 ang_vel);
	void setDragForce(float drag);
	void setDragTorque(float ang_drag);

	void setType(BodyType type);
	void setType(int type);
	void enableGravity(bool ean);
	void setCanSleep(bool ean);

	float getMass();
	glm::vec3 getVelocity();
	glm::vec3 getAngVelocity();
	float getDragForce();
	float getDragTorque();

	BodyType getType();
	bool getIsGravityEnabled();
	bool getCanSleep();
	bool getIsTrigger();

	void addBoxCollider(glm::vec3 pos, glm::vec3 size);
	void addSphereCollider(glm::vec3 pos, float radius);
	void addCapsuleCollider(glm::vec3 pos, float radius, float height);

	void addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction);
	void addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction);
	void addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::quat getOrientation();

	void setPosition(glm::vec3 pos);
	void setQuanternion(glm::quat quat);
	void setEulerRotation(glm::vec3 rot);

protected:

	//Physics system
	PhysicsBody* pb;

};