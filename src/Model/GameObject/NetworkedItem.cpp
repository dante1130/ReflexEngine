#include "NetworkedItem.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

NetworkedItem::NetworkedItem(const std::string& model_name, const std::string& texture_name) {
	model_name_ = model_name;
	material_name_ = texture_name;
}

void NetworkedItem::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };
	//
	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}
//

void NetworkedItem::initNetworkManager() {

}

void
    NetworkedItem::draw(std::shared_ptr<Shader> shader) {
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

	auto& material_m = ResourceManager::get_instance().get_material_manager();
	material_m.get_material(material_name_)
	    .UseMaterial(default_shader->GetShininessLocation(),
	                 default_shader->GetSpecularIntensityLocation());

	auto& mm = ResourceManager::get_instance().get_model_manager();
	mm.get_model(model_name_).RenderModel();
}

void Item::save_object() {
}
