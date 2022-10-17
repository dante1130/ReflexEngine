#include "AffordanceSystem.hpp"

#include "Controller/LuaManager.hpp"

using namespace Affordance;

auto AffordanceSystem::get_instance() -> AffordanceSystem& {
	static AffordanceSystem instance;
	return instance;
}

auto AffordanceSystem::lua_access() -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto affordance_system = lua.create_named_table("AffordanceSystem");

	affordance_system.set_function("add_affordance",
	                               &AffordanceSystem::add_affordance, this);
	affordance_system.set_function("get_affordance",
	                               &AffordanceSystem::get_affordance, this);

	auto affordance_node_type = lua.new_usertype<AffordanceNode>(
	    "AffordanceNode",
	    sol::constructors<AffordanceNode(),
	                      AffordanceNode(std::string, Properties)>());
	affordance_node_type["name"] =
	    sol::property(&AffordanceNode::get_name, &AffordanceNode::set_name);
	affordance_node_type["properties"] = sol::property(
	    &AffordanceNode::get_properties, &AffordanceNode::set_properties);

	auto affordance_leaf_type = lua.new_usertype<AffordanceLeaf>(
	    "AffordanceLeaf",
	    sol::constructors<AffordanceLeaf(),
	                      AffordanceLeaf(std::string, Properties,
	                                     const sol::function&)>(),
	    sol::base_classes, sol::bases<AffordanceNode>());
	affordance_leaf_type["function"] = sol::property(
	    &AffordanceLeaf::get_function, &AffordanceLeaf::set_function);

	auto affordance_composite_type = lua.new_usertype<AffordanceComposite>(
	    "AffordanceComposite", sol::base_classes, sol::bases<AffordanceNode>());
	affordance_composite_type.set_function(
	    "add_affordance", &AffordanceComposite::add_affordance);
	affordance_composite_type.set_function(
	    "remove_affordance", &AffordanceComposite::remove_affordance);
}

auto AffordanceSystem::add_affordance(std::string object,
                                      AffordancePtr affordance) -> void {
	affordance_map_.emplace(std::move(object), std::move(affordance));
}

auto AffordanceSystem::get_affordance(const std::string& object)
    -> AffordancePtr {
	return affordance_map_.at(object);
}
