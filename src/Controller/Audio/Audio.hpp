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
	 * @brief Loads a sound filepath with a given name to the audio engine. Will
	 * return false if the file cannot be loaded.
	 *
	 * @param name The name to be given to the sound.
	 * @param path The path to the sound file.
	 * @return bool
	 */
	bool load_audio(const std::string& name, const std::string& path);

	/**
	 * @brief Plays a sound given a name.
	 *
	 * @param name The name given to the sound.
	 * @param loop Whether the sound should loop or not.
	 */
	void play_sound(const std::string& name, bool loop);

	/**
	 * @brief Plays a sound given a name and position.
	 *
	 * @param name The name given to the sound.
	 * @param pos The position to play the sound at.
	 * @param loop Whether the sound should loop or not.
	 * @param min_dist The minimum distance to play the sound at.
	 */
	void play_3d_sound(const std::string& name, const irrklang::vec3df& pos,
	                   bool loop, float min_dist);

	/**
	 * @brief Updates the listener for 3D sound. This should be called at a game
	 * tick or every frame.
	 */
	void update_listener();

	/**
	 * @brief Stops a sound given a name.
	 *
	 * @param name The name given to the sound.
	 */
	void stop_src(const std::string& name);

	/**
	 * @brief Stops all sounds being played.
	 */
	void stop_all();

	/**
	 * @brief Sets whether to pause sounds currently being played.
	 *
	 * @param is_pause Whether to pause sounds or not.
	 */
	void set_pause_all(bool is_pause);

	/**
	 * @brief Set whether the sound being played should loop.
	 *
	 * @param name The name given to the sound being played.
	 * @param loop Whether the sound should loop or not.
	 */
	void set_loop_sound(const std::string& name, bool loop);

	/**
	 * @brief Set the volume of the sound source.
	 *
	 * @param name The name given to the sound source.
	 * @param volume The volume to set the sound source to.
	 */
	void set_src_volume(const std::string& name, float volume);

	/**
	 * @brief Set the master volume.
	 *
	 * @param volume The volume to set the master volume to.
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

	/**
	 * @brief Adds a sound to the sound map and the stop event listener.
	 *
	 * @param name The name given to the sound.
	 * @param src The sound.
	 */
	void add_sound(const std::string& name, irrklang::ISound* sound);

	/// The irrklang sound engine.
	irrklang::ISoundEngine* audio_engine;

	/// Audio stop event listener.
	AudioStopReceiver audio_stop_receiver;

	/// Unordered map with key of name and value of irrklang sound source.
	std::unordered_map<std::string, irrklang::ISoundSource*> sound_src_map;

	/// Unordered map with key of name and value of irrklang sound.
	std::unordered_map<std::string, irrklang::ISound*> sound_map;
};