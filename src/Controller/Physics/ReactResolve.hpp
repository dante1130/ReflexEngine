#pragma once

#include "PhysicBody.hpp"


class ReactResolve: public PhysicsBody{
	private:
		rp3d::RigidBody* rb;

	public:
		ReactResolve();
	
		//using engine stuff
		bool usingReactResolve() override;

		// Update function
	    void update(float delta_time) override;

		void stop(rp3d::CollisionCallback::ContactPair::EventType c_type) override;

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

		uint32_t addBoxCollider(PhysicsBody* rb, glm::vec3 pos, glm::vec3 size, float bounce, float friction) override;
	    uint32_t addSphereCollider(PhysicsBody* rb, glm::vec3 pos, float radius,
	                               float bounce,
	                               float friction) override;
	    uint32_t addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos,
	                                float radius, float height,
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

		//makes it a trigger
	   // void setIsTrigger(bool ean);
};