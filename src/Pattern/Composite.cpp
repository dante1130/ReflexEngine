#include "Composite.hpp"

auto Pattern::Composite::Component::get_parent() const -> ComponentPtr {
	return parent_;
}

auto Pattern::Composite::Component::set_parent(ComponentPtr parent) -> void {
	parent_ = std::move(parent);
}
