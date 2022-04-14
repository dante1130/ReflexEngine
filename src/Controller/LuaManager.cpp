#include "LuaManager.hpp"

LuaManager& LuaManager::get_instance() {
	static LuaManager instance;
	return instance;
}

sol::state& LuaManager::get_state() { return lua; }

LuaManager::LuaManager() { lua.open_libraries(sol::lib::base); }
