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

/**
 * @class ECSGui
 * @brief ImGui facade to display all the components of an entity in the scene.
 */
class ECSGui {
public:
	ECSGui() = default;

	/**
	 * @brief Draw the entities from the ECS in the scene.
	 *
	 * @param ecs The ECS to draw the entities from.
	 */
	void draw(ECS& ecs);

private:
	/// The currently selected entity.
	entt::entity selected_entity_ = {entt::null};
	/// The drag speed.
	constexpr static float speed_ = 0.1f;

	/**
	 * @brief Draw all the components in the entity.
	 *
	 * @param entity The entity to draw the components from.
	 */
	static void draw_entity(const Reflex::Entity& entity);

	/**
	 * @brief Draw the transform component of the entity.
	 *
	 * @param transform The transform component of the entity.
	 */
	static void draw_transform(Component::Transform& transform);

	/**
	 * @brief Draw the script component of the entity.
	 *
	 * @param script The script component of the entity.
	 */
	static void draw_script(Component::Script& script);

	/**
	 * @brief Draw the mesh component of the entity.
	 *
	 * @param mesh The mesh component of the entity.
	 */
	static void draw_mesh(Component::Mesh& mesh);

	/**
	 * @brief Draw the model component of the entity.
	 *
	 * @param model The model component of the entity.
	 */
	static void draw_model(Component::Model& model);

	/**
	 * @brief Draw the terrain component of the entity.
	 *
	 * @param terrain The terrain component of the entity.
	 */
	static void draw_terrain(Component::Terrain& terrain);

	/**
	 * @brief Draw the directional light component of the entity.
	 *
	 * @param directional_light The directional light component of the entity.
	 */
	static void draw_directional_light(
	    Component::DirectionalLight& directional_light);

	/**
	 * @brief Draw the point light component of the entity.
	 *
	 * @param point_light The point light component of the entity.
	 */
	static void draw_point_light(Component::PointLight& point_light);

	/**
	 * @brief Draw the spot light component of the entity.
	 *
	 * @param spot_light The spot light component of the entity.
	 */
	static void draw_spot_light(Component::SpotLight& spot_light);

	/**
	 * @brief A helper method for ImGui input text update on enter.
	 *
	 * @param label The label of the input text.
	 * @param text The text to update.
	 */
	static void input_text(const char* label, std::string& text);
};