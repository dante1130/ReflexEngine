#pragma once

#include "Physics.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"


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
	
	private:
		bool is_trigger = false;


	protected:
	    std::vector<rp3d::Collider*> colliders;

		/*
		*  The body needs three seperate maps as to allow
		*  users to retrieve specified information about the collider
		*  type. A collider holds information as material properties, whether 
		*  the object is a trigger etc. A collider shape, such as BoxShape for
		*  example, holds information such as its extents (how large the box is).
		*/

		std::unordered_map<rp3d::Collider*, rp3d::BoxShape*> m_box;
		std::unordered_map<rp3d::Collider*, rp3d::SphereShape*>  m_sphere;
		std::unordered_map<rp3d::Collider*, rp3d::CapsuleShape*>  m_capsule;

		/// The previous position of the object
	    /// last update
	    glm::vec3 previous_transform_position;

		virtual void deleteCollider(rp3d::Collider* collider) = 0;

	public:

		//collider access
		size_t colliderSize();
		glm::vec3 getColliderPosition(size_t index, Apply type);
		glm::vec4 getColliderOrientation(size_t index, Apply type);

		float getColliderBounce(size_t index);
		float getColliderFriction(size_t index);
		float getColliderMassDesity(size_t index);
		int getColliderType(size_t index);
	    std::string getColliderName(size_t index);
	    size_t getColliderIndex(rp3d::Collider* collider);

		std::vector<rp3d::Collider*> getColliders();

		rp3d::BoxShape* getColliderBox(size_t index);
		rp3d::SphereShape* getColliderSphere(size_t index);
		rp3d::CapsuleShape* getColliderCapsule(size_t index);

		void setObjectTrigger(bool ean);


		void addMaterialToCollider(size_t index, float bounce, float mass_density, float friction);

		void removeCollider(size_t index);
		void removeAllColliders();

		// Temporary for simple collision response
		glm::vec3 getPreviousPosition();
	    void setPreviousPosition(glm::vec3 prev_pos);

		// collision resolution

		static void collision(rp3d::Collider* c1, rp3d::Collider* c2, 
			rp3d::CollisionCallback::ContactPair::EventType c_type);

		virtual void stop(rp3d::CollisionCallback::ContactPair::EventType c_type) = 0;

	    // collision resolution system type check
	    virtual bool usingReactResolve() = 0;

		// Update function
	    virtual void update(float delta_time) = 0;

		//init setup
	    virtual void initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) = 0;
		virtual void initialise_body(glm::vec3 pos, glm::vec3 rot) = 0;

		virtual void delete_body() = 0;

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
		virtual void setDragForce(float drag) = 0;
		virtual void setDragTorque(float ang_drag) = 0;

		virtual void setType(rp3d::BodyType type) = 0;
		virtual void setType(int type) = 0;
	    virtual void enableGravity(bool ean) = 0;
	    virtual void setCanSleep(bool ean) = 0;

		//Get properties
	    virtual float getMass() = 0;
	    virtual glm::vec3 getVelocity() = 0;
	    virtual glm::vec3 getAngVelocity() = 0;
	    
	    virtual float getDragForce() = 0;
	    virtual float getDragTorque() = 0;

		virtual rp3d::BodyType getType() = 0;
	    virtual bool getIsGravityEnabled() = 0;
	    virtual bool getCanSleep() = 0;
		bool getIsTrigger();

		//Add colliders
	    virtual uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size) = 0;
	    virtual uint32_t addSphereCollider(glm::vec3 pos, float radius) = 0;
	    virtual uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height) = 0;


		virtual uint32_t addBoxCollider(PhysicsBody* rb, glm::vec3 pos, glm::vec3 size, float bounce, float friction) = 0;
	    virtual uint32_t addSphereCollider(PhysicsBody* rb, glm::vec3 pos,
	                                       float radius,
	                                       float bounce, float friction) = 0;
	    virtual uint32_t addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos,
	                                        float radius,
	                                        float height, float bounce,
	                                        float friction) = 0;

	    virtual uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) = 0;
		virtual uint32_t addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction) = 0;
		virtual uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction) = 0;

		//returns for GameObject position and rotation
	    virtual glm::vec3 getPosition() = 0;
	    virtual glm::vec3 getRotation() = 0;
		virtual glm::quat getOrientation() = 0;
		virtual float getAngle() = 0;

		virtual void setPosition(glm::vec3 pos) = 0;
		virtual void setQuaternion(glm::quat quat) = 0;
		virtual void setEulerRotation(glm::vec3 rot) = 0;
		virtual void setRotation(glm::vec3 rot) = 0;
		virtual void setAngle(float ang) = 0;
};