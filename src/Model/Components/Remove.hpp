#pragma once

namespace Component {
/**
 * @author Andrew Ho
 * @struct Remove
 * @brief A component that marks the entity for deletion.
 */
struct Remove {
	/// A temporary variable to ensure struct is not empty.
	bool x = false;
};
}  // namespace Component
