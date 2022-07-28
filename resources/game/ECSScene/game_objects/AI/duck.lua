entity = {
	name = "duck",

	transform = {
		position = {
			x = 20,
			y = -5,
			z = 0
		},
		rotation = {
			x = -90,
			y = 0,
			z = 0
		},
		scale = {
			x = 1,
			y = 1,
			z = 1
		}
	},

	model = {
		model_name = "cat",
		material_name = "shiny"
	},

	statemachine = {
		current_state = "state_patrol",
		global_state = "state_global",
		previous_state = "state_patrol",

		var = {
			faction = 1,
			health = 100,
			damage = 10
		}
	}
}
