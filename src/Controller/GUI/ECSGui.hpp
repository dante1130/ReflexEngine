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

	void draw_entity(const Reflex::Entity& entity);

	void draw_transform(Component::Transform& transform);

	// void draw_script(const Component::Script& script);

	// void draw_mesh(const Component::Mesh& mesh);

	// void draw_model(const Component::Model& model);

	// void draw_terrain(const Component::Terrain& terrain);

	// void draw_directional_light(
	//     const Component::DirectionalLight& directional_light);

	// void draw_point_light(const Component::PointLight& point_light);

	// void draw_spot_light(const Component::SpotLight& spot_light);
};