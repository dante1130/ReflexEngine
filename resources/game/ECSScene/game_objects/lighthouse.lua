entity = {
	name = "Lighthouse",

	transform = {
		position = {
			x = -50,
			y = 2,
			z = 0
		},
		rotation = {
			x = 270,
			y = 0,
			z = 0
		},
		scale = {
			x = 0.2,
			y = 0.2,
			z = 0.2
		},
	},

	script = {
		lua_script = "game/ECSScene/scripts/lighthouse_script.lua"
	},

	model = {
		model_name = "lighthouse",
		material_name = "shiny"
	},

	point_light = {
		color = {
			r = 1,
			g = 1,
			b = 1
		},

		ambient_intensity = 0,
		diffuse_intensity = 1,

		position = {
			x = -50,
			y = 40,
			z = 0
		},

		constant = 0,
		linear = 0,
		quadratic = 1
	},

	spot_light = {
		color = {
			r = 1,
			g = 1,
			b = 1
		},

		ambient_intensity = 0,
		diffuse_intensity = 2,

		position = {
			x = -50.0,
			y = 40.0,
			z = 0.0
		},

		constant = 1,
		linear = 0,
		quadratic = 0,

		direction = {
			x = 0.87,
			y = -0.2,
			z = 0.44
		},

		edge = 10
	}
}
