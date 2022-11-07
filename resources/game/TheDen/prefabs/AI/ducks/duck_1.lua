entity = {
	name = "Duck 1",
	collection_id = 12,

	transform = {
		position = {
			x = 50,
			y = 0.15,
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

	md2_animation = {
		md2_name = "duck",
		texture_name = "duck",
		material_name = "default"
	},

	affordance = {
		object_name = "duck",
		lua_script = "game/TheDen/scripts/Affordances/affordance.lua"
	},

	affordance_agent = {
		properties = { "Duck", "Watch", "Talk", "Study", "Eat", "Move" },
		properties_weights = { ["Duck"] = 2.0, ["Move"] = 2.0 },
		utility = {
			lua_script = "game/TheDen/scripts/AI/duck_ai.lua",
			context = {
				["social"] = {
					value = 1.0,
					arousal_weight = 0.1,
					valence_weight = 0.1
				},
				["hunger"] = {
					value = 0.0,
					arousal_weight = 0.5,
					valence_weight = 0.25
				},
				["stress"] = {
					value = 1.0,
					arousal_weight = 1.0,
					valence_weight = 1.0
				},
				["fun"] = {
					value = 0.25,
					arousal_weight = 1.0,
					valence_weight = 0.5
				}
			},
			update_func = "duck_update",
			states = {
				["watch_state"] = {
					affordance = { "Watch" }
				},
				["talk_state"] = {
					affordance = { "Talk" }
				},
				["study_state"] = {
					affordance = { "Study" }
				},
				["eat_state"] = {
					affordance = { "Eat" }
				}
			}
		},
		mood_state = {
			arousal = 0.0,
			valence = 0.0
		}
	}
}
