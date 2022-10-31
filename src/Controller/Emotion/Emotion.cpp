#include "Emotion.hpp"

#include "Controller/LuaManager.hpp"

using namespace Emotion;

auto EmotionSystem::get_instance() -> EmotionSystem& {
	static EmotionSystem instance;
	return instance;
}

auto EmotionSystem::lua_access() -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto emotion_system = lua.create_named_table("EmotionSystem");

	emotion_system.set_function("set_emotion", &EmotionSystem::set_emotion,
	                            this);

	lua.new_usertype<EmotionState>(
	    "EmotionState",
	    sol::constructors<EmotionState(), EmotionState(float, float)>(),
	    "arousal", &EmotionState::arousal, "valence", &EmotionState::valence);
}

auto EmotionSystem::set_emotion(const std::string& emotion_name,
                                const EmotionState& emotion) -> void {
	emotion_state.emplace(emotion_name, emotion);
}

auto EmotionSystem::find_emotion(const std::string& emotion_name)
    -> EmotionState {
	if (emotion_state.find(emotion_name) != emotion_state.end()) {
		return emotion_state.at(emotion_name);
	}

	return {};
}
