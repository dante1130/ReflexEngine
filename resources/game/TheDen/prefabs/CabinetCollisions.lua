entity = {
	name = "CabinetCollisions",
	collection_id = 3,

	transform = {
		position = {
			x = 12.9651 + 50,
			y = 1.5,
			z = -1.24025 - 1.6
		},
		rotation = {
			x = 0,
			y = 10.4,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	rigidbody = {
        using_react_start = false,
        gravity_on = false,
        can_sleep = true,
        is_trigger = false,
        linear_drag = 0.1,
        angular_drag = 0.1
    },

	script = {
		lua_script = "game/TheDen/scripts/CabinetCollisions_script.lua"
	}

}
