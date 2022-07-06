#pragma once

#include "BodyRigid.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"
#include "Controller/Physics/PhysicResolution.hpp"
#include "View/Renderer/OpenGL/Objects/Model.hpp"
#include "View/Renderer/OpenGL/Objects/Material.hpp"

class PhysicsObject : public GameObject{
public:
	/**
	 * @brief	Default constructor for physics object
	 *
	 * @pre	Nothing
	 * @post	Object created
	 */
	PhysicsObject() = default;

	void set_resolution_type(const PhysicResolution phyx_res);
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

protected:
	/// The model of the item.
	std::string model_name_;
	/// The material of the item.
	std::string material_name_;

	//physics stuff
	PhysicResolution rb; 

};
