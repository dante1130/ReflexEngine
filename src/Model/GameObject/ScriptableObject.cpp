#include "ScriptableObject.hpp"

ScriptableObject::ScriptableObject(const std::string& script) {
	scriptPath = script;
}

void ScriptableObject::update(double delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(scriptPath);

	std::cout << "Finished script: " << scriptPath << std::endl;
}

void ScriptableObject::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle,
	                             "ScriptableObject");
	ObjectSaving::closeStruct();
	ObjectSaving::addValue("script", scriptPath, true);
	ObjectSaving::closeFile();
}
