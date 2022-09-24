#include "ModelManager.hpp"
#include <thread>
#include <future>
//#include <mutex>

// Yeah, need to really sort this all out when I get it working... (also, TheDen model takes ~3 seconds to read)

void ModelManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::table model_table = lua.create_named_table("Model");
	//std::future<void> AsyncLoadModel = std::async(std::launch::async, &ModelManager::set_model_table, &model_table);
	
	std::future<void> AsyncLoadModel = std::async(std::launch::async, [&model_table, this]() {
		model_table.set_function("load_model", &ModelManager::load_model, this);
	});
	
	AsyncLoadModel.get();
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
	//model_table.set_function("load_model", &ModelManager::load_model, this);
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
	
	//std::thread ThreadLoadModel(&load_model_async);  //, &model, model_name, file_name);
	//std::future<bool> AsyncLoadModel = std::async(std::launch::async, load_model_async);  //, &model, model_name, file_name);
	/*
	auto& model = model_hashmap[model_name];
	if (model.LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}
	*/
	
	std::thread ThreadLoadModel([file_name, model_name, this](){
	//std::future<void> AsyncLoadModel = std::async(std::launch::async, [file_name, model_name, this]() {
		//locker.lock();
		auto& model = model_hashmap[model_name];
		file_hashmap[model_name] = file_name;
		if (model_hashmap[model_name].LoadModel(file_name)) {
			std::cout << "loading " << model_name << " from " << file_name
			          << std::endl;
			//locker.unlock();
			//return true;
		}
		//locker.unlock();
	});
	
	ThreadLoadModel.join();
	//AsyncLoadModel.get();
	//return AsyncLoadModel.get();
	
	return false;
	
	//return false;
}

bool ModelManager::load_model_async() {
	
	std::cout << "Running... " << model_hashmap.size() << std::endl;
	
	std::thread worker = std::thread([this]() {
		for (auto& ii : model_hashmap) {
			//auto& model_hsh = ii.second;
			std::string model_name = ii.first;
			std::string file_name = file_hashmap[ii.first];
			std::cout << file_name << std::endl;
			// Model model = model_hashmap[file_hashmap[ii.first]];
			auto& model = model_hashmap[model_name];
			if (model.LoadModel(file_name)) {
				std::cout << "loading " << model_name << " from "
				          << file_name << std::endl;
				//model = model_hashmap[model_name];
				// return true;
			}
			// return false;
		}
		// ThreadLoadModel.join();
	});
	worker.detach();
	/*Comment out here!!!!!<---
	for (auto& ii : model_hashmap) {
		auto& model_hsh = ii.second;
		std::string model_name = ii.first;
		std::future<void> AsyncLoadModel =
		    std::async(std::launch::deferred, [model_name, this]() {
			    if (model_hashmap[model_name].LoadModel(file_hashmap[model_name])) {
				    std::cout << "loading " << model_name << " from "
				              << file_hashmap[model_name] << std::endl;
				    // return true;
			    }
		    });
		AsyncLoadModel.get();
	}
	*/
	/*
	std::future<void> AsyncLoadModel =
	    std::async(std::launch::deferred, [this]() {
		    for (auto& ii : model_hashmap) {
			    auto& model_hsh = ii.second;
			    std::string model_name = ii.first;
			    if (model_hashmap[model_name].LoadModel(
			            file_hashmap[model_name])) {
				    std::cout << "loading " << model_name << " from "
				              << file_hashmap[model_name] << std::endl;
				    // return true;
			    }
		    }
	    });
	std::future<void> ThreadLoadModel = std::async(std::launch::deferred, [&AsyncLoadModel, this] { AsyncLoadModel.get();
		});
	ThreadLoadModel.get();
	//AsyncLoadModel.get();
	/*
	if (model->LoadModel(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}
	
	
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
	*/
	return true;
}

Model& ModelManager::get_model(const std::string& model_name) {
	return model_hashmap[model_name];
}
