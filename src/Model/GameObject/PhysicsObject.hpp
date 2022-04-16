#pragma once

#include "BodyRigid.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Material.hpp"

class PhysicsObject : public BodyRigid {
public:
	/**
	 * @brief	Default constructor for physics object
	 * @param	No param
	 * @return	No return
	 *
	 * @pre	Nothing
	 * @post	Object created
	 */
	PhysicsObject();

	/**
	 * @brief	Initialised the model
	 * @param	model_path		- path to model
	 * @param	shininess		- shininess
	 * @param	spec_intensity	- specual intensity
	 * @return	No return
	 *
	 * @pre		Object exists
	 * @post	model initialised
	 */
	void initModel(const std::string& model_path, GLfloat shininess,
	               GLfloat spec_intensity);

	/**
	 * @brief	Initialised the rigid body
	 * @param	pos			- position of the rigid body
	 * @param	rotation	- axis of rotation of the rigid body
	 * @param	angle		- Rotation around axis of rotation of rigid body
	 * @return	No return
	 *
	 * @pre		Object exists
	 * @post	rigid body initialised
	 */
	void initRB(glm::vec3 pos, glm::vec3 rotation, float angle);

	/**
	 * @brief	Updates the object
	 * @param	delta_time	- Time since last frame
	 * @return	No return
	 *
	 * @pre		rigid body initialised
	 * @post	Object updated
	 */
	void update(float delta_time) override;

	/**
	 * @brief	Adds draw call of object
	 * @param	No param
	 * @return	No return
	 *
	 * @pre		Model initialised
	 * @post	Draw call added
	 */
	void add_draw_call() override;

	/**
	 * @brief	Draws the object
	 * @param	shader	- The shader
	 * @return	No return
	 *
	 * @pre		Model initialised
	 * @post	Model drawn
	 */
	void draw(std::shared_ptr<Shader> shader) override;

private:
	/// The model of the item.
	Model model_ = {};
	/// The material of the item.
	Reflex::Material material_ = {};
};
