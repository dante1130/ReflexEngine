#pragma once

#include <irrklang/irrKlang.h>

/**
 * @class AudioStopReceiver
 * @brief An event class to handle when a sound has stopped playing.
 */
class AudioStopReceiver : public irrklang::ISoundStopEventReceiver {
public:
	/**
	 * @brief On sound stop event.
	 *
	 * @param sound The sound.
	 * @param reason The reason the sound stopped.
	 * @param user_data Any additonal user data.
	 */
	virtual void OnSoundStopped(irrklang::ISound* sound,
	                            irrklang::E_STOP_EVENT_CAUSE reason,
	                            void* user_data) override;
};
