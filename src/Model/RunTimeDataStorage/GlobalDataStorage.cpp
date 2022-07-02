#include "GlobalDataStorage.hpp"

void GlobalDataStorage::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("setBoolData", &DynamicDataStorage::setDynamicBoolData,
	                 &dds);
	lua.set_function("getBoolData", &DynamicDataStorage::getDynamicBoolData,
	                 &dds);

	lua.set_function("setIntData", &DynamicDataStorage::setDynamicIntData,
	                 &dds);
	lua.set_function("getIntData", &DynamicDataStorage::getDynamicIntData,
	                 &dds);

	lua.set_function("setFloatData", &DynamicDataStorage::setDynamicFloatData,
	                 &dds);
	lua.set_function("getFloatData", &DynamicDataStorage::getDynamicFloatData,
	                 &dds);
}
