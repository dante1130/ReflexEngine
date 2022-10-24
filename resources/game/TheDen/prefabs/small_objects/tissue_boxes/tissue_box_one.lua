entity = {
	name = "tissue_box",
	collection_id = 8, 

	transform = {
		position = {
			x = 46.3,
			y = 0.83,
			z = -1
		},
		rotation = {
			x = 0,
			y = -263.9,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "tissue_box",
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
		lua_script = "game/TheDen/scripts/tissue_box_script.lua"
	}
}
