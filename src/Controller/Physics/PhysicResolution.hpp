#pragma once

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "BodyRigidPhysics.hpp"
#include "reactphysics3d/collision/Collider.h"

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


class PhysicResolution
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

		const BoxShape* getColliderBox(int index);
		const SphereShape* getColliderSphere(int index);
		const CapsuleShape* getColliderCapsule(int index);

		void addMaterialToCollider(int index, float bounce, float mass_density, float friction);

		void removeAllColliders();

	    // collision resolution system type check
	    virtual bool usingReactResolve();

		//init setup
	    virtual void init(glm::vec3 rot, glm::vec3 pos, float angle);

		//virtual void update(float delta_time) - maybe?, probs not?

		//Change movement properties
	    virtual void addForce(glm::vec3 force, Apply type);
	    virtual void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type);
	    virtual void addTorque(glm::vec3 torque, Apply type);

		virtual void addDragForce(float drag);
	    virtual void addDragTorque(float ang_drag);

		//Set properties
	    virtual void setMass(float mass);
	    virtual void setCenterOfMass(glm::vec3 p);
	    virtual void setVelocity(glm::vec3 vel);
	    virtual void setAngVelocity(glm::vec3 ang_vel);

		virtual void setType(BodyType type);
	    virtual void enableGravity(bool ean);
	    virtual void setCanSleep(bool ean);

		//Get properties
	    virtual const float getMass();
	    virtual const glm::vec3 getVelocity();
	    virtual const glm::vec3 getAngVelocity();
	    virtual const float getDragForce();
	    virtual const float getDragTorque();

		virtual const BodyType getType();
	    virtual const bool getIsGravityEnabled();
	    virtual const bool getCanSleep();

		//Add colliders
	    virtual void addBoxCollider(glm::vec3 pos, glm::vec3 size);
	    virtual void addSphereCollider(glm::vec3 pos, float radius);
	    virtual void addCapsuleCollider(glm::vec3 pos, float radius, float height);

		//returns for GameObject position and rotation
	    virtual const glm::vec3 getPosition();
	    virtual const glm::vec3 getRotation();
	    virtual const float getAngle();

};