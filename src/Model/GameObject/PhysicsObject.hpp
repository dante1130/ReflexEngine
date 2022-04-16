#pragma once

#include "BodyRigid.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Material.hpp"

class PhysicsObject : public BodyRigid {
public:
	PhysicsObject();

	void initModel(const std::string& model_path, GLfloat shininess,
	               GLfloat spec_intensity);

	void initRB(glm::vec3 pos, glm::vec3 rotation, float angle);

	void update(float delta_time) override;

	void add_draw_call() override;

	void draw(std::shared_ptr<Shader> shader) override;

private:
	/// The model of the item.
	Model model_ = {};
	/// The material of the item.
	Reflex::Material material_ = {};
};
