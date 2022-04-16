#include "MaterialLuaController.hpp"

void MaterialLuaController::CreateLuaAccess() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto& texture_manager =
	    ResourceManager::get_instance().get_texture_manager();

	// Getting access to loading texture for texture manager
	lua.set_function("loadTextureRGBA", &TextureManager::load_texture_rgb,
	                 texture_manager);
	lua.set_function("loadTextureRGB", &TextureManager::load_texture_rgb,
	                 texture_manager);

	// Getting access to loading model for model manager
	//
	//
	//
	//
}
