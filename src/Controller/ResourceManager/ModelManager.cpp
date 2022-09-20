#include "ModelManager.hpp"
#include <thread>
#include <future>

void ModelManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto model_table = lua.create_named_table("Model");
	model_table.set_function("load_model", &ModelManager::load_model, this);
}

bool ModelManager::load_model(const std::string& model_name,
                              const std::string& file_name) {
	auto& model = model_hashmap[model_name];
	//std::thread ThreadLoadModel(&load_model_async, &model, model_name, file_name);
	std::future<bool> AsyncLoadModel = std::async(std::launch::async, load_model_async, &model, model_name, file_name);
	/*
	if (model.LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}
	*/
	//ThreadLoadModel.join();
	return AsyncLoadModel.get();

	//return false;
}

bool ModelManager::load_model_async(Model* model, std::string model_name, std::string file_name) {
	std::cout << "Running..." << std::endl;
	if (model->LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}
	return false;
}

Model& ModelManager::get_model(const std::string& model_name) {
	return model_hashmap[model_name];
}
