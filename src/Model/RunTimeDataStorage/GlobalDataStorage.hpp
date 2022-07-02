#pragma once

#include "DynamicDataStorage.hpp"
#include "Controller/LuaManager.hpp"

namespace GlobalDataStorage {
void lua_access();
inline static DynamicDataStorage dds;
};  // namespace GlobalDataStorage
