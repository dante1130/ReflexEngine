entity = {
	name = "book5",
	collection_id = 5, 

	transform = {
		position = {
			x = 43.5,
			y = 0.805,
			z = -1.2
		},
		rotation = {
			x = 0,
			y = -203,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "book5",
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
		lua_script = "game/TheDen/scripts/book4-5_script.lua"
	}
}
