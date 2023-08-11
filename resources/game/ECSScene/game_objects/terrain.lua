entity = {
	name = "Terrain",

	transform = {
		position = {
			x = 0,
			y = 0,
			z = 0
		},
		rotation = {
			x = 0,
			y = 0,
			z = 0
		},
		scale = {
			x = 2,
			y = 0.05,
			z = 2
		}
	},

	terrain = {
		terrain_name = "terrain",
		texture_name = "grass",
		material_name = "shiny",
		detailmap_name = "grass",

		pathfinding = { --relative to height map values (not in game coordinates)
			min_value = 60.0,
			max_value = 256.0,
			max_distance = 100.0
		}
	}
}
