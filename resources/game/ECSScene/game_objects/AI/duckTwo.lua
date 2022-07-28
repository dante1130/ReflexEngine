entity = {
	name = "chad duck",

	transform = {
		position = {
			x = -20,
			y = 10,
			z = 0
		},
		rotation = {
			x = -90,
			y = 0,
			z = 0
		},
		scale = {
			x = 0.25,
			y = 0.25,
			z = 0.25
		}
	},

	model = {
		model_name = "cat",
		material_name = "shiny"
	},

	statemachine = {
		current_state = "state_chad",
		global_state = "state_global",
		previous_state = "state_chad",

		var = {
			faction = 1,
			health = 100,
			damage = 10
		}
	}
}
