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
		properties = { "Robot", "Watch", "Talk", "Annoy" },
		properties_weights = {},
		utility = {
			lua_script = "game/TheDen/scripts/AI/robot_ai.lua",
			context = {
				["social"] = {
					value = 0.0,
					arousal_weight = -0.5,
					valence_weight = 0.5
				},
				["cheeky"] = {
					value = 0.0,
					arousal_weight = 1,
					valence_weight = 0.5
				},
				["fun"] = {
					value = 0.0,
					arousal_weight = 0.0,
					valence_weight = 0.5
				}
			},
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
		}
	}
}
