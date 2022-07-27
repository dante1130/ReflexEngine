#include "System.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/LuaManager.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Terrain.hpp"
#include "Model/Components/Remove.hpp"

void System::draw_model(entt::registry& registry) {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	auto& resource_manager = ResourceManager::get_instance();
	auto& model_manager = resource_manager.get_model_manager();
	auto& material_manager = resource_manager.get_material_manager();

	registry.view<Component::Transform, Component::Model>().each(
	    [&renderer, &model_manager, &material_manager](auto& transform,
	                                                   auto& model) {
		    DrawCall draw_call = [&transform, &model, &model_manager,
		                          &material_manager](const Shader& shader) {
			    glm::mat4 model_matrix(1.0f);
			    model_matrix = glm::translate(model_matrix, transform.position);
			    model_matrix =
			        model_matrix * glm::mat4_cast(transform.rotation);
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
	    });
}

void System::draw_mesh(entt::registry& registry) {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	auto& resource_manager = ResourceManager::get_instance();
	auto& mesh_manager = resource_manager.get_mesh_manager();
	auto& texture_manager = resource_manager.get_texture_manager();
	auto& material_manager = resource_manager.get_material_manager();

	registry.view<Component::Transform, Component::Mesh>().each(
	    [&renderer, &mesh_manager, &texture_manager, &material_manager](
	        auto& transform, auto& mesh) {
		    DrawCall draw_call = [&transform, &mesh, &mesh_manager,
		                          &texture_manager,
		                          &material_manager](const Shader& shader) {
			    glm::mat4 model_matrix(1.0f);
			    model_matrix = glm::translate(model_matrix, transform.position);
			    model_matrix =
			        model_matrix * glm::mat4_cast(transform.rotation);
			    model_matrix = glm::scale(model_matrix, transform.scale);

			    glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE,
			                       glm::value_ptr(model_matrix));
			    glUniform1i(shader.GetUsingTexture(), true);

			    texture_manager.get_texture(mesh.texture_name).use_texture();

			    material_manager.get_material(mesh.material_name)
			        .UseMaterial(shader.GetShininessLocation(),
			                     shader.GetSpecularIntensityLocation());

			    mesh_manager.get_mesh(mesh.mesh_name).render_mesh();
		    };
		    renderer.add_draw_call(draw_call);
	    });
}

void System::draw_terrain(entt::registry& registry) {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	auto& resource_manager = ResourceManager::get_instance();
	auto& terrain_manager = resource_manager.get_terrain_manager();
	auto& texture_manager = resource_manager.get_texture_manager();
	auto& material_manager = resource_manager.get_material_manager();

	registry.view<Component::Transform, Component::Terrain>().each(
	    [&renderer, &terrain_manager, &texture_manager, &material_manager](
	        auto& transform, auto& terrain_component) {
		    DrawCall draw_call = [&transform, &terrain_component,
		                          &terrain_manager, &texture_manager,
		                          &material_manager](const Shader& shader) {
			    auto& terrain =
			        terrain_manager.get_terrain(terrain_component.terrain_name);

			    terrain.set_scale(transform.scale);

			    glm::mat4 model = glm::mat4(1.0f);
			    model = glm::translate(model, transform.position);
			    model = glm::translate(model, terrain.get_origin());
			    model = model * glm::mat4_cast(transform.rotation);
			    model = glm::scale(model, transform.scale);

			    glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE,
			                       glm::value_ptr(model));

			    material_manager.get_material(terrain_component.material_name)
			        .UseMaterial(shader.GetShininessLocation(),
			                     shader.GetSpecularIntensityLocation());

			    const auto& texture =
			        texture_manager.get_texture(terrain_component.texture_name);

			    const auto& detailmap = texture_manager.get_texture(
			        terrain_component.detailmap_name);

			    terrain.set_texture(texture.get_texture_id());
			    terrain.set_detailmap(detailmap.get_texture_id());

			    terrain.render(shader);
		    };

		    renderer.add_draw_call(draw_call);
	    });
}

void System::init_script(entt::registry& registry, entt::entity entity) {
	auto& lua = LuaManager::get_instance().get_state();

	auto& script = registry.get<Component::Script>(entity);

	if (!script.ecs && !script.entity) return;

	lua.script_file(script.lua_script);

	lua["init"](*script.ecs, *script.entity);

	script.lua_variables = lua["var"];
}

void System::init_directional_light(entt ::registry& registry,
                                    entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& directional_light = registry.get<Component::DirectionalLight>(entity);

	light_manager.set_directional_light(directional_light);
}

void System::init_point_light(entt::registry& registry, entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& point_light = registry.get<Component::PointLight>(entity);

	point_light.light_id = light_manager.add_point_light(point_light);
}

void System::init_spot_light(entt::registry& registry, entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& spot_light = registry.get<Component::SpotLight>(entity);

	spot_light.light_id = light_manager.add_spot_light(spot_light);
}

void System::update_directional_light(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	registry.view<Component::DirectionalLight>().each(
	    [&light_manager](auto& directional_light) {
		    light_manager.update_directional_light(directional_light);
	    });
}

void System::update_point_light(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	registry.view<Component::PointLight>().each(
	    [&light_manager](auto& point_light) {
		    light_manager.update_point_light(point_light.light_id, point_light);
	    });
}

void System::update_spot_light(entt::registry& registry) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	registry.view<Component::SpotLight>().each(
	    [&light_manager](auto& spot_light) {
		    light_manager.update_spot_light(spot_light.light_id, spot_light);
	    });
}

void System::update_script(entt::registry& registry) {
	auto& lua = LuaManager::get_instance().get_state();

	registry.view<Component::Script>().each([&lua](auto& script) {
		if (script.ecs && script.entity) {
			lua.script_file(script.lua_script);

			lua["var"] = script.lua_variables;

			lua["update"](*script.ecs, *script.entity);

			script.lua_variables = lua["var"];
		}
	});
}

void System::update_remove(ECS& ecs) {
	for (auto entity : ecs.get_registry().view<Component::Remove>()) {
		ecs.destroy_entity(entity);
	}
}
