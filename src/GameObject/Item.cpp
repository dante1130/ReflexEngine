#include "Item.hpp"

#include "ReflexEngine/ReflexEngine.hpp"

Item::Item(const std::string& model_path, GLfloat shininess,
           GLfloat spec_intensity) {
	model_.LoadModel(model_path);
	material_ = Material(shininess, spec_intensity);
}

void Item::add_draw_call() {
	DrawCall draw_call = [&]() { draw(); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void Item::draw() {
	auto shader = ReflexEngine::get_instance().renderer_.get_shader();

	shader->UseShader();

	GLuint uniform_model = shader->GetModelLocation();
	GLuint uniform_shininess = shader->GetShininessLocation();
	GLuint uniform_specular = shader->GetSpecularIntensityLocation();

	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
	material_.UseMaterial(uniform_shininess, uniform_specular);
	model_.RenderModel();
}
