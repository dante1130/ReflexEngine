#include "MaterialLuaController.hpp"

void MaterialLuaController::CreateLuaAccess() {
	sol::state& lua = LuaManager::get_instance().get_state();

	// Getting access to loading texture for texture manager
	TextureManager& texture_manager =
	    ResourceManager::get_instance().get_texture_manager();

	lua.set_function("loadTextureRGBA", &TextureManager::load_texture_rgba,
	                 texture_manager);
	lua.set_function("loadTextureRGB", &TextureManager::load_texture_rgb,
	                 texture_manager);

	// Getting access to loading model for model manager
	ModelManager& model_manager =
	    ResourceManager::get_instance().get_model_manager();

	lua.set_function("loadModel", &ModelManager::load_model, model_manager);
}
