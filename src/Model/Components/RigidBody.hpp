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

		Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot)
		{
			if (usingReact)
				pb = new ReactResolve();
			else
				pb = new EngineResolve();

			pb->initialise_body(pos, rot);

		}

		Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot, bool gravity_on, bool can_sleep,
			bool is_trigger, float linear_drag, float angular_drag){

			if (usingReact)
				pb = new ReactResolve();
			else
				pb = new EngineResolve();

			pb->initialise_body(pos, rot);

			pb->enableGravity(gravity_on);
			pb->setCanSleep(can_sleep);
			pb->setObjectTrigger(is_trigger);
			pb->setDragForce(linear_drag);
			pb->setDragTorque(angular_drag);

		}

		void init(bool usingReact, glm::vec3 pos, glm::vec3 rot)
		{
			if (usingReact)
				pb = new ReactResolve();
			else
				pb = new EngineResolve();

			pb->initialise_body(pos, rot);
		}

		void setTransform(glm::vec3 pos, glm::vec3 rot)
		{
			pb->setPosition(pos);
			pb->setEulerRotation(rot);
		}

		void setViewables(bool gravity_on, bool can_sleep,
			bool is_trigger, float linear_drag, float angular_drag)
		{
			pb->enableGravity(gravity_on);
			pb->setCanSleep(can_sleep);
			pb->setObjectTrigger(is_trigger);
			pb->setDragForce(linear_drag);
			pb->setDragTorque(angular_drag);
		}

	//****************************
	// FUNCTIONS FOR PHYSICS STUFF
	//****************************

		// Using react
		bool usingReactResolve() { return pb->usingReactResolve(); }


		// Colliders

		int colliderSize() { return pb->colliderSize(); }

		glm::vec3 getColliderPosition(int index, Apply type) { return pb->getColliderPosition(index, type); }

		float getColliderBounce(int index) { return pb->getColliderBounce(index); }

		float getColliderFriction(int index) { return pb->getColliderFriction(index); }

		float getColliderMassDesity(int index) { return pb->getColliderMassDesity(index); }

		int getColliderType(int index) { return pb->getColliderType(index); }

		const rp3d::BoxShape* getColliderBox(int index) { return pb->getColliderBox(index); }

		const rp3d::SphereShape* getColliderSphere(int index) { return pb->getColliderSphere(index); }

		const rp3d::CapsuleShape* getColliderCapsule(int index) { return pb->getColliderCapsule(index); }

		void addMaterialToCollider(int index, float bounce, float mass_density, float friction)
		{
			return pb->addMaterialToCollider(index, bounce, mass_density, friction);
		}

		void removeAllColliders() { pb->removeAllColliders(); }

		void removeCollider(int index) { pb->removeCollider(index); }


		// Gui viewable variables methods

		void setObjectTrigger(bool ean) { 
			pb->setObjectTrigger(ean);
			is_trigger = ean; 
		}

		void enableGravity(bool ean) {
			pb->enableGravity(ean); 
			gravity_on = ean;
		}

		void setCanSleep(bool ean) { 
			pb->setCanSleep(ean); 
			can_sleep = ean;
		}

		bool getIsGravityEnabled() { return pb->getIsGravityEnabled(); }

		bool getCanSleep() { return pb->getCanSleep(); }

		bool getIsTrigger() { return pb->getIsTrigger(); }


		// Applying interaction methods

		void addForce(glm::vec3 force, Apply type) { 
			pb->addForce(force, type); }

		void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type)
		{
			pb->addForceAtPoint(force, point, type);
		}

		void addTorque(glm::vec3 torque, Apply type) { pb->addTorque(torque, type); }

		void addDragForce(float drag) { 
			pb->addDragForce(drag); 
			lin_drag = pb->getDragForce();
		}

		void addDragTorque(float ang_drag) { 
			pb->addDragTorque(ang_drag); 
			ang_drag = pb->getDragTorque();
		}


		// Set methods

		void setMass(float mass) { pb->setMass(mass); }

		void setCenterOfMass(glm::vec3 p) { pb->setCenterOfMass(p); }

		void setVelocity(glm::vec3 vel) {
			pb->setVelocity(vel);
		}

		void setAngVelocity(glm::vec3 ang_vel) { pb->setAngVelocity(ang_vel); }

		void setDragForce(float drag) { 
			pb->setDragForce(drag);
			lin_drag = drag;
		}

		void setDragTorque(float angular_drag) { 
			pb->setDragTorque(angular_drag); 
			ang_drag = angular_drag;
		}

		void setType(rp3d::BodyType type) { pb->setType(type); }

		void setType(int type) { pb->setType(type); }


		// Get methods

		float getMass() { return pb->getMass(); }

		glm::vec3 getVelocity() { return pb->getVelocity(); }

		glm::vec3 getAngVelocity() { return pb->getAngVelocity(); }

		float getDragForce() { return pb->getDragForce(); }

		float getDragTorque() { return pb->getDragTorque(); }

		rp3d::BodyType getType() { return pb->getType(); }


		// Collider methods

		//void addBoxCollider(glm::vec3 pos, glm::vec3 size) { pb->addBoxCollider(pos, size); }

		//void addSphereCollider(glm::vec3 pos, float radius) { pb->addSphereCollider(pos, radius); }

		//void addCapsuleCollider(glm::vec3 pos, float radius, float height) { pb->addCapsuleCollider(pos, radius, height); }

		uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) {
			return pb->addBoxCollider(pos, size, bounce, friction);
		}
		uint32_t addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
		{
			return pb->addSphereCollider(pos, radius, bounce, friction);
		}
		uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
		{
			return pb->addCapsuleCollider(pos, radius, height, bounce, friction);
		}
		

		// Methods used for transform

		glm::vec3 getPosition() { return pb->getPosition(); }

		glm::vec3 getRotation() { return pb->getRotation(); }

		glm::quat getOrientation() { return pb->getOrientation(); }

		void setPosition(glm::vec3 pos) { pb->setPosition(pos); }

		void setQuanternion(glm::quat quat) { pb->setQuaternion(quat); }

		void setEulerRotation(glm::vec3 rot) { pb->setEulerRotation(rot); }

	};
};