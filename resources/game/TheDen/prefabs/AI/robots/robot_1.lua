entity = {
	name = "Robot 1",
	collection_id = 11,

	transform = {
		position = {
			x = 51,
			y = 0.75,
			z = -5.456
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

	model = {
		model_name = "robot",
		material_name = "default"
	},

	affordance_agent = {
		properties = { "Watch", "Talk" },
		properties_weights = {},
		utility = {
			lua_script = "game/TheDen/scripts/AI/robot_ai.lua",
			update_func = "robot_update",
			states = {
				{
					name = "watch_state",
					affordance = { "Watch" }
				}
			}
		},
		mood_state = {
			arousal = 0.0,
			valence = 0.0
		},
		current_emotion = "Neutral"
	}
}
