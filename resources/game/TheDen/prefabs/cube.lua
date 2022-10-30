entity = {
	name = "Last Block",

	transform = {
		position = {
			x = 45,
			y = 10,
			z = 0
		},
		rotation = {
			x = 0,
			y = 0,
			z = 0
		},
		scale = {
			x = 0.045,
			y = 0.45,
			z = 0.3
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
        linear_drag = 0.1,
        angular_drag = 0.1,
		rb_type = 2
    },

	script = {
		lua_script = "game/TheDen/scripts/rb_add_script.lua"
	}
}
