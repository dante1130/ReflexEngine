#include <catch2/catch_test_macros.hpp>

#include "Controller/LuaManager.hpp"
#include "Controller/Emotion/Emotion.hpp"
#include "Model/Components/Agent.hpp"

/* TO TEST:
* Creating an emotion
* Creating an agent
* Applying an emotion to an agent
* Getting an agent's current emotion
* Getting an agent's mood state
*/

TEST_CASE("Emotion system tests", "[EmotionSystem]") {
	auto& emotion_system = EmotionSystem::Emotions::get_instance();
	emotion_system.lua_access();

	SECTION("Adding an emotion to the definedEmotions map") {
		auto& lua = LuaManager::get_instance().get_state();

		sol::optional<sol::error> error_case = lua.safe_script(R"(
		emotionSystem = add_emotion("RAGE",0.0f,0.0f,0.2f,0.0f)
		)", 
				sol::script_pass_on_error);

		if (error_case) {
			FAIL(error_case.value().what());
		}
		
		std::shared_ptr<EmotionSystem::Emotions> emotion = lua["emotionSystem"];

		Component::mood emotion = emotion->find_emotion("RAGE");

		REQUIRE(emotion->find_emotion("RAGE").joy_sadness == 0.0f);
		REQUIRE(emotion->find_emotion("RAGE").trust_disgust == 0.0f);
		REQUIRE(emotion->find_emotion("RAGE").fear_anger == 0.2f);
		REQUIRE(emotion->find_emotion("RAGE").surprise_anticipation == 0.0f);
	}
	SECTION("Creating an agent") {

	}
	SECTION("Applying an emotion to an agent") {

	}
	SECTION("Getting an agent's current emotion") {

	}
	SECTION("Getting an agent's mood state") {

	}
}