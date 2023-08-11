#pragma once

#include "singleton.h"
#include "Controller/Pathfinding/world.hpp"
#include "Controller/AI/Counter.hpp"

#include <unordered_map>
#include <string>

typedef singleton<world> theWorld;
typedef singleton<Counter> idManager;
typedef singleton<std::unordered_map<std::string, world>> theWorlds;

#define gameWorld theWorld::Instance()
#define idMgr idManager::Instance()
#define gameWorlds theWorlds::Instance()
