#pragma once

#include <string>
#include <unordered_set>

#include <sol/sol.hpp>

namespace Affordance {
using Properties = std::unordered_set<std::string>;
using AffordancePtr = std::shared_ptr<class Affordance>;

/**
 * @class Affordance
 * @brief An affordance is a base composite class that can be used to create a
 * hierarchy of affordances. It is used to represent the properties of an
 * object.
 */
class Affordance {
public:
	Affordance() = default;
	explicit Affordance(const std::string& name);

	/**
	 * @brief Returns whether the affordance is a composite and has children.
	 *
	 * @return true The affordance is a composite.
	 * @return false The affordance is not a composite.
	 */
	virtual auto is_composite() const -> bool = 0;

	/**
	 * @brief Expose the Affordance class to Lua.
	 */
	virtual auto lua_access() -> void;

	/**
	 * @brief Get the name of the affordance.
	 *
	 * @return const std::string&
	 */
	auto get_name() -> const std::string&;

	/**
	 * @brief Get the properties of the affordance.
	 *
	 * @return const Properties&
	 */
	auto get_properties() -> const Properties&;

	/**
	 * @brief Set the name.
	 *
	 * @param name The name of the affordance.
	 */
	auto set_name(const std::string& name) -> void;

	/**
	 * @brief Set the properties.
	 *
	 * @param properties The properties of the affordance.
	 */
	auto set_properties(const Properties& properties) -> void;

private:
	/// The name of the affordance.
	std::string name_;
	/// The properties of the affordance.
	Properties properties_;
};

class AffordanceLeaf : Affordance {
public:
	auto is_composite() const -> bool override;

private:
	sol::function function_;
};

class AffordanceComposite : Affordance {
public:
	auto add_affordance(AffordancePtr component) -> void;
	auto remove_affordance(AffordancePtr component) -> void;
	auto is_composite() const -> bool override;

private:
	std::vector<AffordancePtr> affordances_;
};

};  // namespace Affordance