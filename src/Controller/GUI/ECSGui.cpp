#include "ECSGui.hpp"

#include <imgui/misc/cpp/imgui_stdlib.h>
#include <glm/gtc/type_ptr.hpp>

#include "Model/Components/Remove.hpp"

void ECSGui::draw(ECS& ecs) {
	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	auto& registry = ecs.get_registry();

	ImGui::Begin("Scene entities", nullptr, window_flags);
	registry.each([this, &ecs](auto entity_id) {
		draw_entity(ecs.get_entity(entity_id));
	});

	// Deselect when clicking on blank space.
	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
		selected_entity_ = entt::null;
	}

	if (ImGui::BeginPopupContextWindow("OnBlank",
	                                   ImGuiPopupFlags_MouseButtonRight |
	                                       ImGuiPopupFlags_NoOpenOverItems)) {
		if (ImGui::MenuItem("Create entity")) {
			ecs.create_entity(std::string())
			    .add_component<Component::Transform>();
		}
		ImGui::EndPopup();
	}

	ImGui::End();

	ImGui::Begin("Properties", nullptr, window_flags);
	if (selected_entity_ != entt::null) {
		auto& entity = ecs.get_entity(selected_entity_);
		draw_entity_props(ecs, entity);
		draw_add_component(entity);
	}
	ImGui::End();
}

void ECSGui::draw_entity(Reflex::Entity& entity) {
	ImGui::PushID(static_cast<int>(entity.get_entity_id()));

	bool selected = false;
	ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0, 0.5f));
	ImGui::Selectable(entity.get_name().c_str(), &selected,
	                  ImGuiSelectableFlags_AllowItemOverlap, ImVec2(0, 20));
	ImGui::PopStyleVar();

	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);

	if (ImGui::Button("Delete")) {
		entity.add_component<Component::Remove>();
		if (selected_entity_ == entity.get_entity_id()) {
			selected_entity_ = entt::null;
		}
	}

	if (selected) {
		selected_entity_ = entity.get_entity_id();
	};

	ImGui::PopID();
};

void ECSGui::draw_entity_props(ECS& ecs, Reflex::Entity& entity) {
	draw_name(entity.get_name());
	draw_transform(entity);

	if (entity.any_component<Component::Script>()) {
		draw_script(ecs, entity);
	}

	if (entity.any_component<Component::Mesh>()) {
		draw_mesh(entity);
	}

	if (entity.any_component<Component::Model>()) {
		draw_model(entity);
	}

	if (entity.any_component<Component::Terrain>()) {
		draw_terrain(entity);
	}

	if (entity.any_component<Component::DirectionalLight>()) {
		draw_directional_light(entity);
	}

	if (entity.any_component<Component::PointLight>()) {
		draw_point_light(entity);
	}

	if (entity.any_component<Component::SpotLight>()) {
		draw_spot_light(entity);
	}

	if (entity.any_component<Component::Statemachine>()) {
		draw_statemachine(entity);
	}
}

void ECSGui::draw_add_component(Reflex::Entity& entity) {
	if (ImGui::Button("Add component")) {
		ImGui::OpenPopup("AddComponent");
	}

	if (ImGui::BeginPopup("AddComponent")) {
		if (ImGui::MenuItem("Script")) {
			entity.add_component<Component::Script>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("Mesh")) {
			entity.add_component<Component::Mesh>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("Model")) {
			entity.add_component<Component::Model>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("Terrain")) {
			entity.add_component<Component::Terrain>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("DirectionalLight")) {
			entity.add_component<Component::DirectionalLight>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("PointLight")) {
			entity.add_component<Component::PointLight>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("SpotLight")) {
			entity.add_component<Component::SpotLight>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("Statemachine")) {
			entity.add_component<Component::Statemachine>();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void ECSGui::draw_name(std::string& name) {
	ImGui::PushID("Name");
	ImGui::Text("Name");
	input_text("", name);
	ImGui::PopID();
}

void ECSGui::draw_script(ECS& ecs, Reflex::Entity& entity) {
	auto& script = entity.get_component<Component::Script>();

	ImGui::PushID("Script");
	ImGui::Text("Script");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::Script>();
	}

	if (input_text("Script name", script.lua_script)) {
		entity.patch_component<Component::Script>(
		    [&ecs, &entity](auto& script) {
			    script.ecs = &ecs;
			    script.entity = &entity;
		    });
	};
	ImGui::PopID();
}

void ECSGui::draw_mesh(Reflex::Entity& entity) {
	auto& mesh = entity.get_component<Component::Mesh>();

	ImGui::PushID("Mesh");
	ImGui::Text("Mesh");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::Mesh>();
	}
	input_text("Mesh name", mesh.mesh_name);
	input_text("Texture name", mesh.texture_name);
	input_text("Material name", mesh.material_name);
	ImGui::PopID();
}

void ECSGui::draw_model(Reflex::Entity& entity) {
	auto& model = entity.get_component<Component::Model>();

	ImGui::PushID("Model");
	ImGui::Text("Model");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::Model>();
	}
	input_text("Model name", model.model_name);
	input_text("Material name", model.material_name);
	ImGui::PopID();
}

void ECSGui::draw_terrain(Reflex::Entity& entity) {
	auto& terrain = entity.get_component<Component::Terrain>();

	ImGui::PushID("Terrain");
	ImGui::Text("Terrain");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::Terrain>();
	}
	input_text("Terrain name", terrain.terrain_name);
	input_text("Texture name", terrain.texture_name);
	input_text("Material name", terrain.material_name);
	input_text("Detailmap name", terrain.detailmap_name);
	ImGui::PopID();
}

void ECSGui::draw_transform(Reflex::Entity& entity) {
	auto& transform = entity.get_component<Component::Transform>();

	ImGui::PushID("Transform");
	ImGui::Text("Transform");
	ImGui::DragFloat3("Position", glm::value_ptr(transform.position), speed_);
	ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), speed_);
	ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), speed_);
	ImGui::PopID();
}

void ECSGui::draw_directional_light(Reflex::Entity& entity) {
	auto& light = entity.get_component<Component::DirectionalLight>();

	ImGui::PushID("Directional light");
	ImGui::Text("Directional light");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::DirectionalLight>();
	}
	ImGui::ColorEdit3("Color", glm::value_ptr(light.color));
	ImGui::DragFloat("Ambient", &light.ambient_intensity, speed_);
	ImGui::DragFloat("Diffuse", &light.diffuse_intensity, speed_);
	ImGui::DragFloat3("Direction", glm::value_ptr(light.direction), speed_);
	ImGui::PopID();
}

void ECSGui::draw_point_light(Reflex::Entity& entity) {
	auto& light = entity.get_component<Component::PointLight>();

	ImGui::PushID("Point light");
	ImGui::Text("Point light");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::PointLight>();
	}
	ImGui::ColorEdit3("Color", glm::value_ptr(light.color));
	ImGui::DragFloat("Ambient", &light.ambient_intensity, speed_);
	ImGui::DragFloat("Diffuse", &light.diffuse_intensity, speed_);
	ImGui::DragFloat3("Position", glm::value_ptr(light.position), speed_);
	ImGui::DragFloat("Constant", &light.constant, speed_);
	ImGui::DragFloat("Linear", &light.linear, speed_);
	ImGui::DragFloat("Quadratic", &light.quadratic, speed_);
	ImGui::PopID();
}

void ECSGui::draw_spot_light(Reflex::Entity& entity) {
	auto& light = entity.get_component<Component::SpotLight>();

	ImGui::PushID("Spot light");
	ImGui::Text("Spot light");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::SpotLight>();
	}
	ImGui::ColorEdit3("Color", glm::value_ptr(light.color));
	ImGui::DragFloat("Ambient", &light.ambient_intensity, speed_);
	ImGui::DragFloat("Diffuse", &light.diffuse_intensity, speed_);
	ImGui::DragFloat3("Position", glm::value_ptr(light.position), speed_);
	ImGui::DragFloat("Constant", &light.constant, speed_);
	ImGui::DragFloat("Linear", &light.linear, speed_);
	ImGui::DragFloat("Quadratic", &light.quadratic, speed_);
	ImGui::DragFloat3("Direction", glm::value_ptr(light.direction), speed_);
	ImGui::DragFloat("Edge", &light.edge, speed_);
	ImGui::PopID();
}

void ECSGui::draw_statemachine(Reflex::Entity& entity) {
	auto& statemachine = entity.get_component<Component::Statemachine>();

	ImGui::PushID("Statemachine");
	ImGui::Text("Statemachine");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::Statemachine>();
	}
	ImGui::InputInt("unique id", &statemachine.unique_statemachine_identifier);
	input_text("Global state", statemachine.global_state);
	input_text("Current state", statemachine.current_state);
	input_text("Previous state", statemachine.previous_state);
	ImGui::PopID();
}

bool ECSGui::input_text(const char* label, std::string& text) {
	std::string temp_str = text;
	if (ImGui::InputText(label, &temp_str,
	                     ImGuiInputTextFlags_EnterReturnsTrue)) {
		text = temp_str;
		return true;
	};

	return false;
}
