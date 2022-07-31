#include "TextureManager.hpp"

#include "Controller/LuaManager.hpp"

void TextureManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	auto texture_table = lua.create_named_table("Texture");

	texture_table.set_function("load_texture", &TextureManager::load_texture,
	                           this);
}

bool TextureManager::load_texture(const std::string& texture_name,
                                  const std::string& file_path) {
	auto& texture = texture_hashmap[texture_name] = Texture(file_path.c_str());

	if (texture.LoadTexture()) {
		std::cout << "loading " << texture_name << " from " << file_path
		          << std::endl;
		return true;
	}

	return false;
}

bool TextureManager::load_texture_rgba(const std::string& texture_name,
                                       const std::string& file_path) {
	auto& texture = texture_hashmap[texture_name] = Texture(file_path.c_str());

	if (texture.LoadTextureA()) {
		return true;
	}

	return false;
}

Texture& TextureManager::get_texture(const std::string& texture_name) {
	// Returns a reference instead of the pointer.
	return texture_hashmap[texture_name];
}
