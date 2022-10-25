#include "Emotion.hpp"

#include "Controller/LuaManager.hpp"

using namespace EmotionSystem;

auto Emotions::get_instance() -> Emotions& {
	static Emotions instance;
	return instance;
}

auto Emotions::lua_access() -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto emotion_system = lua.create_named_table("EmotionSystem");

	emotion_system.set_function("set_emotion",
								&Emotions::set_emotion, this);
	emotion_system.set_function("get_emotion",
	                            &AgentEmotions::get_emotion, this);
	emotion_system.set_function("set_current_emotion",
								&AgentEmotions::set_current_emotion, this);
	emotion_system.set_function("get_emotional_state",
	                            &AgentEmotions::get_emotional_state, this);

}

auto AgentEmotions::get_emotion(Component::Agent agent) -> const std::string& { 
	return (agent.current_emotion);
}

auto Emotions::set_emotion(std::string emotion, float joy_sad, float tru_dis,
                           float fea_ang, float sup_ant) {
	emotion_state.insert(std::make_pair(
	    std::string(emotion), Component::mood(joy_sad, tru_dis, fea_ang, sup_ant)));
}

auto Emotions::find_emotion(std::string emotion)
-> const Component::mood& {
	if (emotion_state.find(emotion) != emotion_state.end())
		return (emotion_state.find(emotion)->second);
	else
		return (Component::mood(-1.0f, -1.0f, -1.0f, -1.0f));
}

auto AgentEmotions::set_current_emotion(std::string emotion, Component::Agent agent) {
	Component::mood modifier = Emotions::get_instance().find_emotion(emotion);
	if (modifier.fear_anger > -1.0f && modifier.joy_sadness > -1.0f &&
	    modifier.surprise_anticipation > -1.0f &&
	    modifier.trust_disgust > -1.0f) 
	{
		agent.mood_state.fear_anger *= modifier.fear_anger;
		agent.mood_state.joy_sadness *= modifier.joy_sadness;
		agent.mood_state.surprise_anticipation *= modifier.surprise_anticipation;
		agent.mood_state.trust_disgust *= modifier.trust_disgust;
	}
}

auto AgentEmotions::get_emotional_state(Component::Agent agent){
	return (agent.mood_state);
}