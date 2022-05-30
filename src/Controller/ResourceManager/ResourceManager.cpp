#include "ResourceManager.hpp"

ResourceManager& ResourceManager::get_instance() {
	static ResourceManager instance;
	return instance;
}

ModelManager& ResourceManager::get_model_manager() { return model_manager_; }

Md2ModelManager& ResourceManager::get_md2_model_manager() {
	return md2_model_manager_;
}

TextureManager& ResourceManager::get_texture_manager() {
	return texture_manager_;
}

MaterialManager& ResourceManager::get_material_manager() {
	return material_manager_;
}

ResourceManager::ResourceManager() {
	texture_manager_.lua_access();
	model_manager_.lua_access();
	material_manager_.lua_access();
	md2_model_manager_.lua_access();
}
