#include "PhysicsObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

PhysicsObject::PhysicsObject() {}

void PhysicsObject::initModel(const std::string& model_path, GLfloat shininess,
                              GLfloat spec_intensity) {
	model_.LoadModel(model_path);
	material_ = Reflex::Material(shininess, spec_intensity);
}

void PhysicsObject::initRB(glm::vec3 pos, glm::vec3 rotation, float angle) {
	rb.init(pos, rotation, angle);
}

void PhysicsObject::update(float delta_time) {
	position = rb.getPosition();
	rotation = rb.getRotation();
	angle = rb.getAngle();
}

void PhysicsObject::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void PhysicsObject::draw(std::shared_ptr<Shader> shader) {
	auto default_shader = ReflexEngine::get_instance().renderer_.get_shader();

	glm::mat4 model(1.0f);
	model =
	    glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, glm::radians(angle),
	                    glm::vec3(rotation.x, rotation.y, rotation.z));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader->GetUsingTexture(), true);
	material_.UseMaterial(default_shader->GetShininessLocation(),
	                      default_shader->GetSpecularIntensityLocation());
	model_.RenderModel();
}
