#pragma once

#include "singleton.h"
#include "entityManager.h"
#include "dynamicEnum.h"
#include "messageDispatcher.h"
#include "world.hpp"
#include "Counter.hpp"
#include "Controller/Physics/physicsEntityManager.h"

typedef singleton<dynamicEnum> message;
typedef singleton<entityManager> entityMan;
typedef singleton<messageDispatcher> messageMan;
typedef singleton<world> theWorld;
typedef singleton<Counter> idManager;
typedef singleton<physicsEntityManager> physicsEntityMan;

#define fsmMessage message::Instance()
#define entityMgr entityMan::Instance()
#define messageMgr messageMan::Instance()
#define gameWorld theWorld::Instance()
#define idMgr idManager::Instance()
#define physicsEntityMgr physicsEntityMan::Instance()
