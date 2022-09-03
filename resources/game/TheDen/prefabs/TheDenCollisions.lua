entity = {
	name = "TheDenCollisions",
	collection_id = 3,

	transform = {
		position = {
			x = 50,
			y = 0,
			z = 0
		},
		rotation = {
			x = 0,
			y = 0,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	rigidbody = {
        using_react_start = false,
        gravity_on = false,
        can_sleep = true,
        is_trigger = false,
        linear_drag = 0.1,
        angular_drag = 0.1,
		rb_type = 0
    },

	script = {
		lua_script = "game/TheDen/scripts/TheDenCollisions_script.lua"
	}

}
