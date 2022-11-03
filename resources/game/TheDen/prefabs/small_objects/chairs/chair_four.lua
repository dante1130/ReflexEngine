entity = {
	name = "chair_4",
	collection_id = 9, 

	transform = {
		position = {
			x = 46.5,
			y = 0.4,
			z = -5.3
		},
		rotation = {
			x = 0,
			y = 30,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "chair",
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
		lua_script = "game/TheDen/scripts/chair_script.lua"
	}
}
