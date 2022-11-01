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
		object_name = "talk",
		lua_script = "game/TheDen/scripts/Affordances/affordance.lua"
	},

	affordance_agent = {
		properties = { "Duck", "Watch", "Talk", "Study", "Eat", "Move" },
		properties_weights = { ["Duck"] = 2.0, ["Move"] = 2.0 },
		utility = {
			lua_script = "game/TheDen/scripts/AI/duck_ai.lua",
			context = {
				["social"] = {
					value = 0.0,
					arousal_weight = 0.1,
					valence_weight = 0.1
				},
				["hunger"] = {
					value = 0.0,
					arousal_weight = 0.25,
					valence_weight = 0.25
				},
				["stress"] = {
					value = 0.0,
					arousal_weight = 1.0,
					valence_weight = 1.0
				},
				["fun"] = {
					value = 0.0,
					arousal_weight = 0.0,
					valence_weight = 1.0
				}
			},
			update_func = "duck_update",
			states = {
				{
					name = "watch_state",
					affordance = { "Watch" }
				},
				{
					name = "talk_state",
					affordance = { "Talk" }
				},
				-- {
				-- 	name = "study_state",
				-- 	affordance = { "Study" }
				-- }
			}
		},
		mood_state = {
			arousal = 0.0,
			valence = 0.0
		}
	}
}
