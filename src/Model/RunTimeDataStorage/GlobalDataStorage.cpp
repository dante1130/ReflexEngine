#include "GlobalDataStorage.hpp"

void GlobalDataStorage::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("setBoolData", &DynamicDataStorage::setDynamicBoolData,
	                 &dataMgr);
	lua.set_function("getBoolData", &DynamicDataStorage::getDynamicBoolData,
	                 &dataMgr);

	lua.set_function("setIntData", &DynamicDataStorage::setDynamicIntData,
	                 &dataMgr);
	lua.set_function("getIntData", &DynamicDataStorage::getDynamicIntData,
	                 &dataMgr);

	lua.set_function("setFloatData", &DynamicDataStorage::setDynamicFloatData,
	                 &dataMgr);
	lua.set_function("getFloatData", &DynamicDataStorage::getDynamicFloatData,
	                 &dataMgr);
}
