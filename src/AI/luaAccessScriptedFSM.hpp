#pragma once

#include <sol/sol.hpp>
#include "AI/NPC.hpp"
#include "AI/stateMachine.h"
#include "AI/messageDispatcher.h"
#include "AI/telegram.h"
#include <glm/glm.hpp>
#include "Model/ModelData.hpp"

namespace luaAccessScriptedFSM {
void registerAllAI();
void registerScriptedStateMachine();
void registerGameObject();
void registerPlayer();
void registerVector2D();
void registerMessage();
void registerTelegram();
}  // namespace luaAccessScriptedFSM

namespace registerAnimation {
void registerModelData();
}
