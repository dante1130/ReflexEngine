#include "Md2ModelManager.hpp"

#include "Controller/LuaManager.hpp"

void Md2ModelManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto md2 = lua["Md2Model"].get_or_create<sol::table>();

	md2.set_function("load_md2_model", &Md2ModelManager::load_md2_model, this);
}

bool Md2ModelManager::load_md2_model(const std::string& model_name,
                                     const std::string& file_name) {
	auto& md2_model = md2_model_hashmap[model_name];

	if (md2_model.load_md2(file_name)) {
		std::cout << "loading " << model_name << " from " << file_name
		          << std::endl;
		return true;
	}

	return false;
}

Md2Model& Md2ModelManager::get_md2_model(const std::string& model_name) {
	// Returns a reference instead of the pointer.
	return md2_model_hashmap[model_name];
}