#pragma once

#include "View/guiManager.hpp"

#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Terrain.hpp"

class ECSGui {
public:
	ECSGui() = default;

	void draw(ECS& ecs);

private:
	entt::entity selected_entity_ = {entt::null};
	constexpr static float speed_ = 0.1f;

	static void draw_entity(const Reflex::Entity& entity);

	static void draw_transform(Component::Transform& transform);

	static void draw_script(Component::Script& script);

	static void draw_mesh(Component::Mesh& mesh);

	static void draw_model(Component::Model& model);

	static void draw_terrain(Component::Terrain& terrain);

	static void draw_directional_light(
	    Component::DirectionalLight& directional_light);

	static void draw_point_light(Component::PointLight& point_light);

	static void draw_spot_light(Component::SpotLight& spot_light);

	static void input_text(const char* label, std::string& text);
};