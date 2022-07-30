#include "MaterialManager.hpp"

void MaterialManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto material_table = lua.create_named_table("Material");

	material_table.set_function("load_material",
	                            &MaterialManager::load_material, this);
}

void MaterialManager::load_material(const std::string& material_name,
                                    float shine, float spec_intensity) {
	material_hashmap[material_name] = Reflex::Material(shine, spec_intensity);
}

Reflex::Material& MaterialManager::get_material(
    const std::string& material_name) {
	return material_hashmap[material_name];
}