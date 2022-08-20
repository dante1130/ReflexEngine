#include "ECSGui.hpp"

#include <imgui/misc/cpp/imgui_stdlib.h>
#include <glm/gtc/type_ptr.hpp>

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Md2Animation.hpp"
#include "Model/Components/Terrain.hpp"
#include "Model/Components/Statemachine.hpp"
#include "Model/Components/Remove.hpp"
#include "Model/Components/Rigidbody.hpp"

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
	if (registry.valid(selected_entity_)) {
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

	if (entity.any_component<Component::Md2Animation>()) {
		draw_md2_animation(entity);
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

	if (entity.any_component<Component::Rigidbody>()) {
		draw_rigidbody(entity);
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

		if (ImGui::MenuItem("Md2Animation")) {
			entity.add_component<Component::Md2Animation>();
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

		if (ImGui::MenuItem("Rigidbody")) {
			entity.add_component<Component::Rigidbody>();
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
	input_text("Mesh", mesh.mesh_name);
	input_text("Texture", mesh.texture_name);
	input_text("Material", mesh.material_name);
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
	input_text("Model", model.model_name);
	input_text("Material", model.material_name);
	ImGui::PopID();
}

void ECSGui::draw_md2_animation(Reflex::Entity& entity) {
	auto& md2_animation = entity.get_component<Component::Md2Animation>();

	ImGui::PushID("Md2Animation");
	ImGui::Text("Md2Animation");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::Terrain>();
	}
	input_text("Md2 model", md2_animation.md2_name);
	input_text("Texture", md2_animation.texture_name);
	input_text("Material", md2_animation.material_name);

	draw_animation_state(entity);

	ImGui::Checkbox("Animation done", &md2_animation.is_animation_done);
	ImGui::Checkbox("Loop", &md2_animation.is_loop);
	ImGui::Checkbox("Interpolated", &md2_animation.is_interpolated);

	ImGui::PopID();
}

void ECSGui::draw_animation_state(Reflex::Entity& entity) {
	auto& animstate = entity.get_component<Component::Md2Animation>().animstate;

	ImGui::PushID("AnimationState");
	ImGui::Text("AnimationState");

	const char* curr_anim_type =
	    md2::animation_type_str[static_cast<size_t>(animstate.type)];

	constexpr size_t max_anims =
	    static_cast<size_t>(md2::animation_type::MAX_ANIMATIONS);

	input_int("Start frame", animstate.start_frame);
	input_int("End frame", animstate.end_frame);
	input_int("FPS", animstate.fps);

	if (ImGui::BeginCombo("Animation type", curr_anim_type)) {
		for (size_t i = 0; i < max_anims; ++i) {
			if (ImGui::Selectable(md2::animation_type_str[i])) {
				entity.patch_component<Component::Md2Animation>(
				    [i](auto& md2_animation) {
					    md2_animation.animstate.type =
					        static_cast<md2::animation_type>(i);
				    });
			}
		}
		ImGui::EndCombo();
	}

	input_int("Current frame", animstate.curr_frame);
	input_int("Next frame", animstate.next_frame);

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
	input_text("Terrain", terrain.terrain_name);
	input_text("Texture", terrain.texture_name);
	input_text("Material", terrain.material_name);
	input_text("Detailmap", terrain.detailmap_name);
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

void ECSGui::draw_rigidbody(Reflex::Entity& entity) {
	auto& rigidbody = entity.get_component<Component::Rigidbody>();

	ImGui::PushID("Rigidbody");
	ImGui::Text("Rigidbody");
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	if (ImGui::Button("Delete")) {
		entity.remove_component<Component::Rigidbody>();
	}
	bool react_resolution = rigidbody.usingReactResolve();
	ImGui::Checkbox("Using react resolution", &react_resolution);
	ImGui::Checkbox("Gravity On", &rigidbody.gravity_on);
	ImGui::Checkbox("Is Trigger", &rigidbody.is_trigger);
	ImGui::Checkbox("Can Sleep", &rigidbody.can_sleep);
	if (ImGui::InputFloat("Drag Force", &rigidbody.lin_drag, speed_)) {
		if (rigidbody.lin_drag < 0) {
			rigidbody.lin_drag = 0;
		}
	}
	if (ImGui::InputFloat("Drag Torque", &rigidbody.ang_drag, speed_)) {
		if (rigidbody.ang_drag < 0) {
			rigidbody.ang_drag = 0;
		}
	}
	glm::vec3 linear_velocity = rigidbody.getVelocity();
	if (ImGui::DragFloat3("Linear velocity", glm::value_ptr(linear_velocity),
	                      speed_)) {
		rigidbody.setVelocity(linear_velocity);
	}

	glm::vec3 angular_velocity = rigidbody.getAngVelocity();
	if (ImGui::DragFloat3("Angular velocity", glm::value_ptr(angular_velocity),
	                      speed_)) {
		rigidbody.setAngVelocity(angular_velocity);
	}
	glm::vec3 pos = rigidbody.getPosition();
	std::string rb_position = "rb position: " + std::to_string(pos.x) + " " +
	                          std::to_string(pos.y) + " " +
	                          std::to_string(pos.z);
	ImGui::Text(rb_position.c_str());
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
	input_int("unique id", statemachine.unique_statemachine_identifier);
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

bool ECSGui::input_int(const char* label, int& value) {
	int temp_int = value;
	if (ImGui::InputInt(label, &temp_int)) {
		value = temp_int;
		return true;
	};

	return false;
}

bool ECSGui::input_double(const char* label, double& value) {
	double temp_double = value;
	if (ImGui::InputDouble(label, &temp_double)) {
		value = temp_double;
		return true;
	};

	return false;
}
