#include "ECSGui.hpp"

#include <imgui/misc/cpp/imgui_stdlib.h>
#include <glm/gtc/type_ptr.hpp>

void ECSGui::draw(ECS& ecs) {
	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Scene entities", nullptr, window_flags);
	ecs.get_registry().each([this, &ecs](auto entity_id) {
		auto& entity = ecs.get_entity(entity_id);

		if (ImGui::Selectable(entity.get_name().c_str())) {
			selected_entity_ = entity.get_entity_id();
		};
	});
	ImGui::End();

	ImGui::Begin("Properties", nullptr, window_flags);
	if (selected_entity_ != entt::null) {
		draw_entity(ecs.get_entity(selected_entity_));
	}
	ImGui::End();
}

void ECSGui::draw_entity(const Reflex::Entity& entity) {
	if (entity.any_component<Component::Transform>()) {
		draw_transform(entity.get_component<Component::Transform>());
	}

	if (entity.any_component<Component::Script>()) {
		draw_script(entity.get_component<Component::Script>());
	}

	if (entity.any_component<Component::Mesh>()) {
		draw_mesh(entity.get_component<Component::Mesh>());
	}

	if (entity.any_component<Component::Model>()) {
		draw_model(entity.get_component<Component::Model>());
	}

	if (entity.any_component<Component::Terrain>()) {
		draw_terrain(entity.get_component<Component::Terrain>());
	}

	if (entity.any_component<Component::DirectionalLight>()) {
		draw_directional_light(
		    entity.get_component<Component::DirectionalLight>());
	}

	if (entity.any_component<Component::PointLight>()) {
		draw_point_light(entity.get_component<Component::PointLight>());
	}

	if (entity.any_component<Component::SpotLight>()) {
		draw_spot_light(entity.get_component<Component::SpotLight>());
	}
}

void ECSGui::draw_script(Component::Script& script) {
	ImGui::Text("Script");
	input_text("Script name", script.lua_script);
}

void ECSGui::draw_mesh(Component::Mesh& mesh) {
	ImGui::Text("Mesh");

	input_text("Mesh name", mesh.mesh_name);
	input_text("Texture name", mesh.texture_name);
	input_text("Material name", mesh.material_name);
}

void ECSGui::draw_model(Component::Model& model) {
	ImGui::Text("Model");
	input_text("Model name", model.model_name);
	input_text("Material name", model.material_name);
}

void ECSGui::draw_terrain(Component::Terrain& terrain) {
	ImGui::Text("Terrain");
	input_text("Terrain name", terrain.terrain_name);
	input_text("Texture name", terrain.texture_name);
	input_text("Material name", terrain.material_name);
	input_text("Detailmap name", terrain.detailmap_name);
}

void ECSGui::draw_transform(Component::Transform& transform) {
	glm::vec3 euler = glm::eulerAngles(transform.rotation);

	ImGui::Text("Transform");
	ImGui::DragFloat3("Position", glm::value_ptr(transform.position), speed_);
	ImGui::DragFloat3("Rotation", glm::value_ptr(euler), speed_);
	ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), speed_);

	transform.rotation = glm::quat(euler);
}

void ECSGui::draw_directional_light(Component::DirectionalLight& light) {
	ImGui::Text("Directional light");
	ImGui::DragFloat3("Color", glm::value_ptr(light.color), speed_);
	ImGui::DragFloat("Ambient intensity", &light.ambient_intensity, speed_);
	ImGui::DragFloat("Diffuse intensity", &light.diffuse_intensity, speed_);
	ImGui::DragFloat3("Direction", glm::value_ptr(light.direction), speed_);
}

void ECSGui::draw_point_light(Component::PointLight& light) {
	ImGui::Text("Point light");
	ImGui::DragFloat3("Color", glm::value_ptr(light.color), speed_);
	ImGui::DragFloat("Ambient intensity", &light.ambient_intensity, speed_);
	ImGui::DragFloat("Diffuse intensity", &light.diffuse_intensity, speed_);
	ImGui::DragFloat3("Position", glm::value_ptr(light.position), speed_);
	ImGui::DragFloat("Constant", &light.constant, speed_);
	ImGui::DragFloat("Linear", &light.linear, speed_);
	ImGui::DragFloat("Quadratic", &light.quadratic, speed_);
}

void ECSGui::draw_spot_light(Component::SpotLight& light) {
	ImGui::Text("Spot light");
	ImGui::DragFloat3("Color", glm::value_ptr(light.color), speed_);
	ImGui::DragFloat("Ambient intensity", &light.ambient_intensity, speed_);
	ImGui::DragFloat("Diffuse intensity", &light.diffuse_intensity, speed_);
	ImGui::DragFloat3("Position", glm::value_ptr(light.position), speed_);
	ImGui::DragFloat("Constant", &light.constant, speed_);
	ImGui::DragFloat("Linear", &light.linear, speed_);
	ImGui::DragFloat("Quadratic", &light.quadratic, speed_);
	ImGui::DragFloat3("Direction", glm::value_ptr(light.direction), speed_);
	ImGui::DragFloat("Edge", &light.edge, speed_);
}

void ECSGui::input_text(const char* label, std::string& text) {
	std::string temp_str = text;
	if (ImGui::InputText(label, &temp_str,
	                     ImGuiInputTextFlags_EnterReturnsTrue)) {
		text = temp_str;
	};
}