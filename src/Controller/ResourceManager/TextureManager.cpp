#include "TextureManager.hpp"

#include "Controller/LuaManager.hpp"

void TextureManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("loadTextureRGB", &TextureManager::load_texture_rgb, this);
	lua.set_function("loadTextureRGBA", &TextureManager::load_texture_rgba,
	                 this);
}

bool TextureManager::load_texture_rgb(const std::string& texture_name,
                                      const std::string& file_path) {
	Texture* texture = new Texture(file_path.c_str());

	if (texture->LoadTexture()) {
		std::cout << "loading " << texture_name << " from " << file_path
		          << std::endl;
		texture_hashmap[texture_name] = texture;
		return true;
	}

	return false;
}

bool TextureManager::load_texture_rgba(const std::string& texture_name,
                                       const std::string& file_path) {
	Texture* texture = new Texture(file_path.c_str());

	if (texture->LoadTextureA()) {
		texture_hashmap[texture_name] = texture;
		return true;
	}

	return false;
}

const Texture& TextureManager::get_texture(
    const std::string& texture_name) const {
	// Returns a reference instead of the pointer.
	return *texture_hashmap.at(texture_name);
}

TextureManager::~TextureManager() {
	for (auto& texture : texture_hashmap) {
		delete texture.second;
	}
}
