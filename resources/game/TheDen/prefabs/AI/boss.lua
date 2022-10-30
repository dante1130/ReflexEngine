entity = {
	name = "Boss",
	collection_id = 10,

	transform = {
		position = {
			x = 56,
			y = 2,
			z = -5.456
		},
		rotation = {
			x = 0,
			y = 0,
			z = 90
		},
		scale = {
			x = 0.5,
			y = 0.5,
			z = 0.5
		}
	},

	model = {
		model_name = "boss",
		material_name = "default"
	},

	affordance_agent = {
		properties = { "Watch" },
		properties_weights = {},
		utility = {
			lua_script = "game/TheDen/scripts/AI/boss_ai.lua",
			update_func = "boss_update",
			states = {
				{
					name = "watch_state",
					affordance = { "Watch" }
				}
			}
		},
		mood_state = {
			joy_sadness = 0.0,
			trust_disgust = 0.0,
			fear_anger = 0.0,
			surprise_anticipation = 0.0
		},
		current_emotion = "Neutral"
	}
}
