entity = {
	spot_light = {
		color = { x = 1, y = 1, z = 1 },

		ambient_intensity = 1,
		diffuse_intensity = 1,

		position = { x = 0, y = 0, z = 0 },
		direction = { x = 0, y = 0, z = 0 },

		constant = 1,
		linear = 0,
		quadratic = 0,

		edge = 15,
	},

	script = {
		lua_script = "scripts/ECSScene/flashlight_script.lua"
	}
}
