#include <catch2/catch_test_macros.hpp>

#include "Controller/LuaManager.hpp"
#include "Controller/Emotion/Emotion.hpp"

/* TO TEST:
 * Creating an emotion
 * Creating an agent
 * Applying an emotion to an agent
 * Getting an agent's current emotion
 * Getting an agent's mood state
 */

TEST_CASE("Emotion system tests", "[EmotionSystem]") {
	auto& emotion_system = Emotion::EmotionSystem::get_instance();
	emotion_system.lua_access();

	SECTION("Adding an emotion to the DefinedEmotions map") {
		auto& lua = LuaManager::get_instance().get_state();

		sol::optional<sol::error> error_case =
		    lua.safe_script(R"(
		EmotionSystem.set_emotion("RAGE", EmotionState.new(0.0, 0.0, 0.2, 0.0))
		)",
		                    sol::script_pass_on_error);

		if (error_case) {
			FAIL(error_case.value().what());
		}

		Emotion::EmotionState rage_emotion =
		    emotion_system.find_emotion("RAGE");

		REQUIRE(rage_emotion.joy_sadness == 0.0F);
		REQUIRE(rage_emotion.trust_disgust == 0.0F);
		REQUIRE(rage_emotion.fear_anger == 0.2F);
		REQUIRE(rage_emotion.surprise_anticipation == 0.0F);
	}
	SECTION("Creating an agent") {}
	SECTION("Applying an emotion to an agent") {}
	SECTION("Getting an agent's current emotion") {}
	SECTION("Getting an agent's mood state") {}
}