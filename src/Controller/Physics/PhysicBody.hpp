#pragma once

#include "Physics.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

//These are to make it easier to determine where a force
//in the game world is can be applied

enum class Apply {
	LOCAL,
	WORLD
};

enum class ApplyPoint {
	LOCAL_LOCAL,
	LOCAL_WORLD,
	WORLD_LOCAL,
	WORLD_WORLD
};


class PhysicsBody
{
	//This is basically what physics object should be, might need to change it up

	protected:
	    std::vector<Collider*> colliders;

		std::unordered_map<int, BoxShape*> m_box;
		std::unordered_map<int, SphereShape*>  m_sphere;
		std::unordered_map<int, CapsuleShape*>  m_capsule;


	public:

		//collider access
		const int colliderSize();
		const glm::vec3 getColliderPosition(int index, Apply type);
		const glm::vec4 getColliderOrientation(int index, Apply type);

		const float getColliderBounce(int index);
		const float getColliderFriction(int index);
		const float getColliderMassDesity(int index);

		const int getColliderType(int index);

		void setObjectTrigger(bool ean);

		const BoxShape* getColliderBox(int index);
		const SphereShape* getColliderSphere(int index);
		const CapsuleShape* getColliderCapsule(int index);

		void addMaterialToCollider(int index, float bounce, float mass_density, float friction);

		void removeAllColliders();
	    // collision resolution system type check
	    virtual bool usingReactResolve() = 0;

		//init setup
	    virtual void init(glm::vec3 rot, glm::vec3 pos, float angle) = 0;


		//Change movement properties
	    virtual void addForce(glm::vec3 force, Apply type) = 0;
	    virtual void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type) = 0;
	    virtual void addTorque(glm::vec3 torque, Apply type) = 0;

		virtual void addDragForce(float drag) = 0;
	    virtual void addDragTorque(float ang_drag) = 0;

		//Set properties
	    virtual void setMass(float mass) = 0;
	    virtual void setCenterOfMass(glm::vec3 p) = 0;
	    virtual void setVelocity(glm::vec3 vel) = 0;
	    virtual void setAngVelocity(glm::vec3 ang_vel) = 0;

		virtual void setType(BodyType type) = 0;
		virtual void setType(int type) = 0;
	    virtual void enableGravity(bool ean) = 0;
	    virtual void setCanSleep(bool ean) = 0;

		//Get properties
	    virtual const float getMass() = 0;
	    virtual const glm::vec3 getVelocity() = 0;
	    virtual const glm::vec3 getAngVelocity() = 0;
	    virtual const float getDragForce() = 0;
	    virtual const float getDragTorque() = 0;

		virtual const BodyType getType() = 0;
	    virtual const bool getIsGravityEnabled() = 0;
	    virtual const bool getCanSleep() = 0;

		//Add colliders
	    virtual void addBoxCollider(glm::vec3 pos, glm::vec3 size) = 0;
	    virtual void addSphereCollider(glm::vec3 pos, float radius) = 0;
	    virtual void addCapsuleCollider(glm::vec3 pos, float radius, float height) = 0;


		virtual void addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) = 0;
		virtual void addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction) = 0;
		virtual void addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction) = 0;

		//returns for GameObject position and rotation
	    virtual const glm::vec3 getPosition() = 0;
	    virtual const glm::vec3 getRotation() = 0;
	    virtual const float getAngle() = 0;

		virtual void setPosition(glm::vec3 pos) = 0;
		virtual void setRotation(glm::vec3 rot) = 0;
		virtual void setAngle(float ang) = 0;

};