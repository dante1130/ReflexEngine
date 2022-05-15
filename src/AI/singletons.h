#ifndef __SINGLETONS_H
#define __SINGLETONS_H

#include "singleton.h"
#include "entityManager.h"
#include "dynamicEnum.h"
#include "messageDispatcher.h"
//#include "world.h"

typedef singleton<dynamicEnum> message;
typedef singleton<entityManager> entityMan;
typedef singleton<messageDispatcher> messageMan;
// typedef singleton<world> theWorld;

#define fsmMessage message::Instance()
#define entityMgr entityMan::Instance()
#define messageMgr messageMan::Instance()
//#define gameWorld theWorld::Instance()

#endif
