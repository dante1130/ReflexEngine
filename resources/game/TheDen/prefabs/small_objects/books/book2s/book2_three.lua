entity = {
	name = "book2",
	collection_id = 5, 

	transform = {
		position = {
			x = 43,
			y = 0.825,
			z = -2
		},
		rotation = {
			x = 0,
			y = -43.5,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "book2",
		material_name = "default"
	},

	rigidbody = {
        using_react_start = false,
        gravity_on = true,
        can_sleep = true,
        is_trigger = false,
        linear_drag = 0.5,
        angular_drag = 0.5,
		rb_type = 2
    },

	script = {
		lua_script = "game/TheDen/scripts/book2_script.lua"
	}
}
