entity = {
	name = "pizza_box",
	collection_id = 7, 

	transform = {
		position = {
			x = 44.7,
			y = 0.82,
			z = -5.8
		},
		rotation = {
			x = 0,
			y = -12,
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
        is_trigger = false,
        linear_drag = 0.5,
        angular_drag = 0.5,
		rb_type = 2
    },

	script = {
		lua_script = "game/TheDen/scripts/pizza_box_script.lua"
	}
}
