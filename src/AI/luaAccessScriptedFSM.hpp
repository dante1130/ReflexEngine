#pragma once

namespace luaAccessScriptedFSM {
/*
 * @brief	registers All AI to lua. Only need to call this as it will call the
 * rest
 */
void registerAllAI();

/*
 * @brief	registers StateMachine to lua
 */
void registerScriptedStateMachine();

/*
 * @brief	registers GameObject to lua
 */
void registerGameObject();

/*
 * @brief	registers Player (NPC) to lua
 */
void registerPlayer();

/*
 * @brief	registers Vector2D (glm::vec2) to lua
 */
void registerVector2D();

/*
 * @brief	registers Message to lua
 */
void registerMessage();

/*
 * @brief	registers World to lua
 */
void registerWorld();

/*
 * @brief	registers Telegram to lua
 */
void registerTelegram();
}  // namespace luaAccessScriptedFSM

namespace registerAnimation {
/*
 * @brief	registers ModelData to lua
 */
void registerModelData();
}  // namespace registerAnimation
