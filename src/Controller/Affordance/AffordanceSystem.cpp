#include "AffordanceSystem.hpp"

#include "Controller/LuaManager.hpp"

using namespace Affordance;

SOL_BASE_CLASSES(AffordanceLeaf, AffordanceNode);
SOL_BASE_CLASSES(AffordanceComposite, AffordanceNode);
SOL_DERIVED_CLASSES(AffordanceNode, AffordanceLeaf, AffordanceComposite);

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

	auto affordance_node_type =
	    lua.new_usertype<AffordanceNode>("AffordanceNode", sol::no_constructor);
	affordance_node_type["name"] =
	    sol::property(&AffordanceNode::get_name, &AffordanceNode::set_name);
	affordance_node_type["properties"] = sol::property(
	    &AffordanceNode::get_properties, &AffordanceNode::set_properties);

	auto affordance_leaf_type = lua.new_usertype<AffordanceLeaf>(
	    "AffordanceLeaf",
	    sol::factories([](const std::string& name,
	                      const sol::as_table_t<Properties>& properties,
	                      const sol::function& function) {
		    return std::make_shared<AffordanceLeaf>(name, properties.value(),
		                                            function);
	    }),
	    sol::base_classes, sol::bases<AffordanceNode>());
	affordance_leaf_type["function"] = sol::property(
	    &AffordanceLeaf::get_function, &AffordanceLeaf::set_function);

	auto affordance_composite_type = lua.new_usertype<AffordanceComposite>(
	    "AffordanceComposite",
	    sol::factories(
	        [](const std::string& name,
	           const sol::as_table_t<Properties>& properties,
	           const sol::as_table_t<std::vector<AffordancePtr>>& affordances) {
		        return std::make_shared<AffordanceComposite>(
		            name, properties.value(), affordances.value());
	        }),
	    sol::base_classes, sol::bases<AffordanceNode>());
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
