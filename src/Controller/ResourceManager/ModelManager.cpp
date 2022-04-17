#include "ModelManager.hpp"

void ModelManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("loadModel", &ModelManager::load_model, this);
}

bool ModelManager::load_model(const std::string& model_name,
                              const std::string& file_name) {
	Model* model = new Model();

	if (model->LoadModel(file_name)) {
		model_hashmap[model_name] = model;
		return true;
	}

	return false;
}

const Model& ModelManager::get_model(const std::string& model_name) const {
	// Returns a reference instead of the pointer.
	return *model_hashmap.at(model_name);
}

ModelManager::~ModelManager() {
	for (auto& model : model_hashmap) {
		delete model.second;
	}
}
