#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "Physics.hpp"
#include <glm/glm.hpp>
#include <math.h>

struct colliderData {
	int m_colliderStored = 0;
};

struct colliderData_sphere : public colliderData {
	float m_radius = 0;

	colliderData_sphere(int num, float rad) {
		m_colliderStored = num;
		m_radius = rad;
	}
};

struct colliderData_capsule : public colliderData {
	float m_radius = 0;
	float m_height = 0;

	colliderData_capsule(int num, float rad, float hei) {
		m_colliderStored = num;
		m_radius = rad;
		m_height = hei;
	}
};

struct colliderData_box : public colliderData {
	glm::vec3 m_size = {};

	colliderData_box(int num, float x, float y, float z) {
		m_colliderStored = num;
		m_size.x = x;
		m_size.y = y;
		m_size.z = z;
	}
};

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
	 * @brief	set force to the object
	 * @param	velocity	- velocity to set
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Force added
	 */
	void setLinearVelocity(glm::vec3 velocity);

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
	 * @brief	set torque to the object
	 * @param	velocity	- velocity to set
	 * @return	Void
	 *
	 * @pre		Rigid body exists
	 * @post	Torque added
	 */
	void setAngularVelocity(glm::vec3 velocity);

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
	 * @brief	Gets the linear velocity of the rigid body
	 * @param	No param
	 * @return	glm::vec3	- linear velocity
	 *
	 * @pre		Rigid body exists
	 * @post	linear velocity retrieved
	 */
	glm::vec3 getLinearVelocity();

	/**
	 * @brief	Gets the angular velocity of the rigid body
	 * @param	No param
	 * @return	glm::vec3	- angular velocity
	 *
	 * @pre		Rigid body exists
	 * @post	angular velocity retrieved
	 */
	glm::vec3 getAngularVelocity();

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
	 * @brief	Gets if gravity is allowed in the rb (rigid body)
	 * @param	No param
	 * @return	bool	- True if gravity is allowed on rb
	 *
	 * @pre		rb exists
	 * @post	if gravity allowed retrieved
	 */
	bool getIfGravityActive();

	/**
	 * @brief	Retrieves the rigid body type
	 * @param	No param
	 * @return	int	- The type of rigid body
	 *
	 * @pre		rb exists
	 * @post	rigid body type retrieved
	 */
	int getRBType();

	/**
	 * @brief	Gets the number of colliders attached to the rigid body
	 * @param	No param
	 * @return	int	- Number of colliders
	 *
	 * @pre		rb & colliders exist
	 * @post	Collider number retrieved
	 */
	int getNumberOfColliders();

	/**
	 * @brief	Gets the linear damping value of the object
	 * @param	No param
	 * @return	float	- the linear damping value
	 *
	 * @pre		rb exists
	 * @post	linear damping retrieved
	 */
	float getLinearDamping();

	/**
	 * @brief	Gets the angular damping value of the object
	 * @param	No param
	 * @return	float	- The angular damping value
	 *
	 * @pre		rb exists
	 * @post	angular damping retrieved
	 */
	float getAngularDamping();

	/**
	 * @brief	Gets it the object can go to sleep (performce improvement)
	 * @param	No param
	 * @return	bool	- true if object can go to sleep
	 *
	 * @pre		rb exists
	 * @post	allowed to sleep retrieved
	 */
	bool getIfAllowedSleep();

	/**
	 * @brief	Gets the type of collider (sphere, box, capsule)
	 * @param	index	- The index of the collider in question
	 * @return	int		- the colliders type
	 *
	 * @pre		collider & rb exist
	 * @post	collider type retrieved
	 */
	int getColliderType(int index);

	/**
	 * @brief	Gets a collders bounciness value
	 * @param	index	- The index of the collider in question
	 * @return	float	- The bounciness of the collider
	 *
	 * @pre		collider & rb exist
	 * @post	collider bounciness retrieved
	 */
	float getBounciness(int index);

	/**
	 * @brief	Gets a colliders friction value
	 * @param	index	- The index of the collider in question
	 * @return	float	- The friction of the collider
	 *
	 * @pre		collider & rb exist
	 * @post	Friction value returned
	 */
	float getFriction(int index);

	/**
	 * @brief	Gets the local position of the collider attached to the rb
	 * @param	index		- The index of the collider in question
	 * @return	glm::vec3	- The position of the collider in relation to the rb
	 *
	 * @pre		Collider & rb exist
	 * @post	Local coordinates returned
	 */
	glm::vec3 getLocalColliderPos(int index);

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
