#include "Affordance.hpp"

#include <string>

using namespace Affordance;

AffordanceNode::AffordanceNode(std::string name, Properties properties)
    : name_(std::move(name)), properties_(std::move(properties)) {}

auto AffordanceNode::get_name() -> const std::string& { return name_; }

auto AffordanceNode::get_properties() -> const Properties& {
	return properties_;
}

auto AffordanceNode::set_name(const std::string& name) -> void { name_ = name; }

auto AffordanceNode::set_properties(const Properties& properties) -> void {
	properties_ = properties;
}

auto AffordanceLeaf::is_composite() const -> bool { return false; }

auto AffordanceLeaf::get_function() const -> const sol::function& {
	return function_;
}

auto AffordanceLeaf::set_function(const sol::function& function) -> void {
	function_ = function;
}

auto AffordanceComposite::is_composite() const -> bool { return true; }

auto AffordanceComposite::add_affordance(AffordancePtr affordance) -> void {
	affordances_.emplace_back(std::move(affordance));
}

auto AffordanceComposite::remove_affordance(const AffordancePtr& affordance)
    -> void {
	affordances_.erase(
	    std::remove(affordances_.begin(), affordances_.end(), affordance),
	    affordances_.end());
}
