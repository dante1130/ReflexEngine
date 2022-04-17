#include "Item.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

Item::Item(const std::string& modelName, GLfloat shininess,
           GLfloat spec_intensity) {
	m_modelName = modelName;
	material_ = Reflex::Material(shininess, spec_intensity);
}

void Item::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void Item::draw(std::shared_ptr<Shader> shader) {
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
	ModelManager& mm = ResourceManager::get_instance().get_model_manager();
	mm.get_model(m_modelName).RenderModel();
}

void Item::saveObject() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle, "Item");
	ObjectSaving::closeSctruct();
	ObjectSaving::createStruct("item");
	ObjectSaving::addValue("modelName", "cat", false);
	ObjectSaving::addValue("shininess", material_.getShininess(), false);
	ObjectSaving::addValue("spec_intensity", material_.getSpecIntensity(),
	                       true);
	ObjectSaving::closeSctruct();
	ObjectSaving::closeFile();
}
