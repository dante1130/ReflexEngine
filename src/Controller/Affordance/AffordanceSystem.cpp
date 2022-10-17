#include "AffordanceSystem.hpp"

#include "Controller/LuaManager.hpp"

using namespace Affordance;

auto AffordanceSystem::get_instance() -> AffordanceSystem& {
	static AffordanceSystem instance;
	return instance;
}

auto AffordanceSystem::lua_access() -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto affordance_system = lua.create_named_table("AffordanceSystem");

	affordance_system.set_function("add_affordance",
	                               &AffordanceSystem::add_affordance, this);
	affordance_system.set_function("get_affordance",
	                               &AffordanceSystem::get_affordance, this);
}

auto AffordanceSystem::add_affordance(std::string object,
                                      AffordancePtr affordance) -> void {
	affordance_map_.emplace(std::move(object), std::move(affordance));
}

auto AffordanceSystem::get_affordance(const std::string& object)
    -> AffordancePtr {
	return affordance_map_.at(object);
}
