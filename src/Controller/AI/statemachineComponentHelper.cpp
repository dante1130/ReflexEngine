#include "statemachineComponentHelper.hpp"

#include <Controller/LuaManager.hpp>

#include "Model/Components/Statemachine.hpp"

void statemachineComponentHelper::change_state(ECS& ecs, Reflex::Entity& entity,
                                               std::string new_state) {
	auto& lua = LuaManager::get_instance().get_state();
	sol::function exe;

	auto stateMachine = entity.get_component<Component::Statemachine>();
	stateMachine.previous_state = stateMachine.current_state;
	stateMachine.current_state = new_state;

	exe = lua[stateMachine.previous_state]["exit"];
	exe(ecs, entity);

	exe = lua[stateMachine.current_state]["enter"];
	exe(ecs, entity);
}
