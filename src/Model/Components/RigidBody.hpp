#pragma once

namespace Component {

	struct Rigidbody {
		/// Determines if gravity is enabled
		bool gravity_on = true;
		/// Determines if the body can sleep
		bool can_sleep = true;
		/// Determines if the body is a trigger
		bool is_trigger = false;

		// The value of the force drag
		float linear_drag = 0.0f;
		/// The value of the torque drag
		float angular_drag = 0.0f;

		Rigidbody() = default;

		Rigidbody(const Rigidbody&) = default;

		Rigidbody(bool gravity_on, bool can_sleep,
			bool is_trigger, float linear_drag, float angular_drag)
			: gravity_on(gravity_on), can_sleep(can_sleep),
			is_trigger(is_trigger), linear_drag(linear_drag),
			angular_drag(angular_drag) {}
	};
};