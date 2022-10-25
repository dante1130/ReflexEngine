entity = {
	name = "chair_1",
	collection_id = 9, 

	transform = {
		position = {
			x = 43,
			y = 1.5,
			z = -5
		},
		rotation = {
			x = 0,
			y = -180,
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
        gravity_on = false,
        can_sleep = true,
        is_trigger = false,
        linear_drag = 0,
        angular_drag = 0,
		rb_type = 2
    },

	script = {
		lua_script = "game/TheDen/scripts/chair_script.lua"
	}
}
