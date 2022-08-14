entity = {
	name = "Flashlight",

	spot_light = {
		shadow_width = 1024,
		shadow_height = 1024,
		near_plane = 0.1,
		far_plane = 100,

		color = { r = 1, g = 1, b = 1 },

		ambient_intensity = 0,
		diffuse_intensity = 1,

		position = { x = 0, y = 0, z = 0 },
		direction = { x = 0, y = 0, z = 0 },

		constant = 1,
		linear = 0,
		quadratic = 0,

		edge = 15,
	},

	script = {
		lua_script = "game/ECSScene/scripts/flashlight_script.lua"
	}
}
