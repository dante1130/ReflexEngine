entity = {
	transform = {
		-- Position set internally in the water_script.lua
		position = { x = 0, y = 0, z = 0 },
		rotation = { x = 0, y = 0, z = 0, w = 1 },
		scale = { x = 100, y = 1, z = 100 }
	},

	mesh = {
		mesh_name = "water",
		texture_name = "water",
		material_name = "shiny"
	},

	script = {
		lua_script = "game/ECSScene/scripts/water_script.lua"
	}
}
