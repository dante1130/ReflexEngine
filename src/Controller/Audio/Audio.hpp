#pragma once

#include <irrklang/irrKlang.h>
#include <unordered_map>

/**
 * @class Audio
 * @brief Singleton audio class that facades the irrklang audio library.
 */
class Audio {
public:
	/**
	 * @brief Get the instance of the Audio class.
	 *
	 * @return Audio&
	 */
	static Audio& get_instance();

	/**
	 * @brief Loads a sound filepath with a given name to the audio engine.
	 *
	 * @param name
	 * @param path
	 * @return true
	 * @return false
	 */
	bool load_audio(const std::string& name, const std::string& path);

	/**
	 * @brief Plays a sound given a name.
	 *
	 * @param name
	 * @param loop
	 */
	void play_sound(const std::string& name, bool loop);

	~Audio();

private:
	/**
	 * @brief Construct a new Audio object.
	 */
	Audio();

	/**
	 * @brief Exposes the audio class to lua.
	 */
	void lua_access();

	/// The irrklang sound engine.
	irrklang::ISoundEngine* audio_engine;

	/// Unordered map with key of audio name
	std::unordered_map<std::string, irrklang::ISoundSource*> sound_map;
};