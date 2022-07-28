#include "ECSGui.hpp"

#include "glm/gtc/type_ptr.hpp"

void ECSGui::draw(ECS& ecs) {
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
	                             ImGuiDockNodeFlags_PassthruCentralNode);

	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Scene entities", nullptr, window_flags);
	ecs.get_registry().each([this, &ecs](auto entity_id) {
		auto& entity = ecs.get_entity(entity_id);

		if (ImGui::Selectable(entity.get_name().c_str())) {
			selected_entity_ = entity.get_entity_id();
		};
	});
	ImGui::End();

	if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
		selected_entity_ = entt::null;

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

	// if (entity.any_component<Component::Script>()) {
	// 	draw_script(entity.get_component<Component::Script>());
	// }

	// if (entity.any_component<Component::Mesh>()) {
	// 	draw_mesh(entity.get_component<Component::Mesh>());
	// }

	// if (entity.any_component<Component::Model>()) {
	// 	draw_model(entity.get_component<Component::Model>());
	// }

	// if (entity.any_component<Component::Terrain>()) {
	// 	draw_terrain(entity.get_component<Component::Terrain>());
	// }

	// if (entity.any_component<Component::DirectionalLight>()) {
	// 	draw_directional_light(
	// 	    entity.get_component<Component::DirectionalLight>());
	// }

	// if (entity.any_component<Component::PointLight>()) {
	// 	draw_point_light(entity.get_component<Component::PointLight>());
	// }

	// if (entity.any_component<Component::SpotLight>()) {
	// 	draw_spot_light(entity.get_component<Component::SpotLight>());
	// }
}

void ECSGui::draw_transform(Component::Transform& transform) {
	constexpr float speed = 0.1f;

	glm::vec3 euler = glm::eulerAngles(transform.rotation);

	ImGui::Text("Transform");
	ImGui::DragFloat3("Position", glm::value_ptr(transform.position), speed);
	ImGui::DragFloat3("Rotation", glm::value_ptr(euler), speed);
	ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), speed);

	transform.rotation = glm::quat(euler);
}