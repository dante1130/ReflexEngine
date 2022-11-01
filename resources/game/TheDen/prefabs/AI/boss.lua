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

	affordance = {
		object_name = "talk",
		lua_script = "game/TheDen/scripts/Affordances/affordance.lua"
	},

	affordance_agent = {
		properties = { "Boss", "Watch" },
		properties_weights = {},
		utility = {
			lua_script = "game/TheDen/scripts/AI/boss_ai.lua",
			context = {
				["social"] = {
					value = 0.0,
					arousal_weight = 1,
					valence_weight = 1
				},
				["loneliness"] = {
					value = 0.0,
					arousal_weight = 1,
					valence_weight = 1
				},
				["fun"] = {
					value = 0.0,
					arousal_weight = 0.0,
					valence_weight = 0.1
				}
			},
			update_func = "boss_update",
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
