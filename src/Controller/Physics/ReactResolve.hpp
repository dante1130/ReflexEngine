#pragma once

#include "PhysicResolution.hpp"


class ReactResolve: public PhysicResolution{
	private:
		RigidBody* rb;

	public:
		ReactResolve();
	
		//using engine stuff
		bool usingReactResolve() override;

		// init setup
	    void init(glm::vec3 rot, glm::vec3 pos, float angle) override;

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

		void setType(BodyType type) override;
	    void enableGravity(bool ean) override;
	    void setCanSleep(bool ean) override;

		// Get properties
	    const float getMass() override;
	    const glm::vec3 getVelocity() override;
	    const glm::vec3 getAngVelocity() override;
	    const float getDragForce() override;
	    const float getDragTorque() override;

	    const BodyType getType() override;
	    const bool getIsGravityEnabled() override;
	    const bool getCanSleep() override;

		// Add colliders
	    void addBoxCollider(glm::vec3 pos, glm::vec3 size) override;
	    void addSphereCollider(glm::vec3 pos, float radius) override;
	    void addCapsuleCollider(glm::vec3 pos, float radius, float height) override;

	    // returns for GameObject position and rotation
	    const glm::vec3 getPosition() override;
	    const glm::vec3 getRotation() override;
	    const float getAngle() override;

		//makes it a trigger
	   // void setIsTrigger(bool ean);
};