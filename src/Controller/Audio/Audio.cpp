#include "Audio.hpp"

#include "Controller/LuaManager.hpp"

Audio& Audio::get_instance() {
	static Audio instance;
	return instance;
}

bool Audio::load_audio(const std::string& name, const std::string& path) {
	auto* sound_src = audio_engine->addSoundSourceFromFile(path.c_str());

	if (!sound_src) return false;

	sound_src_map[name] = sound_src;
	return true;
}

void Audio::play_sound(const std::string& name, bool loop) {
	if (sound_src_map.find(name) != sound_src_map.end()) {
		auto* sound = audio_engine->play2D(sound_src_map.at(name), loop, false,
		                                   true, true);

		if (!sound) return;

		sound_map[name] = sound;
		sound->setSoundStopEventReceiver(&audio_stop_receiver, &sound_map);
	}
}

void Audio::stop_src(const std::string& name) {
	if (sound_src_map.find(name) != sound_src_map.end()) {
		audio_engine->stopAllSoundsOfSoundSource(sound_src_map.at(name));
	}
}

void Audio::stop_all() { audio_engine->stopAllSounds(); }

void Audio::set_pause_all(bool is_pause) {
	audio_engine->setAllSoundsPaused(is_pause);
}

void Audio::set_loop_sound(const std::string& name, bool loop) {
	if (sound_map.find(name) != sound_map.end()) {
		sound_map.at(name)->setIsLooped(loop);
	}
}

void Audio::set_src_volume(const std::string& name, float volume) {
	if (sound_src_map.find(name) != sound_src_map.end()) {
		volume = std::clamp(volume, 0.0f, 1.0f);
		sound_src_map.at(name)->setDefaultVolume(volume);
	}
}

void Audio::set_master_volume(float volume) {
	volume = std::clamp(volume, 0.0f, 1.0f);
	audio_engine->setSoundVolume(volume);
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
	audio.set_function("stop_src", &Audio::stop_src, this);
	audio.set_function("stop_all", &Audio::stop_all, this);
	audio.set_function("set_pause_all", &Audio::set_pause_all, this);
	audio.set_function("set_loop_sound", &Audio::set_loop_sound, this);
	audio.set_function("set_src_volume", &Audio::set_src_volume, this);
	audio.set_function("set_master_volume", &Audio::set_master_volume, this);
}

Audio::Audio() {
	audio_engine = irrklang::createIrrKlangDevice();
	lua_access();
}
