#pragma once

#include "Physics.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"


//These are to make it easier to determine where a force
//in the game world is can be applied

/**
 * @author Spencer Shaw
 * @class Apply
 * @brief enum class used for determining the location 
 * of an applied item
 */
enum class Apply {
	LOCAL,
	WORLD
};

/**
 * @author Spencer Shaw
 * @class ApplyPoint
 * @brief enum class used for determining the location
 * of an applied item at a specified point
 */
enum class ApplyPoint {
	LOCAL_LOCAL,
	LOCAL_WORLD,
	WORLD_LOCAL,
	WORLD_WORLD
};
/**
 * @brief typedef of a collision type (CollisionStart, CollisionStay, or CollisionExit) 
 * in a shorter data type name
 */
typedef rp3d::CollisionCallback::ContactPair::EventType CollisionEvent; 

/**
 * @author Spencer Shaw
 * @class PhysicsBody
 * @brief An abstract class to encapusate collision detection and different 
 * methods of collision response
 */
class PhysicsBody
{
	//This is basically what physics object should be, might need to change it up
	
	private:
		/// Global boolean used for all colliders determining if
		/// the object is a trigger
		bool is_trigger = false;

	protected:

		/// Collection of pointers to rigidbodies colliders
	    std::vector<rp3d::Collider*> colliders;

		/*
		*  The body needs three seperate maps as to allow
		*  users to retrieve specified information about the collider
		*  type. A collider holds information as material properties, whether 
		*  the object is a trigger etc. A collider shape, such as BoxShape for
		*  example, holds information such as its extents (how large the box is).
		*/

		/// Collection of pointers to specific collider box types
		std::unordered_map<rp3d::Collider*, rp3d::BoxShape*> m_box;
	    /// Collection of pointers to specific collider sphere types
		std::unordered_map<rp3d::Collider*, rp3d::SphereShape*>  m_sphere;
	    /// Collection of pointers to specific collider capsule types
		std::unordered_map<rp3d::Collider*, rp3d::CapsuleShape*>  m_capsule;

		/// The previous position of the object from last update
	    glm::vec3 previous_transform_position;

		/**
	     * @brief Deletes a specified collider form rigidbody
	     *
	     * @param collider - Pointer to collider for deletion
	     * @return void
	     */
		virtual void deleteCollider(rp3d::Collider* collider) = 0;

	public:

	    /**
	     * @brief Gets the size of the colliders vector
	     *
	     * @return size_t
	     */
		size_t colliderSize();

	    /**
	     * @brief Gets the position of the rigidbody
	     *
	     * @param index - Index of collider
	     * @param type - An enum determining local or world position
	     * @return glm::vec3
	     */
		glm::vec3 getColliderPosition(size_t index, Apply type);

	    /**
	     * @brief Gets the orientation of the rigidbody
	     *
	     * @param index - Index of collider
	     * @param type - An enum determining local or world position
	     * @return glm::vec4
	     */
		glm::vec4 getColliderOrientation(size_t index, Apply type);

		/**
	     * @brief Gets the bounciness property of a
	     * given colliders
	     *
	     * @param index - Index of collider
	     * @return float
	     */
		float getColliderBounce(size_t index);

		/**
	     * @brief Gets the friction property of a
	     * given colliders
	     *
	     * @param index - Index of collider
	     * @return float
	     */
		float getColliderFriction(size_t index);

		/**
	     * @brief Gets the mass density property of a
	     * given colliders
	     *
	     * @param index - Index of collider
	     * @return float
	     */
		float getColliderMassDesity(size_t index);

		/**
	     * @brief Gets the shape of the collider as
	     * an integer value
	     *
	     * @param index - Index of collider
	     * @return int
	     */
		int getColliderType(size_t index);

		/**
	     * @brief Returns a pseduo name containing the
	     * collider type and index of the collider
	     *
	     * @param index - Index of collider
	     * @return std::string
	     */
	    std::string getColliderName(size_t index);

		/**
	     * @brief Returns a index of a collider based
		 * of pointer unless it can not find the collider
	     *
	     * @param collider - Pointer to collider
	     * @return size_t
	     */
	    size_t getColliderIndex(rp3d::Collider* collider);

		/**
	     * @brief Gets all collider pointers inside
	     * colliders
	     *
	     * @return std::vector<rp3d::Collider*>
	     */
		std::vector<rp3d::Collider*> getColliders();

		/**
	     * @brief Returns pointer to box collider
	     * if collider at index is a box type
	     *
	     * @param index - Index of collider
	     * @return rp3d::BoxShape*
	     */
		rp3d::BoxShape* getColliderBox(size_t index);

		/**
	     * @brief Returns pointer to sphere collider
	     * if collider at index is a sphere type
	     *
	     * @param index - Index of collider
	     * @return rp3d::SphereShape*
	     */
		rp3d::SphereShape* getColliderSphere(size_t index);

		/**
	     * @brief Returns pointer to capsule collider
	     * if collider at index is a capsule type
	     *
	     * @param index - Index of collider
	     * @return rp3d::CapsuleShape*
	     */
		rp3d::CapsuleShape* getColliderCapsule(size_t index);

		/**
	     * @brief Sets if the object is a trigger
	     *
	     * @param ean - if the object should be a trigger
	     * @return void
	     */
		void setObjectTrigger(bool ean);

		/**
	     * @brief Adds a material to a collider at
	     * a given index
	     *
	     * @param index - Index of collider
	     * @param bounce - The value of bounciness property
	     * @param mass_density - The value of mass density property
	     * @param friction - The value of friction property
	     * @return void
	     */
		void addMaterialToCollider(size_t index, float bounce, float mass_density, float friction);

		/**
	     * @brief Removes collider at given index
	     *
	     * @param index - Index of collider
	     * @return void
	     */
		void removeCollider(size_t index);

		/**
	     * @brief Remove all colliders in body
	     *
	     * @return void
	     */
		void removeAllColliders();

		/**
	     * @brief Gets the previous position of
	     * the rigidbody
	     *
	     * @return glm::vec3
	     */
		glm::vec3 getPreviousPosition();

		/**
	     * @brief Sets the previous position of
	     * the rigidbody
	     *
	     * @param prev_pos - the previous position
	     * @return void
	     */
	    void setPreviousPosition(glm::vec3 prev_pos);

		/**
	     * @brief Called when a collision between two rigidbodies 
	     * has occured. Finds rigidbodies collision resolution.
		 * 
	     * @param c1 - Pointer to first collider
		 * @param c2 - Pointer to second collider
		 * @param normal - The collision normal
		 * @param c_type - The collision event type
	     * @return void
	     */
		static void collision(rp3d::Collider* c1, rp3d::Collider* c2, 
			rp3d::Vector3 normal, CollisionEvent c_type);

		/**
	     * @brief Calculates collison response and applies it to 
		 * rigidbody
	     *
	     * @param normal - The collision normal
	     * @param c_type - The collision event type
	     * @return void
	     */
		virtual void resolve(glm::vec3 normal, CollisionEvent c_type) = 0;

	    /**
	     * @brief Returns boolean of if the body is using reactphysics3d 
		 * collision resolution or the engines collision resolution
	     *
	     * @return bool
	     */
	    virtual bool usingReactResolve() = 0;

		/**
	     * @brief Applies physics calculations and finds the new
	     * transform properties of the object
	     *
	     * @param delta_time - The delta time
	     * @return void
	     */
	    virtual void update(float delta_time) = 0;

		/**
	     * @brief Intialises rigidbody with axis angle rotation
	     *
	     * @param pos - The desired position
		 * @param rot - The desired axis
		 * @param angle - The desired angle
	     * @return void
	     */
	    virtual void initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) = 0;

	    /**
	     * @brief Intialises rigidbody with euler rotation
	     *
	     * @param pos - The desired position
		 * @param rot - The desired rotation
	     * @return void
	     */
		virtual void initialise_body(glm::vec3 pos, glm::vec3 rot) = 0;

		/**
	     * @brief Removes a the body (CollisionBody/Rigidbody)
	     * of PhysicsBody and its properties
	     *
	     * @return void
	     */
		virtual void delete_body() = 0;
		
		/**
	     * @brief Adds a force to an object's center of mass
	     *
	     * @param force - the size of the force applied
	     * @param type - An enum determining local or world position
	     * @return void
	     */
	    virtual void addForce(glm::vec3 force, Apply type) = 0;

	    /**
	     * @brief Adds a force to an object at a given point
	     *
	     * @param force - the size of the force applied
	     * @param point - position of applied force
	     * @param type - An enum determining relative position to
	     * object
	     * @return void
	     */
	    virtual void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type) = 0;

		/**
	     * @brief Adds torque to an object
	     *
	     * @param force - the size of the torque applied
	     * @param type - An enum determining relative position to
	     * object
	     * @return void
	     */
	    virtual void addTorque(glm::vec3 torque, Apply type) = 0;

		/**
	     * @brief Adds a drag force to an object
	     *
	     * @param drag - the size of the drag force applied
	     * @return void
	     */
		virtual void addDragForce(float drag) = 0;

		/**
	     * @brief Adds a torque drag to an object
	     *
	     * @param ang_drag - the size of the torque drag applied
	     * @return void
	     */
	    virtual void addDragTorque(float ang_drag) = 0;

		/**
	     * @brief Sets the total mass of object
	     *
	     * @param mass - the size of the mass
	     * @return void
	     */
	    virtual void setMass(float mass) = 0;

		/**
	     * @brief Sets the center of mass
	     *
	     * @param p - the desired center of mass
	     * @return void
	     */
	    virtual void setCenterOfMass(glm::vec3 p) = 0;
	    /**
	     * @brief Sets the velocity of object
	     *
	     * @param vel - the desired velocity
	     * @return void
	     */
	    virtual void setVelocity(glm::vec3 vel) = 0;

		/**
	     * @brief Sets the angular velocity of object
	     *
	     * @param ang_vel - the desired angular velocity
	     * @return void
	     */
	    virtual void setAngVelocity(glm::vec3 ang_vel) = 0;

		/**
	     * @brief Sets the linear drag on object
	     *
	     * @param drag - the desired linear drag
	     * @return void
	     */
		virtual void setDragForce(float drag) = 0;

		/**
	     * @brief Sets the angular drag on object
	     *
	     * @param angular_drag - the desired angular drag
	     * @return void
	     */
		virtual void setDragTorque(float ang_drag) = 0;

		/**
	     * @brief Sets the physics type (Static, Kinematic
	     * or Dynamic)
	     *
	     * @param type - the desired physics type
	     * @return void
	     */
		virtual void setType(rp3d::BodyType type) = 0;

		/**
	     * @brief Sets the physics type (Static, Kinematic
	     * or Dynamic)
	     *
	     * @param type - the desired physics type as an integer
	     * @return void
	     */
		virtual void setType(int type) = 0;

		/**
	     * @brief Sets if the object has gravity applied
	     *
	     * @param ean - if the object should have gravity applied
	     * @return void
	     */
	    virtual void enableGravity(bool ean) = 0;

		/**
	     * @brief Sets if the object can sleep
	     *
	     * @param ean - if the object should be able to sleep
	     * @return void
	     */
	    virtual void setCanSleep(bool ean) = 0;

		/**
	     * @brief Gets the total mass of object
	     *
	     * @return float
	     */
	    virtual float getMass() = 0;

	    /**
	     * @brief Gets the velocity of object
	     *
	     * @return glm::vec3
	     */
	    virtual glm::vec3 getVelocity() = 0;

		/**
	     * @brief Gets the angular of object
	     *
	     * @return glm::vec3
	     */
	    virtual glm::vec3 getAngVelocity() = 0;
	    
		/**
	     * @brief Gets the linear drag of object
	     *
	     * @return float
	     */
	    virtual float getDragForce() = 0;

		/**
	     * @brief Gets the angular drag of object
	     *
	     * @return float
	     */
	    virtual float getDragTorque() = 0;

		/**
	     * @brief Gets the object type as an integer
	     *
	     * @return int
	     */
		virtual rp3d::BodyType getType() = 0;

		/**
	     * @brief Gets if the object has gravity applied
	     *
	     * @return bool
	     */
	    virtual bool getIsGravityEnabled() = 0;

		/**
	     * @brief Gets if the object can sleep
	     *
	     * @return bool
	     */
	    virtual bool getCanSleep() = 0;

		/**
	     * @brief Gets if the object is a trigger
	     *
	     * @return bool
	     */
		bool getIsTrigger();

		/**
	     * @brief Creates and adds a box collider to object
	     * with no material properties
		 * 
	     * @param pos - the desired position
	     * @param size - the desired half extents
	     * @return uint32_t
	     */
	    virtual uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size) = 0;

		/**
	     * @brief Creates and adds a sphere collider to object
	     * with no material properties
	     *
	     * @param pos - the desired position
	     * @param radius - the desired radius
	     * @return uint32_t
	     */
	    virtual uint32_t addSphereCollider(glm::vec3 pos, float radius) = 0;

		/**
	     * @brief Creates and adds a capsule collider to object
	     * with no material properties
	     *
	     * @param pos - the desired position
	     * @param radius - the desired radius
		 * @param height - the desired height
	     * @return uint32_t
	     */
	    virtual uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height) = 0;

		/**
	     * @brief Creates and adds a box collider to object
	     * and links the rigidbody data to it
		 * 
		 * @param rb - pointer to physicsbody for linking
	     * @param pos - the desired position
	     * @param size - the desired half extents
	     * @param bounce - the bounciness property
	     * @param friction - the friction property
	     * @return uint32_t
	     */
		virtual uint32_t addBoxCollider(PhysicsBody* rb, glm::vec3 pos, glm::vec3 size, float bounce, float friction) = 0;

		/**
	     * @brief Creates and adds a sphere collider to object
	     * and links the rigidbody data to it
		 * 
		 * @param rb - pointer to physicsbody for linking
	     * @param pos - the desired position
	     * @param radius - the desired radius
	     * @param bounce - the bounciness property
	     * @param friction - the friction property
	     * @return uint32_t
	     */
	    virtual uint32_t addSphereCollider(PhysicsBody* rb, glm::vec3 pos,
	                                       float radius,
	                                       float bounce, float friction) = 0;

		/**
	     * @brief Creates and adds a capsule collider to object
	     * and links the rigidbody data to it
		 * 
		 * @param rb - pointer to physicsbody for linking
	     * @param pos - the desired position
	     * @param radius - the desired radius
	     * @param height - the desired height
	     * @param bounce - the bounciness property
	     * @param friction - the friction property
	     * @return uint32_t
	     */
	    virtual uint32_t addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos,
	                                        float radius,
	                                        float height, float bounce,
	                                        float friction) = 0;

		/**
	     * @brief Creates and adds a box collider to object
	     *
	     * @param pos - the desired position
	     * @param size - the desired half extents
	     * @param bounce - the bounciness property
	     * @param friction - the friction property
	     * @return uint32_t
	     */
	    virtual uint32_t addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) = 0;

		/**
	     * @brief Creates and adds a sphere collider to object
	     *
	     * @param pos - the desired position
	     * @param radius - the desired radius
	     * @param bounce - the bounciness property
	     * @param friction - the friction property
	     * @return uint32_t
	     */
		virtual uint32_t addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction) = 0;

		/**
	     * @brief Creates and adds a capsule collider to object
	     *
	     * @param pos - the desired position
	     * @param radius - the desired radius
	     * @param height - the desired height
	     * @param bounce - the bounciness property
	     * @param friction - the friction property
	     * @return uint32_t
	     */
		virtual uint32_t addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction) = 0;

		/**
	     * @brief Gets the position of the rigidbody
	     *
	     * @return glm::vec3
	     */
	    virtual glm::vec3 getPosition() = 0;

		/**
	     * @brief Gets the euler rotation of the
	     * rigidbody
	     *
	     * @return glm::vec3
	     */
	    virtual glm::vec3 getRotation() = 0;

		/**
	     * @brief Gets the quanterion orientation of
	     * the rigidbody
	     *
	     * @return glm::vec3
	     */
		virtual glm::quat getOrientation() = 0;

		/**
	     * @brief Gets the w component of quanternion
	     *
	     * @return glm::vec3
	     */
		virtual float getAngle() = 0;

		/**
	     * @brief Sets the position of the rigidbody
	     *
	     * @param pos - the desired position
	     * @return void
	     */
		virtual void setPosition(glm::vec3 pos) = 0;

		/**
	     * @brief Sets the quanterion orientation of
	     * the rigidbody
	     *
	     * @param quat - the desired orientation
	     * @return void
	     */
		virtual void setQuaternion(glm::quat quat) = 0;

		/**
	     * @brief Sets the euler rotation of
	     * the rigidbody
	     *
	     * @param rot - the desired rotation
	     * @return void
	     */
		virtual void setEulerRotation(glm::vec3 rot) = 0;

		/**
	     * @brief Sets the x, y, z components of
	     * the qunaternion
	     *
	     * @param rot - the desired x, y, z
	     * @return void
	     */
		virtual void setRotation(glm::vec3 rot) = 0;

		/**
	     * @brief Sets the w component of quanternion
	     *
		 * @param ang - the desired w
	     * @return void
	     */
		virtual void setAngle(float ang) = 0;
};