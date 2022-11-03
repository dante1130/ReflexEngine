entity = {
	name = "Sphere",

	transform = {
		position = {
			x = 51,
			y = 10.25,
			z = -0.25
		},
		rotation = {
			x = 0,
			y = 0,
			z = 0
		},
		scale = {
			x = 0.05,
			y = 0.05,
			z = 0.05
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
        linear_drag = 0.1,
        angular_drag = 0.1,
		rb_type = 2
    },

	script = {
		lua_script = "game/TheDen/scripts/rb_sphere_add.lua"
	}
}
