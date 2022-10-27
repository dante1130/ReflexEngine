#include "Emotion.hpp"

#include "Controller/LuaManager.hpp"

using namespace Emotion;

auto EmotionSystem::get_instance() -> Emotion::EmotionSystem& {
	static EmotionSystem instance;
	return instance;
}

auto EmotionSystem::lua_access() -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto emotion_system = lua.create_named_table("EmotionSystem");

	emotion_system.set_function("add_emotion", &EmotionSystem::set_emotion,
	                            this);
}

auto EmotionSystem::set_emotion(std::string emotion, float joy_sad,
                                float tru_dis, float fea_ang, float sup_ant) {
	emotion_state[emotion] =
	    Emotion::emotion(joy_sad, tru_dis, fea_ang, sup_ant);
}

auto EmotionSystem::find_emotion(std::string emotion)
    -> const Emotion::emotion& {
	if (emotion_state.find(emotion) != emotion_state.end())
		return (emotion_state.find(emotion)->second);
	else
		return (Emotion::emotion(0.0f, 0.0f, 0.0f, 0.0f));
}
