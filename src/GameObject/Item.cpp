#include "Item.hpp"

#include "ReflexEngine/ReflexEngine.hpp"

Item::Item(const std::string& model_path, GLfloat shininess,
           GLfloat spec_intensity) {
	model_.LoadModel(model_path);
	material_ = Material(shininess, spec_intensity);
}

void Item::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void Item::draw(std::shared_ptr<Shader> shader) {
	auto default_shader = ReflexEngine::get_instance().renderer_.get_shader();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, 4.0f));
	model =
	    glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	material_.UseMaterial(default_shader->GetShininessLocation(),
	                      default_shader->GetSpecularIntensityLocation());
	model_.RenderModel();
}
