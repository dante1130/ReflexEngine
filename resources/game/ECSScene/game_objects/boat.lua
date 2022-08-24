entity = {
	name = "Boat",

	transform = {
		position = {
			x = 100,
			y = 2.5,
			z = 75
		},
		rotation = {
			x = 0,
			y = -180,
			z = 0
		},
		scale = {
			x = 0.5,
			y = 0.5,
			z = 0.5
		}
	},

	model = {
		model_name = "boat",
		material_name = "shiny"
	},

	script = {
		lua_script = "game/ECSScene/scripts/boat_script.lua"
	}
}
