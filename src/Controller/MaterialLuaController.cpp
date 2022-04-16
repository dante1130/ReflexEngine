#include "MaterialLuaController.hpp"

void MaterialLuaController::CreateLuaAccess() {
	sol::state& lua = LuaManager::get_instance().get_state();

	// Getting access to loading texture for texture manager
	lua.set_function("loadTextureRGBA", &TextureManager::load_texture_rgb,
	                 TextureManager());
	lua.set_function("loadTextureRGB", &TextureManager::load_texture_rgb,
	                 TextureManager());

	// Getting access to loading model for model manager
	//
	//
	//
	//
}
