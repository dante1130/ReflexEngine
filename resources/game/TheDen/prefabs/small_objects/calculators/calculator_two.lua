entity = {
	name = "calculator",
	collection_id = 8, 

	transform = {
		position = {
			x = 43.3,
			y = 0.795,
			z = -2.2
		},
		rotation = {
			x = 0,
			y = -119,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "calculator",
		material_name = "default"
	},

	rigidbody = {
        using_react_start = false,
        gravity_on = true,
        can_sleep = true,
        linear_drag = 0.5,
        angular_drag = 0.5,
		rb_type = 2
    },

	script = {
		lua_script = "game/TheDen/scripts/calculator_script.lua"
	}
}
