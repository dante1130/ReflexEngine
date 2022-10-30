entity = {
	name = "CabinetCollisions",
	collection_id = 3,

	transform = {
		position = {
			x = 62.465,
			y = 1.5,
			z = -2.455
		},
		rotation = {
			x = 0,
			y = 5,
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
        linear_drag = 0.1,
        angular_drag = 0.1,
		rb_type = 0
    },

	script = {
		lua_script = "game/TheDen/scripts/CabinetCollisions_script.lua"
	}

}
