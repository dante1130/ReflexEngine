#pragma once

#include "singleton.h"
#include "Controller/AI/entityManager.h"
#include "Controller/AI/messageDispatcher.h"
#include "Controller/Pathfinding/world.hpp"
#include "Controller/AI/Counter.hpp"

typedef singleton<entityManager> entityMan;
typedef singleton<messageDispatcher> messageMan;
typedef singleton<world> theWorld;
typedef singleton<Counter> idManager;

#define entityMgr entityMan::Instance()
#define messageMgr messageMan::Instance()
#define gameWorld theWorld::Instance()
#define idMgr idManager::Instance()
