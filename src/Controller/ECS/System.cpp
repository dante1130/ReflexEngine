#include "System.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/Physics/Physics.hpp"
#include "Controller/Affordance/AffordanceHelper.hpp"
#include "Controller/Affordance/AffordanceSystem.hpp"

#include "Model/RunTimeDataStorage/GlobalDataStorage.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Md2Animation.hpp"
#include "Model/Components/Terrain.hpp"
#include "Model/Components/Statemachine.hpp"
#include "Model/Components/Remove.hpp"
#include "Model/Components/RigidBody.hpp"
#include "Model/Components/AffordanceAgent.hpp"
#include "Model/Components/Affordance.hpp"

void System::draw_model(entt::registry& registry) {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	auto& resource_manager = ResourceManager::get_instance();
	auto& model_manager = resource_manager.get_model_manager();
	auto& material_manager = resource_manager.get_material_manager();

	registry.view<Component::Transform, Component::Model>().each(
	    [&](auto& transform, auto& model) {
		    DrawCall draw_call = [&](const Shader& shader) {
			    glm::mat4 model_matrix(1.0f);
			    model_matrix = glm::translate(model_matrix, transform.position);
			    model_matrix *=
			        glm::mat4_cast(glm::quat(glm::radians(transform.rotation)));
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
	    [&](auto& transform, auto& mesh) {
		    DrawCall draw_call = [&](const Shader& shader) {
			    glm::mat4 model_matrix(1.0f);
			    model_matrix = glm::translate(model_matrix, transform.position);
			    model_matrix *=
			        glm::mat4_cast(glm::quat(glm::radians(transform.rotation)));
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

void System::draw_md2(entt::registry& registry) {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	auto& resource_manager = ResourceManager::get_instance();
	auto& md2_manager = resource_manager.get_md2_model_manager();
	auto& texture_manager = resource_manager.get_texture_manager();
	auto& material_manager = resource_manager.get_material_manager();

	registry.view<Component::Transform, Component::Md2Animation>().each(
	    [&](auto& transform, auto& md2) {
		    DrawCall draw_call = [&](const Shader& shader) {
			    glm::mat4 model(1.0F);
			    model = glm::translate(model, transform.position);
			    model *=
			        glm::mat4_cast(glm::quat(glm::radians(transform.rotation)));
			    // Md2 custom rotations.
			    model = glm::rotate(model, glm::radians(-90.0F),
			                        glm::vec3(1.0F, 0.0F, 0.0F));
			    model = glm::rotate(model, glm::radians(90.0F),
			                        glm::vec3(0.0F, 0.0F, 1.0F));
			    model = glm::scale(model, transform.scale);

			    glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE,
			                       glm::value_ptr(model));
			    glUniform1i(shader.GetUsingTexture(), true);

			    texture_manager.get_texture(md2.texture_name).use_texture();

			    material_manager.get_material(md2.material_name)
			        .UseMaterial(shader.GetShininessLocation(),
			                     shader.GetSpecularIntensityLocation());

			    auto& md2_model = md2_manager.get_md2_model(md2.md2_name);

			    if (md2.is_interpolated) {
				    md2_model.render_interpolated_frame(
				        md2.animstate.curr_frame, md2.animstate.next_frame,
				        md2.animstate.interpol);
			    } else {
				    md2_model.render_frame(md2.animstate.curr_frame);
			    }
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
	    [&](auto& transform, auto& terrain_component) {
		    DrawCall draw_call = [&](const Shader& shader) {
			    auto& terrain =
			        terrain_manager.get_terrain(terrain_component.terrain_name);

			    terrain.set_scale(transform.scale);

			    glm::mat4 model = glm::mat4(1.0f);
			    model = glm::translate(model, transform.position);
			    model = glm::translate(model, terrain.get_origin());
			    model *=
			        glm::mat4_cast(glm::quat(glm::radians(transform.rotation)));
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

void System::init_rigidbody(entt::registry& registry, entt::entity entity) {
	auto& rigidbody_manager =
	    ResourceManager::get_instance().get_rigidbody_manager();

	auto& rigidbody = registry.get<Component::Rigidbody>(entity);
	auto& transform = registry.get<Component::Transform>(entity);

	rigidbody_manager.add_rigidbody(rigidbody, transform);
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

void System::init_md2_animation(entt::registry& registry, entt::entity entity) {
	auto& md2 = registry.get<Component::Md2Animation>(entity);

	md2::anim_t anim = md2::animations_[static_cast<int>(md2.animstate.type)];

	md2.animstate.start_frame = anim.first_frame;
	md2.animstate.end_frame = anim.last_frame;
	md2.animstate.next_frame = anim.first_frame + 1;
	md2.animstate.fps = anim.fps;
}

void System::init_statemachine(entt::registry& registry, entt::entity entity) {
	const auto& lua = LuaManager::get_instance().get_state();

	auto& statemachine = registry.get<Component::Statemachine>(entity);

	if (!statemachine.entity) return;

	statemachine.lua_variables = lua["entity"]["statemachine"]["var"];
}

void System::update_rigidbody(entt::registry& registry) {
	if (EngineTime::is_paused()) {
		Physics::updateWorld(EngineTime::get_time_step());
		return;
	}

	auto& rigidbody_manager =
	    ResourceManager::get_instance().get_rigidbody_manager();

	float fixed_delta_time = EngineTime::get_fixed_delta_time();
	while (RigidbodyManager::accumulator(fixed_delta_time)) {
		fixed_delta_time = 0.0F;

		registry.view<Component::Rigidbody, Component::Transform>().each(
		    [&rigidbody_manager](auto& rigidbody, auto& transform) {
			    rigidbody_manager.update_rigidbody(rigidbody, transform);
		    });

		Physics::updateWorld(EngineTime::get_time_step());

		registry.view<Component::Rigidbody, Component::Transform>().each(
		    [](Component::Rigidbody& rigidbody,
		       Component::Transform& transform) {
			    if (rigidbody.pb->is_modified()) {
				    transform.position = rigidbody.getPosition();
				    transform.rotation = rigidbody.getRotation();
				    rigidbody.setPreviousPosition(transform.position);
				    rigidbody.pb->set_modified(false);
			    }
		    });
	}
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

#include "Controller/GUI/DebugLogger.hpp"
void System::update_script(entt::registry& registry) {
	auto& lua = LuaManager::get_instance().get_state();

	registry.view<Component::Script>().each([&lua](auto& script) {
		if (script.ecs && script.entity) {
			if (script.is_active) {
				lua.script_file(script.lua_script);
				auto update_func = lua["update"];
				lua["var"] = script.lua_variables;
				update_func(*script.ecs, *script.entity);
				script.lua_variables = lua["var"];
			}
		}
	});
}

void System::update_md2(entt::registry& registry) {
	registry.view<Component::Md2Animation>().each([](auto& md2) {
		if (md2.is_animation_done) return;

		md2.animstate.curr_time += EngineTime::get_delta_time();

		if (md2.animstate.curr_time - md2.animstate.prev_time >
		    (1.0 / md2.animstate.fps)) {
			md2.animstate.curr_frame = md2.animstate.next_frame;
			++md2.animstate.next_frame;

			if (md2.animstate.next_frame > md2.animstate.end_frame) {
				if (md2.is_loop) {
					md2.animstate.next_frame = md2.animstate.start_frame;
				} else {
					md2.is_animation_done = true;
					md2.animstate.next_frame = md2.animstate.end_frame;
				}
			}

			md2.animstate.prev_time = md2.animstate.curr_time;
		}

		md2.animstate.interpol = md2.animstate.fps * (md2.animstate.curr_time -
		                                              md2.animstate.prev_time);
	});
}

void System::update_remove(ECS& ecs) {
	for (auto entity : ecs.get_registry().view<Component::Remove>()) {
		ecs.destroy_entity(entity);
	}
}

void System::update_statemachine(ECS& ecs) {
	auto& lua = LuaManager::get_instance().get_state();
	sol::function exe;

	if (EngineTime::is_paused()) {
		return;
	}

	float time =
	    dataMgr.getDynamicFloatData("time_since_state_machine_last_update", 0);
	time += EngineTime::get_delta_time();

	if (time <
	    dataMgr.getDynamicFloatData("state_machine_update_delay", 1 / 20)) {
		return;
	}

	auto view = ecs.get_registry().view<Component::Statemachine>();

	for (auto entity : view) {
		auto& stateM = view.get<Component::Statemachine>(entity);

		if (!stateM.entity) continue;
		lua["var"] = stateM.lua_variables;

		// Global state update
		if (!stateM.global_state.empty()) {
			exe = lua[stateM.global_state]["execute"];
			exe(ecs, stateM.entity);
		}

		// Current state update
		if (!stateM.current_state.empty()) {
			exe = lua[stateM.current_state]["execute"];
			exe(ecs, stateM.entity);
		}

		stateM.lua_variables = lua["var"];
	}
}

void System::update_affordance_agent(ECS& ecs) {
	auto& registry = ecs.get_registry();
	auto& affordance_system = Affordance::AffordanceSystem::get_instance();

	registry.view<Component::Transform, Component::AffordanceAgent>().each(
	    [&](auto agent_id, auto& agent_transform, auto& agent) {
		    const auto& agent_entity = ecs.get_entity(agent_id);

		    // Updates the agent's utilities, can be anything from updating the
		    // agent's context, emotions or any component that is in the agent.
		    agent.utility.update_func(agent_entity);

		    // Evaluates the agent's utility and determines the best action, an
		    // affordance that the agent desires to interact in this case.
		    Affordance::evaluate_utility(agent_entity);

		    // Gets the best affordance.
		    const auto& agent_decision_properties =
		        agent.utility.states.at(agent.utility.decision).properties;

		    // Distance is used to the agent to choose the nearest affordance.
		    auto best_distance = std::numeric_limits<float>::max();

		    registry.view<Component::Transform, Component::Affordance>().each(
		        [&](auto affordance_id, auto& affordance_transform,
		            auto& affordance) {
			        auto affordance_tree = affordance_system.get_affordance(
			            affordance.object_name);

			        // If the affordance has the affordance that the agent
			        // desires
			        if (Affordance::has_affordance(affordance_tree,
			                                       agent_decision_properties)) {
				        auto distance =
				            glm::distance(agent_transform.position,
				                          affordance_transform.position);

				        // Determine if the affordance is the nearest affordance
				        if (distance < best_distance) {
					        best_distance = distance;
					        agent.affordance = affordance_id;
				        }
			        }
		        });

		    if (!ecs.get_registry().valid(agent.affordance)) {
			    return;
		    }

		    auto& affordance_entity = ecs.get_entity(agent.affordance);

		    const auto& affordance_component =
		        affordance_entity.get_component<Component::Affordance>();

		    auto affordance = affordance_system.get_affordance(
		        affordance_component.object_name);

		    // Find the affordance that the leaf that matches the agent's
		    // properties and property weights.
		    affordance = Affordance::find_affordance(
		        affordance, agent.properties, agent.property_weights);

		    // If it is not a composite affordance, then it is has an action
		    if (!affordance->is_composite()) {
			    auto affordance_leaf =
			        std::dynamic_pointer_cast<Affordance::AffordanceLeaf>(
			            affordance);

			    // Execute the affordance action.
			    affordance_leaf->get_function()(agent_entity,
			                                    affordance_entity);
		    }
	    });
}

void System::delete_directional_light(entt::registry& registry,
                                      entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	light_manager.delete_directional_light();
}

void System::delete_point_light(entt::registry& registry, entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& point_light = registry.get<Component::PointLight>(entity);

	light_manager.delete_point_light(point_light.light_id);
}

void System::delete_spot_light(entt::registry& registry, entt::entity entity) {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	auto& spot_light = registry.get<Component::SpotLight>(entity);

	light_manager.delete_spot_light(spot_light.light_id);
}

void System::delete_rigidbody(entt::registry& registry, entt::entity entity) {
	auto& rigidbody_manager =
	    ResourceManager::get_instance().get_rigidbody_manager();

	auto& rigidbody = registry.get<Component::Rigidbody>(entity);

	rigidbody_manager.delete_rigidbody(rigidbody);
}
