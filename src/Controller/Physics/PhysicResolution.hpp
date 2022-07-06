#pragma once

#include "glm/vec3.hpp"
#include "BodyRigidPhysics.hpp"

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
		CollisionBody* cb;
	    std::vector<Collider*> colliders;

	public:

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

		//Add colliders
	    void addBoxCollider(glm::vec3 pos, glm::vec3 size);
	    void addSphereCollider(glm::vec3 pos, float radius);
	    void addCapsuleCollider(glm::vec3 pos, float radius, float height);

		//returns for GameObject position and rotation
	    glm::vec3 getPosition();
	    glm::vec3 getRotation();
	    float getAngle();

};