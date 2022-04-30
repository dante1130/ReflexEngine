#include "Audio.hpp"

#include "Controller/LuaManager.hpp"

Audio& Audio::get_instance() {
	static Audio instance;
	return instance;
}

bool Audio::load_audio(const std::string& audio_name, const std::string& path) {
	irrklang::ISoundSource* sound_src =
	    audio_engine->addSoundSourceFromFile(path.c_str());

	if (!sound_src) return false;

	sound_map[audio_name] = sound_src;
	return true;
}

void Audio::play_sound(const std::string& audio_name, bool loop) {
	if (sound_map.find(audio_name) != sound_map.end()) {
		audio_engine->play2D(sound_map.at(audio_name), loop);
	}
}

Audio::~Audio() {
	if (audio_engine) {
		audio_engine->drop();
		audio_engine = nullptr;
	}
}

void Audio::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto audio = lua["Audio"].get_or_create<sol::table>();

	audio.set_function("load_audio", &Audio::load_audio, this);
	audio.set_function("play_sound", &Audio::play_sound, this);
}

Audio::Audio() {
	audio_engine = irrklang::createIrrKlangDevice();
	lua_access();
}
