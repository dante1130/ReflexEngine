#pragma once

#include "Controller/Physics/PhysicBody.hpp"
#include "Controller/Physics/ReactResolve.hpp"
#include "Controller/Physics/EngineResolve.hpp"

#include "glm/vec3.hpp"

namespace Component {

	struct Rigidbody {

	private:

		//Physics system
		PhysicsBody* pb;
		
	public:

		bool gravity_on;
		bool can_sleep;
		bool is_trigger;

		float lin_drag;
		float ang_drag;

		Rigidbody() = default;

		Rigidbody(const Rigidbody&) = default;

		Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot);

		Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot, bool gravity_on, bool can_sleep,
			bool is_trigger, float linear_drag, float angular_drag);

		void init(bool usingReact, glm::vec3 pos, glm::vec3 rot);

		void setTransform(glm::vec3 pos, glm::vec3 rot);

		void setViewables(bool gravity_on, bool can_sleep,
			bool is_trigger, float linear_drag, float angular_drag);

	//****************************
	// FUNCTIONS FOR PHYSICS STUFF
	//****************************

		// Using react
		bool usingReactResolve();


		// Colliders

		size_t colliderSize();

		glm::vec3 getColliderPosition(size_t index, Apply type);

		float getColliderBounce(size_t index);

		float getColliderFriction(size_t index);

		float getColliderMassDesity(size_t index);

		int getColliderType(size_t index);

		const rp3d::BoxShape* getColliderBox(size_t index);

		const rp3d::SphereShape* getColliderSphere(size_t index);

		const rp3d::CapsuleShape* getColliderCapsule(size_t index);

		void addMaterialToCollider(size_t index, float bounce, float mass_density, float friction);

		void removeAllColliders();

		void removeCollider(size_t index);


		// Gui viewable variables methods

		void setObjectTrigger(bool ean);

		void enableGravity(bool ean);

		void setCanSleep(bool ean);

		bool getIsGravityEnabled();

		bool getCanSleep();

		bool getIsTrigger();


		// Applying interaction methods

		void addForce(glm::vec3 force, Apply type);

		void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type);

		void addTorque(glm::vec3 torque, Apply type);

		void addDragForce(float drag);

		void addDragTorque(float ang_drag);


		// Set methods

		void setMass(float mass);

		void setCenterOfMass(glm::vec3 p);

		void setVelocity(glm::vec3 vel);

		void setAngVelocity(glm::vec3 ang_vel);

		void setDragForce(float drag);

		void setDragTorque(float angular_drag);

		void setType(rp3d::BodyType type);

		void setType(int type);


		// Get methods

		float getMass();

		glm::vec3 getVelocity();

		glm::vec3 getAngVelocity();

		float getDragForce();

		float getDragTorque();

		rp3d::BodyType getType();


		// Collider methods

		//void addBoxCollider(glm::vec3 pos, glm::vec3 size) { pb->addBoxCollider(pos, size); }

		//void addSphereCollider(glm::vec3 pos, float radius) { pb->addSphereCollider(pos, radius); }

		//void addCapsuleCollider(glm::vec3 pos, float radius, float height) { pb->addCapsuleCollider(pos, radius, height); }

		uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction);

		uint32_t addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction);

		uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction);


		// Methods used for transform

		glm::vec3 getPosition();

		glm::vec3 getRotation();

		glm::quat getOrientation();

		void setPosition(glm::vec3 pos);
			
		void setQuanternion(glm::quat quat);

		void setEulerRotation(glm::vec3 rot);

	};
};