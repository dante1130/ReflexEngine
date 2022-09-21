#include "ModelManager.hpp"
#include <thread>
#include <future>

// Yeah, need to really sort this all out when I get it working... (also, TheDen model takes ~3 seconds to read)

void ModelManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::table model_table = lua.create_named_table("Model");
	//std::future<void> AsyncLoadModel = std::async(std::launch::async, &ModelManager::set_model_table, &model_table);
	/*
	std::future<void> AsyncLoadModel = std::async(std::launch::async, [&model_table, this]() {
		model_table.set_function("load_model", &ModelManager::load_model, this);
	});
	*/
	/*
	std::thread ThreadLoadModel([&model_table, this]() {
		model_table.set_function("load_model", &ModelManager::load_model, this);
	});
	ThreadLoadModel.join();
	*/
	//auto handle = std::async(std::launch::async, ModelManager::set_model_table, model_table);
	//ModelManager modelmngr;
	//std::thread ThreadLoadModel(&ModelManager::set_model_table, &model_table);
	//ThreadLoadModel.join();
	model_table.set_function("load_model", &ModelManager::load_model, this);
	model_table.set_function("finished_loading", &ModelManager::load_model_async, this);
}


void ModelManager::workaround(int index) {
	std::cout << "Winning!" << std::endl;
	/*
	auto& model = model_hashmap[index];
	if (model->LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
	}
	*/
	
}

void ModelManager::set_model_table(sol::table *model_table) {
	model_table->set_function("load_model", &ModelManager::load_model, this);
}

bool ModelManager::load_model(const std::string& model_name,
                              const std::string& file_name) {
	auto& model = model_hashmap[model_name];
	auto& file = file_hashmap[model_name] = file_name;
	//std::thread ThreadLoadModel(&load_model_async, &model, model_name, file_name);
	//std::future<bool> AsyncLoadModel = std::async(std::launch::async, load_model_async, &model, model_name, file_name);
	/*
	if (model.LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}
	/*
	
	std::thread ThreadLoadModel([&model, file_name, model_name](){
	//std::future<bool> AsyncLoadModel = std::async(std::launch::deferred, [&model, file_name, model_name]() {
		if (model.LoadModel(file_name)) {
			std::cout << "loading " << model_name << " from " << file_name
			          << std::endl;
			return true;
		}
	});
	*/
	//ThreadLoadModel.join();
	//return AsyncLoadModel.get();
	return true;
	//return false;
}

bool ModelManager::load_model_async() {
	/*
	std::cout << "Running... " << model_hashmap.size() << std::endl;
	std::vector<std::thread> workers;
	for (auto& ii : model_hashmap) {
		//auto& model = ii.second;
		std::string file_name = file_hashmap[ii.first];
		workers.push_back(std::thread([file_name, &ii, this]() {
			auto& model = ii.second;  // model_hashmap[ii.first];
			if (model.LoadModel(file_name)) {
				std::cout << "loading " << ii.first << " from " << file_name
				          << std::endl;
				//model_hashmap[ii.first] = model;
				//return true;
			}
			//return false;
		}));	
		//ThreadLoadModel.join();
	}
	for (auto jj = workers.begin(), end = workers.end(); jj != end; ++jj) {
		std::thread th = std::move(*jj);
		th.join();
	}
	/*
	if (model->LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}
	*/

	for (auto& ii : model_hashmap) {
		// auto& model = ii.second;
		std::string file_name = file_hashmap[ii.first];
		auto& model = ii.second;  // model_hashmap[ii.first];
		if (model.LoadModel(file_name)) {
			std::cout << "loading " << ii.first << " from " << file_name
				        << std::endl;
			// model_hashmap[ii.first] = model;
			// return true;
		}
		// ThreadLoadModel.join();
	}
	return true;
}

Model& ModelManager::get_model(const std::string& model_name) {
	return model_hashmap[model_name];
}
