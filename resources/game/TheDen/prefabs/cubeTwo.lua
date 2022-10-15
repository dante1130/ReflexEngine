entity = {
	name = "Cube Two",

	transform = {
		position = {
			x = 2,
			y = 0,
			z = 0
		},
		rotation = {
			x = 0,
			y = 0,
			z = 0
		},
		scale = {
			x = 0.25,
			y = 0.25,
			z = 0.25
		}
	},

	model = {
		model_name = "default",
		material_name = "default"
	},

	rigidbody = {
        using_react_start = false,
        gravity_on = false,
        can_sleep = true,
        is_trigger = false,
        linear_drag = 0.1,
        angular_drag = 0.1,
		rb_type = 0
    },

	script = {
		lua_script = "game/TheDen/scripts/rb_add_script.lua"
	}

}
