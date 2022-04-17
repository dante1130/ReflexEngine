#pragma once

#include "LuaManager.hpp"
#include <time.h>
#include <random>

namespace GenericFunctions {
void lua_access();

void init_random(int seed, bool useSeed);
int get_random(int min, int max);
bool getIfSave();
void setIfSave(bool val);
bool getIfLoad();
void setIfLoad(bool val);

};  // namespace GenericFunctions
