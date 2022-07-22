#include "MaterialManager.hpp"

void MaterialManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto material_table = lua.create_named_table("Material");

	material_table.set_function("load_material",
	                            &MaterialManager::load_material, this);
}

bool MaterialManager::load_material(const std::string& material_name,
                                    float shine, float spec_intensity) {
	Reflex::Material* material = new Reflex::Material(shine, spec_intensity);

	if (material) {
		material_hashmap[material_name] = material;
		return true;
	}

	return false;
}

const Reflex::Material& MaterialManager::get_material(
    const std::string& material_name) const {
	return *material_hashmap.at(material_name);
}

MaterialManager::~MaterialManager() {
	for (auto& material : material_hashmap) {
		delete material.second;
	}
}
