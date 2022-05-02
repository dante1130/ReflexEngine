#pragma once

#include <irrklang/irrKlang.h>

class AudioStopReceiver : public irrklang::ISoundStopEventReceiver {
public:
	virtual void OnSoundStopped(irrklang::ISound* sound,
	                            irrklang::E_STOP_EVENT_CAUSE reason,
	                            void* user_data) override;
};
