entity = {
	name = "rubix_cube",
	collection_id = 8, 

	transform = {
		position = {
			x = 56.7,
			y = 0.63,
			z = -4.7
		},
		rotation = {
			x = 0,
			y = -241.9,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "rubix_cube",
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
		lua_script = "game/TheDen/scripts/rubix_cube_script.lua"
	}
}
