#include "ECSGui.hpp"

void ECSGui::draw(ECS& ecs) {
	ImGui::Begin("Scene entities");
	ecs.get_registry().each([this, &ecs](auto entity_id) {
		draw_entity(ecs.get_entity(entity_id));
	});
	ImGui::End();
}

void ECSGui::draw_entity(const Reflex::Entity& entity) {
	ImGui::Selectable(entity.get_name().c_str());

	// constexpr ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected |
	//                                      ImGuiTreeNodeFlags_OpenOnArrow |
	//                                      ImGuiTreeNodeFlags_OpenOnDoubleClick;

	// ImGui::TreeNodeEx((void*)entity.get_entity_id(), flags,
	//                   entity.get_name().c_str());

	// if (entity.any_component<Component::Transform>()) {
	// 	draw_transform(entity.get_component<Component::Transform>());
	// }

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