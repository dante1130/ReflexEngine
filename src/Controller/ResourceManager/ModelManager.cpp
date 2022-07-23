#include "ModelManager.hpp"

void ModelManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto model_table = lua.create_named_table("Model");

	model_table.set_function("load_model", &ModelManager::load_model, this);
}

bool ModelManager::load_model(const std::string& model_name,
                              const std::string& file_name) {
	auto& model = model_hashmap[model_name];

	if (model.LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}

	return false;
}

const Model& ModelManager::get_model(const std::string& model_name) const {
	// Returns a reference instead of the pointer.
	return model_hashmap.at(model_name);
}
