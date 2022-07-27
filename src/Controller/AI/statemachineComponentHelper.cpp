#include "statemachineComponentHelper.hpp"

#include <Controller/LuaManager.hpp>

#include "Model/Components/Statemachine.hpp"

void statemachineComponentHelper::change_state(entt::registry& registry,
                                               Reflex::Entity& entity,
                                               std::string new_state) {
	auto& lua = LuaManager::get_instance().get_state();
	sol::function exe;

	Component::Statemachine& stateMachine =
	    entity.get_component<Component::Statemachine>();
	stateMachine.previous_state = stateMachine.current_state;
	stateMachine.current_state = new_state;

	exe = lua[stateMachine.previous_state]["exit"];
	exe(registry, entity);

	exe = lua[stateMachine.current_state]["enter"];
	exe(registry, entity);
}
