entity = {
	name = "Sphere",

	transform = {
		position = {
			x = 1,
			y = 0,
			z = 0
		},
		rotation = {
			x = 0,
			y = 0,
			z = 0
		},
		scale = {
			x = 0.025,
			y = 0.025,
			z = 0.025
		}
	},

	model = {
		model_name = "Sphere",
		material_name = "default"
	},

	rigidbody = {
        using_react_start = false,
        gravity_on = false,
        can_sleep = true,
        is_trigger = false,
        linear_drag = 0.1,
        angular_drag = 0.1,
		rb_type = 2
    },

	script = {
		lua_script = "game/TheDen/scripts/rb_sphere_add.lua"
	}
}
