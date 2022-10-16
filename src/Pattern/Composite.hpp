#pragma once

#include <memory>

namespace Pattern::Composite {
using ComponentPtr = std::shared_ptr<class Component>;

class Component {
public:
	[[nodiscard]] auto get_parent() const -> ComponentPtr;
	auto set_parent(ComponentPtr parent) -> void;

	virtual auto add(ComponentPtr component) -> void = 0;
	virtual auto remove(ComponentPtr component) -> void = 0;
	[[nodiscard]] virtual auto is_composite() const -> bool = 0;
	virtual ~Component() = default;

private:
	ComponentPtr parent_;
};
}  // namespace Pattern::Composite