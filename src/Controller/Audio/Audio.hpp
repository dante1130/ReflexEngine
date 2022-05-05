#pragma once

#include <irrklang/irrKlang.h>
#include <unordered_map>

#include "AudioStopReceiver.hpp"

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

	/**
	 * @brief Stops a sound given a name.
	 *
	 * @param name
	 */
	void stop_src(const std::string& name);

	/**
	 * @brief Stops all sounds being played.
	 */
	void stop_all();

	/**
	 * @brief Sets whether to pause sounds currently being played.
	 *
	 * @param is_pause
	 */
	void set_pause_all(bool is_pause);

	/**
	 * @brief Set whether the sound should loop.
	 *
	 * @param name
	 * @param loop
	 */
	void set_loop_sound(const std::string& name, bool loop);

	/**
	 * @brief Set the volume of the audio source.
	 *
	 * @param name
	 * @param volume
	 */
	void set_src_volume(const std::string& name, float volume);

	/**
	 * @brief Set the master volume.
	 *
	 * @param volume
	 */
	void set_master_volume(float volume);

	/**
	 * @brief Destroy the Audio object
	 */
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

	/// Audio stop event listener.
	AudioStopReceiver audio_stop_receiver;

	/// Unordered map with key of name and value of irrklang sound source.
	std::unordered_map<std::string, irrklang::ISoundSource*> sound_src_map;

	/// Unordered map with key of name and value of irrklang sound.
	std::unordered_map<std::string, irrklang::ISound*> sound_map;
};