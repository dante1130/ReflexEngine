#include "ScriptableObject.hpp"

ScriptableObject::ScriptableObject(std::string script) { scriptPath = script; }

void ScriptableObject::update(float delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(scriptPath);
}

void ScriptableObject::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle,
	                             "ScriptableObject");
	ObjectSaving::closeStruct();
	ObjectSaving::addValue("script", scriptPath, true);
	ObjectSaving::closeFile();
}
