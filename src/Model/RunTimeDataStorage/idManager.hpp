#pragma once

#include <Model/singleton.h>
#include "Controller/AI/Counter.hpp"

typedef singleton<Counter> idManager;

#define statemachineIDMgr idManager::Instance()
