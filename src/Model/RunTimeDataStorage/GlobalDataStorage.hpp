#pragma once

#include "DynamicDataStorage.hpp"
#include "Controller/LuaManager.hpp"
#include "Model/singleton.h"

typedef singleton<DynamicDataStorage> dataMan;
#define dataMgr dataMan::Instance()

/**
 * @author Daniel Rodic
 * @brief Creates a dynamic data storage variables and provides it access to lua
 * to modify key variables for engine functionality which is provided
 *
 */
namespace GlobalDataStorage {
void lua_access();
};  // namespace GlobalDataStorage
