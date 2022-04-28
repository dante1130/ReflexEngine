#pragma once

#include <irrklang/irrKlang.h>
#include <unordered_map>

class Audio {
public:
	static Audio& get_instance();

	bool load_audio(const std::string& name, const std::string& path);

	void play_sound(const std::string& name, bool loop);

	~Audio();

private:
	Audio();

	void lua_access();

	irrklang::ISoundEngine* audio_engine;

	/// Unordered map with key of audio name
	std::unordered_map<std::string, irrklang::ISoundSource*> sound_map;
};