#pragma once

#include "DynamicDataStorage.hpp"
#include "Controller/LuaManager.hpp"
#include "Model/singleton.h"

typedef singleton<DynamicDataStorage> dataMan;
#define dataMgr dataMan::Instance()

namespace GlobalDataStorage {
void lua_access();
};  // namespace GlobalDataStorage
