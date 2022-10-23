#include "Emotion.hpp"

#include "Controller/LuaManager.hpp"

using namespace EmotionSystem;

Emotions::Emotions(float joy_sad, float tru_dis, float fea_ang, float sup_ant) {

}

auto Emotions::lua_access() -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto emotion_system = lua.create_named_table("EmotionSystem");

	emotion_system.set_function("set_emotion",
								&Emotions::set_emotion, this);
	emotion_system.set_function("get_emotion",
	                            &Emotions::get_emotion, this);
	emotion_system.set_function("set_current_emotion",
								&Emotions::set_current_emotion, this);
	emotion_system.set_function("get_emotional_state",
	                            &Emotions::get_emotional_state, this);

}

auto Emotions::get_emotion(Component::Agent agent) -> const std::string& { 
	return (agent.current_emotion);
}

auto Emotions::set_emotion(std::string emotion, float joy_sad, float tru_dis,
                           float fea_ang, float sup_ant) {
	emotion_state.insert(std::make_pair(
	    std::string(emotion), Component::mood(joy_sad, tru_dis, fea_ang, sup_ant)));
}

auto Emotions::set_current_emotion(std::string emotion) {

}

auto Emotions::get_emotional_state() -> const definedEmotions& {
	return (emotion_state);
}