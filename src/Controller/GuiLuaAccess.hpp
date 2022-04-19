#pragma once

#include "LuaManager.hpp"
#include "guiManager.hpp"

namespace guiLuaAccess {
/**
 * @brief	Gives lua access to gui related functions
 *
 * @pre		Nothing
 * @post	Lua has access to gui methods
 *
 */
void exposeGui();

}  // namespace guiLuaAccess
