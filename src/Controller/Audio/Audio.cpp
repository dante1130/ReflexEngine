#include "Audio.hpp"

Audio& Audio::get_instance() {
	static Audio instance;
	return instance;
}

bool Audio::load_audio(const std::string& audio_name, const std::string& path) {
	sound_map[audio_name] = audio_engine->addSoundSourceFromFile(path.c_str());
}

void Audio::play_sound(const std::string& audio_name, bool loop) {
	audio_engine->play2D(sound_map[audio_name], loop);
}

Audio::~Audio() {
	if (audio_engine) {
		audio_engine->drop();
		audio_engine = nullptr;
	}

	for (auto& sound : sound_map) {
		sound.second->drop();
		sound.second = nullptr;
	}
}

Audio::Audio() { audio_engine = irrklang::createIrrKlangDevice(); }
