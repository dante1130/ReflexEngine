#include "Affordance.hpp"

#include <string>

using namespace Affordance;

AffordanceNode::AffordanceNode(std::string name, Properties properties)
    : name_(std::move(name)), properties_(std::move(properties)) {}

auto AffordanceNode::is_composite() const -> bool { return false; }

auto AffordanceNode::get_name() -> const std::string& { return name_; }

auto AffordanceNode::get_properties() -> const Properties& {
	return properties_;
}

auto AffordanceNode::set_name(const std::string& name) -> void { name_ = name; }

auto AffordanceNode::set_properties(const Properties& properties) -> void {
	properties_ = properties;
}

AffordanceLeaf::AffordanceLeaf(std::string name, Properties properties,
                               sol::function function)
    : AffordanceNode(std::move(name), std::move(properties)),
      function_(std::move(function)) {}

auto AffordanceLeaf::is_composite() const -> bool { return false; }

auto AffordanceLeaf::get_function() const -> const sol::function& {
	return function_;
}

auto AffordanceLeaf::set_function(const sol::function& function) -> void {
	function_ = function;
}

AffordanceComposite::AffordanceComposite(std::string name,
                                         Properties properties,
                                         std::vector<AffordancePtr> affordances)
    : AffordanceNode(std::move(name), std::move(properties)),
      affordances_(std::move(affordances)) {}

auto AffordanceComposite::is_composite() const -> bool { return true; }

auto AffordanceComposite::add_affordance(AffordancePtr affordance) -> void {
	affordances_.push_back(std::move(affordance));
}

auto AffordanceComposite::remove_affordance(const AffordancePtr& affordance)
    -> void {
	affordances_.erase(
	    std::remove(affordances_.begin(), affordances_.end(), affordance),
	    affordances_.end());
}

auto AffordanceComposite::get_affordances() -> std::vector<AffordancePtr>& {
	return affordances_;
}
