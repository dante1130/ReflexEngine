entity = {
	name = "laptop",
	collection_id = 6, 

	transform = {
		position = {
			x = 56.5,
			y = 0.75,
			z = -5.8
		},
		rotation = {
			x = 0,
			y = -241.3,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "laptop",
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
		lua_script = "game/TheDen/scripts/laptop_script.lua"
	}
}
