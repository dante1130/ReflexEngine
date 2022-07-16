#pragma once

#include "Controller/Physics/Physics.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"
#include "Controller/Physics/PhysicBody.hpp"
#include "Controller/Physics/EngineResolve.hpp"
#include "Controller/Physics/ReactResolve.hpp"
#include "View/Renderer/OpenGL/Objects/Model.hpp"
#include "View/Renderer/OpenGL/Objects/Material.hpp"

class PhysicsObject : public GameObject{
public:
	void init();
	/**
	 * @brief	Default constructor for physics object
	 *
	 * @pre	Nothing
	 * @post	Object created
	 */
	PhysicsObject() = default;

	/**
	 * @brief	Initialised the model
	 * @param	model_name		name of model
	 * @param	material_name	name of material
	 *
	 * @pre		Object exists
	 * @post	model initialised
	 */
	void initModel(const std::string& model_name,
	               const std::string& material_name);

	/**
	 * @brief	Initialised the rigid body
	 * @param	pos			- position of the rigid body
	 * @param	rotation	- axis of rotation of the rigid body
	 * @param	angle		- Rotation around axis of rotation of rigid body
	 *
	 * @pre		Object exists
	 * @post	rigid body initialised
	 */
	void initRB(glm::vec3 pos, glm::vec3 rotation, float angle);

	/**
	 * @brief	Initialised the rigid body
	 * @param	pos			- position of the rigid body
	 * @param	rotation	- axis of rotation of the rigid body
	 * @param	angle		- Rotation around axis of rotation of rigid body
	 * @param   type		- Uses engine collision resolution or react3D's
	 * @pre		Object exists
	 * @post	rigid body initialised
	 */
	void initRB(glm::vec3 pos, glm::vec3 rotation, float angle, bool type);

	/**
	 * @brief	Updates the object
	 * @param	delta_time	- Time since last frame
	 *
	 * @pre		rigid body initialised
	 * @post	Object updated
	 */
	void update(double delta_time) override;

	/**
	 * @brief Updates the body object with fixed delta time.
	 *
	 * @param delta_time
	 */
	void fixed_update(double delta_time) override;

	/**
	 * @brief	Adds draw call of object
	 *
	 * @pre		Model initialised
	 * @post	Draw call added
	 */
	void add_draw_call() override;

	/**
	 * @brief	Draws the object
	 * @param	shader	- The shader
	 *
	 * @pre		Model initialised
	 * @post	Model drawn
	 */
	void draw(const Shader& shader) override;

	/**
	 * @brief	Saves the object to lau file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

	/**
	 * @brief	default destructor
	 */
	~PhysicsObject() = default;

	//****************************
	// FUNCTIONS FOR PHYSICS STUFF
	//****************************

	int colliderSize();
	glm::vec3 getColliderPosition(int index, Apply type);
	glm::vec4 getColliderOrientation(int index, Apply type);

	float getColliderBounce(int index);
	float getColliderFriction(int index);
	float getColliderMassDesity(int index);

	int getColliderType(int index);

	const BoxShape* getColliderBox(int index);
	const SphereShape* getColliderSphere(int index);
	const CapsuleShape* getColliderCapsule(int index);

	void addMaterialToCollider(int index, float bounce, float mass_density, float friction);

	void removeAllColliders();

	void setObjectTrigger(bool ean);

	bool usingReactResolve();

	void init(glm::vec3 rot, glm::vec3 pos, float angle);

	void addForce(glm::vec3 force, Apply type);
	void addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type);
	void addTorque(glm::vec3 torque, Apply type);

	void addDragForce(float drag);
	void addDragTorque(float ang_drag);

	void setMass(float mass);
	void setCenterOfMass(glm::vec3 p);
	void setVelocity(glm::vec3 vel);
	void setAngVelocity(glm::vec3 ang_vel);

	void setType(BodyType type);
	void setType(int type);
	void enableGravity(bool ean);
	void setCanSleep(bool ean);

	float getMass();
	glm::vec3 getVelocity();
	glm::vec3 getAngVelocity();
	float getDragForce();
	float getDragTorque();

	BodyType getType();
	bool getIsGravityEnabled();
	bool getCanSleep();

	void addBoxCollider(glm::vec3 pos, glm::vec3 size);
	void addSphereCollider(glm::vec3 pos, float radius);
	void addCapsuleCollider(glm::vec3 pos, float radius, float height);

	void addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction);
	void addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction);
	void addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	float getAngle();

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
	void setAngle(float ang);

protected:
	/// The model of the item.
	std::string model_name_;
	/// The material of the item.
	std::string material_name_;

	//physics stuff
	PhysicsBody* pb; 


	/**
	 * @brief	Saves the sphere collider of rb
	 * @param	index	- Which collider to save
	 *
	 * @pre		Collider exists
	 * @post	Collider stored
	 */
	void saveSphereCollider(size_t index);

	/**
	 * @brief	Saves the capsule collider of rb
	 * @param	index	- Which collider to save
	 *
	 * @pre		Collider exists
	 * @post	Collider stored
	 */
	void saveCapsuleCollider(size_t index);

	/**
	 * @brief	Saves the box collider of rb
	 * @param	index	- Which collider to save
	 *
	 * @pre		Collider exists
	 * @post	Collider stored
	 */
	void saveBoxCollider(size_t index);
	/**
	 * @brief	Saves the collider of rb
	 * @param	index	- Which collider to save
	 * @param	type	- The type of collider
	 *
	 * @pre		Collider exists
	 * @post	Collider stored
	 */
	void saveCollider(size_t index, int type);
};
