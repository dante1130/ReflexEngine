entity = {
	name = "book4",
	collection_id = 5, 

	transform = {
		position = {
			x = 46.3,
			y = 0.805,
			z = -1.8
		},
		rotation = {
			x = 0,
			y = -282,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "book4",
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
