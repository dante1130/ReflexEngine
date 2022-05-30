#pragma once
#include "Controller/Physics/BodyRigidPhysics.hpp"
#include "Body.hpp"
#include <glm/glm.hpp>
#include <vector>

class BodyRigid : public Body {
public:
	/**
	 * @brief	Basic initialiser for engine to call. Does nothing
	 *
	 * @pre	Nothing
	 * @post	Nothing
	 */
	void init() override;

	/**
	 * @brief	Draw call for engine to call. Does nothing
	 *
	 * @pre		Nothing
	 * @post	Nothing
	 */
	void add_draw_call() override {}

	/**
	 * @brief	Draws object. Does nothing
	 *
	 * @pre		Nothing
	 * @post	Nothing
	 */
	void draw(std::shared_ptr<Shader> shader) override {}

	/**
	 * @brief	Creates rigid body.
	 * @param	pos			- Position of the body
	 * @param	rotation	- axis of rotation of the body
	 * @param	angle		- angle around axis of rotation
	 *
	 * @pre		Physics world exists
	 * @post	Rigid body initialised
	 */
	void createBR(glm::vec3 pos, glm::vec3 rotation, float angle);

	/**
	 * @brief	Sets the position of the rigid body
	 * @param	pos	- The position of the rigid body
	 *
	 * @pre		Rigid body exists
	 * @post		Rigid body updated
	 */
	void set_position(glm::vec3 pos);

	/**
	 * @brief	Set type of rigid body
	 * @param	type	- type of body. 0 = static, 1 = kinematic, 2 = dynamic
	 *
	 * @pre		Rigid body exists
	 * @post	Type set
	 */
	void setType(int type);

	/**
	 * @brief	Gets the type of rigid body
	 * @return	type	- type of body. 0 = static, 1 = kinematic, 2 = dynamic
	 *
	 * @pre		Rigid body exists
	 * @post	Type returned
	 */
	int getType();

	/**
	 * @brief	Set if you want gravity
	 * @param	val	- True = allow gravity
	 *
	 * @pre		Rigid body exists
	 * @post	Gravity set
	 */
	void enableGravity(bool val);

	/**
	 * @brief	Movement dampining
	 * @param	val	- higher value increaes velocity dampining
	 *
	 * @pre		Rigid body exists
	 * @post	linear dampining set
	 */
	void setLinearVelocityDamping(float val);

	/**
	 * @brief	Rotation dampining
	 * @param	val	- higher value increaes rotation dampining
	 *
	 * @pre		Rigid body exists
	 * @post	angular dampining set
	 */
	void setAngularVelocityDamping(float val);

	/**
	 * @brief	Sets if the body can go to sleep
	 * @param	val	- true = body can go to sleep if inactive
	 *
	 * @pre		Rigid body exists
	 * @post	Rigid body can sleep
	 */
	void setIfBodyCanSleep(bool val);

	/**
	 * @brief	Adds force to the object
	 * @param	force	- Force to add
	 *
	 * @pre		Rigid body exists
	 * @post	Force added
	 */
	void addForce(glm::vec3 force);

	/**
	 * @brief	set force to the object
	 * @param	velocity	- velocity to set
	 *
	 * @pre		Rigid body exists
	 * @post	Force added
	 */
	void setLinearVelocity(glm::vec3 velocity);

	/**
	 * @brief	Adds torque to the object
	 * @param	torque	- Torque to add
	 *
	 * @pre		Rigid body exists
	 * @post	Torque added
	 */
	void addTorque(glm::vec3 torque);

	/**
	 * @brief	set torque to the object
	 * @param	velocity	- velocity to set
	 *
	 * @pre		Rigid body exists
	 * @post	Torque added
	 */
	void setAngularVelocity(glm::vec3 velocity);

	/**
	 * @brief	Updates the object
	 * @param	delta_time	- Time between last frame
	 *
	 * @pre		Rigid body exists
	 * @post	Rigid body updated
	 */
	void update(double delta_time) override;

	/**
	 * @brief Updates the body object with fixed delta time.
	 *
	 * @param delta_time
	 */
	void fixed_update(double delta_time) override;

	/**
	 * @brief	Gets the position vector
	 * @return	glm::vec3	- The position of the rigid body
	 *
	 * @pre		Rigid body exists
	 * @post	Position retrieved
	 */
	glm::vec3 getPosition();

	/**
	 * @brief	Gets the axis of rotation vector of the rigid body
	 * @return	glm::vec3	- The axis of rotation vector
	 *
	 * @pre		Rigid body exists
	 * @post	Rotation retrieved
	 */
	glm::vec3 getRotation();

	/**
	 * @brief	Gets the angle around the axis of rotation of the rigid body
	 * @return	float	- Angle around axis of rotation
	 *
	 * @pre		Rigid body exists
	 * @post	Angle retrieved
	 */
	float getAngle();

	/**
	 * @brief	Gets the linear velocity of the rigid body
	 * @return	glm::vec3	- linear velocity
	 *
	 * @pre		Rigid body exists
	 * @post	linear velocity retrieved
	 */
	glm::vec3 getLinearVelocity();

	/**
	 * @brief	Gets the angular velocity of the rigid body
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
	 *
	 * @pre		Rigid body exists
	 * @post	Capsule collider added
	 */
	void addCapsuleCollider(glm::vec3 pos, float radius, float height,
	                        float bounciness, float friction);

	/**
	 * NOT CURRENTLY IMPLEMENTED
	 * @brief	Creates a height field shape collision box
	 * @param	bounciness	- The bounciness of the collision box
	 * @param	friction	- The friction of the collision box
	 *
	 * @pre		Rigid body exists
	 * @post	Height field added
	 */
	void addHeightFieldShape(float bounciness, float friction) = delete;

	/**
	 * @brief	Changes the linear axis factor. I.e. if set a axis to 0 it will
	 * no longer move on that axis.
	 * @param	factor	- The factor you want for each axis. i.e. 1, 0, 1, stops
	 * y movement.
	 *
	 * @pre		Rigid body exists
	 * @post	Linear axis factor changed
	 */
	void setLinearAxisFactor(glm::vec3 factor);

	/**
	 * @brief	Changes the angular axis factor. I.e. if set a axis to 0 it will
	 * no longer rotate on that axis.
	 * @param	factor	- The factor you want for each axis. i.e. 1, 0, 1, stops
	 * y rotation.
	 *
	 * @pre		Rigid body exists
	 * @post	Angular axis factor changed
	 */
	void setAngularAxisFactor(glm::vec3 factor);

	/**
	 * @brief	Destructor
	 *
	 * @pre	Object was created
	 * @post	Object deleted
	 */
	~BodyRigid();

	/**
	 * @brief	Saves the object to lau file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override {}

	std::vector<colliderData_capsule> getCapsuleColliders();

protected:
	/// <summary>
	/// Facaded react rigid body
	/// </summary>
	BodyRigidPhysics rb;

	/// <summary>
	/// The number of colliders in the rb
	/// </summary>
	int m_numOfColliders = 0;

	/// <summary>
	/// List of sphere colliders. Used for storing data to file
	/// </summary>
	std::vector<colliderData_sphere> m_sphere;

	/// <summary>
	/// List of capsule colliders. Used for storing data to file
	/// </summary>
	std::vector<colliderData_capsule> m_capsule;

	/// <summary>
	/// List of capsule colliders. Used for storing data to file
	/// </summary>
	std::vector<colliderData_box> m_box;
};
