entity = {
	name = "pizza_box",
	collection_id = 7, 

	transform = {
		position = {
			x = 45.7,
			y = 0.82,
			z = -4.9
		},
		rotation = {
			x = 0,
			y = -153.6,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "pizza_box",
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
		lua_script = "game/TheDen/scripts/pizza_box_script.lua"
	}
}
