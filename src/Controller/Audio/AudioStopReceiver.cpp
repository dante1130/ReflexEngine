#include "AudioStopReceiver.hpp"

#include <iostream>
#include <unordered_map>

using SoundMap = std::unordered_map<std::string, irrklang::ISound*>;

void AudioStopReceiver::OnSoundStopped(irrklang::ISound* sound,
                                       irrklang::E_STOP_EVENT_CAUSE reason,
                                       void* user_data) {
	auto* sound_map = static_cast<SoundMap*>(user_data);

	for (auto& sound_pair : *sound_map) {
		if (sound_pair.second == sound) {
			sound_map->erase(sound_pair.first);

			sound->drop();
			sound = nullptr;
			break;
		}
	}
}
