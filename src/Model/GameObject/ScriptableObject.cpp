#include "ScriptableObject.hpp"

ScriptableObject::ScriptableObject(const std::string& script) {
	scriptPath = script;
}

void ScriptableObject::update(double delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(scriptPath);
}

void ScriptableObject::save_object() {
	if (savable) {
		ObjectSaving::openFile();
		ObjectSaving::saveGameObject(position, rotation, scale, angle,
		                             "ScriptableObject", savable);
		ObjectSaving::closeStruct();
		ObjectSaving::addValue("script", scriptPath, true);
		ObjectSaving::closeFile();
	}
}
