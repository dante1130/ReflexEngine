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
#include "Model/Components/Statemachine.hpp"

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
	 * @brief Draw the selectable for the entity.
	 *
	 * @param entity The entity.
	 */
	void draw_entity(Reflex::Entity& entity);

	/**
	 * @brief Draw all the components in the entity.
	 *
	 * @param ecs The ECS.
	 * @param entity The entity to draw the components from.
	 */
	static void draw_entity_props(ECS& ecs, Reflex::Entity& entity);

	/**
	 * @brief Draw the add component button.
	 *
	 * @param entity The entity to add the component to.
	 */
	static void draw_add_component(Reflex::Entity& entity);

	/**
	 * @brief Draw the name of the entity.
	 *
	 * @param name The entity's name.
	 */
	static void draw_name(std::string& name);

	/**
	 * @brief Draw the transform component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_transform(Reflex::Entity& entity);

	/**
	 * @brief Draw the script component of the entity.
	 *
	 * @param ecs The ECS.
	 * @param entity The entity.
	 */
	static void draw_script(ECS& ecs, Reflex::Entity& entity);

	/**
	 * @brief Draw the mesh component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_mesh(Reflex::Entity& entity);

	/**
	 * @brief Draw the model component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_model(Reflex::Entity& entity);

	/**
	 * @brief Draw the terrain component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_terrain(Reflex::Entity& entity);

	/**
	 * @brief Draw the directional light component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_directional_light(Reflex::Entity& entity);

	/**
	 * @brief Draw the point light component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_point_light(Reflex::Entity& entity);

	/**
	 * @brief Draw the spot light component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_spot_light(Reflex::Entity& entity);

	/**
	 * @brief Draw the statemachine component of the entity.
	 *
	 * @param entity The entity.
	 */
	static void draw_statemachine(Reflex::Entity& entity);

	/**
	 * @brief A helper method for ImGui input text update on enter.
	 *
	 * @param label The label of the input text.
	 * @param text The text to update.
	 *
	 * @return True if the text was updated, false otherwise.
	 */
	static bool input_text(const char* label, std::string& text);
};
