#include "ScriptableObject.hpp"

ScriptableObject::ScriptableObject(std::string script) { scriptPath = script; }

void ScriptableObject::update(float delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(scriptPath);
}
