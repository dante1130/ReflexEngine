#include "ComponentFunctions.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/LuaManager.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"

void component::model_draw(entt::registry& registry) {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	auto& resource_manager = ResourceManager::get_instance();
	auto& model_manager = resource_manager.get_model_manager();
	auto& material_manager = resource_manager.get_material_manager();

	auto view = registry.view<Transform, Model>();

	for (auto entity : view) {
		auto& transform = view.get<Transform>(entity);
		auto& model = view.get<Model>(entity);

		DrawCall draw_call = [transform, model, &model_manager,
		                      &material_manager](const Shader& shader) {
			glm::mat4 model_matrix(1.0f);
			model_matrix =
			    glm::translate(model_matrix, glm::vec3(transform.position.x,
			                                           transform.position.y,
			                                           transform.position.z));
			model_matrix = glm::rotate(
			    model_matrix, glm::radians(transform.angle),
			    glm::vec3(transform.rotation.x, transform.rotation.y,
			              transform.rotation.z));
			model_matrix = glm::scale(
			    model_matrix, glm::vec3(transform.scale.x, transform.scale.y,
			                            transform.scale.z));
			glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE,
			                   glm::value_ptr(model_matrix));
			glUniform1i(shader.GetUsingTexture(), true);

			material_manager.get_material(model.material_name)
			    .UseMaterial(shader.GetShininessLocation(),
			                 shader.GetSpecularIntensityLocation());

			model_manager.get_model(model.model_name).RenderModel();
		};

		renderer.add_draw_call(draw_call);
	}
}

void component::script_init(entt::registry& registry, entt::entity entity) {
	auto& lua = LuaManager::get_instance().get_state();

	auto& script = registry.get<Script>(entity);

	if (!script.entity) return;

	lua.script_file(script.lua_script);

	lua["init"](*script.entity);

	script.lua_variables = lua["variables"];
}

void component::directional_light_init(entt ::registry& registry,
                                       entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& directional_light = registry.get<DirectionalLight>(entity);
	light_manager.set_directional_light(directional_light.light_data);
}

void component::point_light_init(entt::registry& registry,
                                 entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& point_light = registry.get<PointLight>(entity);
	auto& transform = registry.get<Transform>(entity);

	point_light.light_data.position = transform.position;

	light_manager.add_point_light(point_light.light_data);
}

void component::spot_light_init(entt::registry& registry, entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& spot_light = registry.get<SpotLight>(entity);
	auto& transform = registry.get<Transform>(entity);

	spot_light.light_data.position = transform.position;

	light_manager.add_spot_light(spot_light.light_data);
}

void component::directional_light_update(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto view = registry.view<DirectionalLight>();

	for (auto entity : view) {
		auto& directional_light = view.get<DirectionalLight>(entity);
		light_manager.update_directional_light(directional_light.light_data);
	}
}

void component::point_light_update(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto view = registry.view<PointLight, Transform>();

	for (auto entity : view) {
		auto& point_light = view.get<PointLight>(entity);
		auto& transform = view.get<Transform>(entity);

		point_light.light_data.position = transform.position;

		light_manager.update_point_light(point_light.light_id,
		                                 point_light.light_data);
	}
}

void component::spot_light_update(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto view = registry.view<SpotLight, Transform>();

	for (auto entity : view) {
		auto& spot_light = view.get<SpotLight>(entity);
		auto& transform = view.get<Transform>(entity);

		spot_light.light_data.position = transform.position;

		light_manager.update_spot_light(spot_light.light_id,
		                                spot_light.light_data);
	}
}

void component::script_update(entt::registry& registry) {
	auto& lua = LuaManager::get_instance().get_state();

	auto view = registry.view<Script>();

	for (auto entity : view) {
		auto& script = view.get<Script>(entity);

		if (!script.entity) continue;

		lua.script_file(script.lua_script);

		lua["variables"] = script.lua_variables;

		lua["update"](*script.entity);

		script.lua_variables = lua["variables"];
	}
}