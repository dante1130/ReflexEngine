entity = {
	name = "Theater light",

	point_light = {
		shadow_width = 1024,
		shadow_height = 1024,
		near_plane = 0.1,
		far_plane = 100,

		color = {
			r = 1,
			g = 0.83,
			b = 0.5
		},

		ambient_intensity = 0,
		diffuse_intensity = 1,

		position = {
			x = 57,
			y = 2.5,
			z = -5.456
		},

		constant = 0,
		linear = 0,
		quadratic = 0.25
	},

	spot_light = {
		shadow_width = 1024,
		shadow_height = 1024,
		near_plane = 0.1,
		far_plane = 100,

		color = {
			r = 1,
			g = 0.83,
			b = 0.5
		},

		ambient_intensity = 0,
		diffuse_intensity = 1,

		position = {
			x = 57,
			y = 2.5,
			z = -5.456
		},

		constant = 0,
		linear = 0.1,
		quadratic = 0,

		direction = {
			x = 0.987,
			y = -0.5,
			z = 0.0
		},

		edge = 20
	}
}
