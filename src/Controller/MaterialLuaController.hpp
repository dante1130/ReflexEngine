#pragma once

#include "LuaManager.hpp"

#include "ResourceManager/ResourceManager.hpp"
//#include "ModelManager.hpp"

namespace MaterialLuaController {
/**
 * @brief	Gives lua access to material related functions (texture & model
 * managers)
 * @param	No param
 * @return	Void
 *
 * @pre		Nothing
 * @post	Lua has access to material methods
 *
 */
void CreateLuaAccess();
}  // namespace MaterialLuaController
