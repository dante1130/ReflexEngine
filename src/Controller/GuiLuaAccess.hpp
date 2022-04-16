#pragma once

#include "LuaManager.hpp"
#include "guiManager.hpp"

namespace guiLuaAccess {
/**
 * @brief	Gives lua access to gui related functions
 * @param	No param
 * @return	Void
 *
 * @pre		Nothing
 * @post	Lua has access to gui methods
 *
 */
void exposeGui();
}  // namespace guiLuaAccess
