#include "ComponentFunctions.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/LuaManager.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"

void component::draw_model(entt::registry& registry) {
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
			model_matrix = glm::translate(model_matrix, transform.position);
			model_matrix = model_matrix * glm::mat4_cast(transform.rotation);
			model_matrix = glm::scale(model_matrix, transform.scale);

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

void component::init_script(entt::registry& registry, entt::entity entity) {
	auto& lua = LuaManager::get_instance().get_state();

	auto& script = registry.get<Script>(entity);

	if (!script.entity) return;

	lua.script_file(script.lua_script);

	lua["init"](*script.entity);

	script.lua_variables = lua["variables"];
}

void component::init_directional_light(entt ::registry& registry,
                                       entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& directional_light = registry.get<DirectionalLight>(entity);

	light_manager.set_directional_light(directional_light);
}

void component::init_point_light(entt::registry& registry,
                                 entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& point_light = registry.get<PointLight>(entity);

	point_light.light_id = light_manager.add_point_light(point_light);
}

void component::init_spot_light(entt::registry& registry, entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& spot_light = registry.get<SpotLight>(entity);

	spot_light.light_id = light_manager.add_spot_light(spot_light);
}

void component::update_directional_light(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto view = registry.view<DirectionalLight>();

	for (auto entity : view) {
		auto& directional_light = view.get<DirectionalLight>(entity);
		light_manager.update_directional_light(directional_light);
	}
}

void component::update_point_light(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto view = registry.view<PointLight>();

	for (auto entity : view) {
		auto& point_light = view.get<PointLight>(entity);

		light_manager.update_point_light(point_light.light_id, point_light);
	}
}

void component::update_spot_light(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto view = registry.view<SpotLight>();

	for (auto entity : view) {
		auto& spot_light = view.get<SpotLight>(entity);

		light_manager.update_spot_light(spot_light.light_id, spot_light);
	}
}

void component::update_script(entt::registry& registry) {
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
