entity = {
	name = "Theater light",
	collection_id = 1,

	point_light = {
		shadow_width = 512,
		shadow_height = 512,
		near_plane = 0.1,
		far_plane = 128,

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
		shadow_width = 512,
		shadow_height = 512,
		near_plane = 0.1,
		far_plane = 128,

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
