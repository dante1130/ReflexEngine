#include "Md2ModelManager.hpp"

#include "Controller/LuaManager.hpp"

void Md2ModelManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto md2 = lua["Md2Model"].get_or_create<sol::table>();

	md2.set_function("load_md2_model", &Md2ModelManager::load_md2_model, this);
	md2.set_function("load_texture", &Md2ModelManager::load_texture, this);
}

bool Md2ModelManager::load_md2_model(const std::string& model_name,
                                     const std::string& file_name) {
	Md2Model* md2_model = new Md2Model();

	if (md2_model->load_md2(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		md2_model_hashmap[model_name] = md2_model;
		return true;
	}

	return false;
}

bool Md2ModelManager::load_texture(const std::string& model_name,
                                   const std::string& file_name) {
	Md2Model* md2_model = md2_model_hashmap.at(model_name);
	return md2_model->load_texture(file_name);
}

Md2Model& Md2ModelManager::get_md2_model(const std::string& model_name) {
	// Returns a reference instead of the pointer.
	return *md2_model_hashmap.at(model_name);
}

const Md2Model& Md2ModelManager::get_md2_model(
    const std::string& model_name) const {
	// Returns a reference instead of the pointer.
	return *md2_model_hashmap.at(model_name);
}

Md2ModelManager::~Md2ModelManager() {
	for (auto& md2_model : md2_model_hashmap) {
		delete md2_model.second;
	}
}
