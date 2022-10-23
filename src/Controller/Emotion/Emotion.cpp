#include "Emotion.hpp"

#include "Controller/LuaManager.hpp"

using namespace EmotionSystem;

auto Emotions::lua_access() -> void {

}

auto Emotions::get_emotion(Component::Agent agent) -> const std::string& { 
	return (agent.current_emotion); 
}

auto Emotions::set_emotion(std::string emotion,
                                definedEmotions emotionState) {

}

auto Emotions::set_current_emotion(std::string emotion) {

}

auto Emotions::get_emotional_state() -> const definedEmotions& {
	return (emotion_state);
}