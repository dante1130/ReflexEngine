#pragma once

#include <sol/sol.hpp>

/**
 * @class LuaManager
 * @brief A class to encapsulate a lua bind interface.
 */
class LuaManager {
public:
	/**
	 * @brief Get an isntance of the LuaManager
	 *
	 * @return LuaManager&
	 */
	static LuaManager& get_instance();

	/**
	 * @brief Get the lua state.
	 *
	 * @return sol::state&
	 */
	sol::state& get_state();

	// These are deleted as a singleton pattern is used.
	LuaManager(LuaManager& other) = delete;
	LuaManager(const LuaManager& other) = delete;
	void operator=(LuaManager&&) = delete;
	void operator=(const LuaManager&) = delete;

private:
	/// The lua state.
	sol::state lua;

	/**
	 * @brief Construct a new Lua Manager object
	 */
	LuaManager();
};
