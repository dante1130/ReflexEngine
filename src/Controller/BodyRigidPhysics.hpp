#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "Physics.hpp"
#include <glm/glm.hpp>
#include <math.h>

class BodyRigidPhysics {
public:
	/**
	 * @brief	Default constructor. DOES NOTHING
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Nothing
	 * @post	Object created
	 */
	BodyRigidPhysics();

	/**
	 * @brief	Creates rigid body.
	 * @param	pos			- Position of the body
	 * @param	rotation	- axis of rotation of the body
	 * @param	angle		- angle around axis of rotation
	 * @reutrn	Void
	 *
	 * @pre		Physics world exists
	 * @post	Rigid body initialised
	 */
	void init(glm::vec3 pos, glm::vec3 rotation, float angle);

	/**
	 * @brief	Set type of rigid body
	 * @param	type	- type of body. 0 = static, 1 = kinematic, 2 = dynamic
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Type set
	 */
	void setType(int type);

	/**
	 * @brief	Set if you want gravity
	 * @param	val	- True = allow gravity
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Gravity set
	 */
	void enableGravity(bool val);

	/**
	 * @brief	Movement dampining
	 * @param	val	- higher value increaes velocity dampining
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	linear dampining set
	 */
	void setLinearVelocityDamping(float val);

	/**
	 * @brief	Rotation dampining
	 * @param	val	- higher value increaes rotation dampining
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	angular dampining set
	 */
	void setAngularVelocityDamping(float val);

	/**
	 * @brief	Sets if the body can go to sleep
	 * @param	val	- true = body can go to sleep if inactive
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Rigid body can sleep
	 */
	void setIfBodyCanSleep(bool val);

	/**
	 * @brief	Adds force to the object
	 * @param	force	- Force to add
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Force added
	 */
	void addForce(glm::vec3 force);

	/**
	 * @brief	Adds torque to the object
	 * @param	torque	- Torque to add
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Torque added
	 */
	void addTorque(glm::vec3 torque);

	/**
	 * @brief	Gets the position vector
	 * @param	No param
	 * @return	glm::vec3	- The position of the rigid body
	 *
	 * @pre		Rigid body exists
	 * @post	Position retrieved
	 */
	glm::vec3 getPosition();

	/**
	 * @brief	Gets the axis of rotation vector of the rigid body
	 * @param	No param
	 * @return	glm::vec3	- The axis of rotation vector
	 *
	 * @pre		Rigid body exists
	 * @post	Rotation retrieved
	 */
	glm::vec3 getRotation();

	/**
	 * @brief	Gets the angle around the axis of rotation of the rigid body
	 * @param	No param
	 * @return	float	- Angle around axis of rotation
	 *
	 * @pre		Rigid body exists
	 * @post	Angle retrieved
	 */
	float getAngle();

	/**
	 * @brief	Adds a box ciller to a rigid body
	 * @param	pos			- The local position of the collision box
	 * @param	halfSize	- The size of each size if it were halved
	 * @param	bounciness	- The bounciness of the collision box
	 * @param	friction	- The friction of the collision box
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Box collider added
	 */
	void addBoxCollider(glm::vec3 pos, glm::vec3 halfSize, float bounciness,
	                    float friction);

	/**
	 * @brief	Adds a sphere collider to a rigid body
	 * @param	pos			- The local position of the collision box
	 * @param	radius		- The radius of the sphere
	 * @param	bounciness	- The bounciness of the collision box
	 * @param	friction	- The friction of the collision box
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Sphere collider added
	 */
	void addSphereCollider(glm::vec3 pos, float radius, float bounciness,
	                       float friction);

	/**
	 * @brief	Adds a capsule collider to a rigid body
	 * @param	pos			- The local position of the collision box
	 * @param	radius		- The radius of the capsule
	 * @param	height		- The height of the capsule
	 * @param	bounciness	- The bounciness of the collision box
	 * @param	friction	- The friction of the collision box
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Capsule collider added
	 */
	void addCapsuleCollider(glm::vec3 pos, float radius, float height,
	                        float bounciness, float friction);

	/**
	 * NOT CURRENTLY IMPLEMENTED
	 * @brief	Creates a height field shape collision box
	 * @param	pos			- The local position of the collision box
	 * @param	bounciness	- The bounciness of the collision box
	 * @param	friction	- The friction of the collision box
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Height field added
	 */
	void addHeightFieldShape(glm::vec3 pos, float bounciness,
	                         float friction) = delete;

	/**
	 * @brief	Destructor
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Object was created
	 * @post	Object deleted
	 */
	~BodyRigidPhysics();

private:
	/// <summary>
	/// True if created, else false
	/// </summary>
	bool created = false;

	/// <summary>
	/// React rigid body of the object
	/// </summary>
	RigidBody* rb;
};
