local quat_rotation = Math.euler_to_quat(Math.vec3.new(0, Math.radians(-180), 0))

entity = {
	transform = {
		position = {
			x = 100,
			y = 2.5,
			z = 75
		},
		rotation = {
			x = quat_rotation.x,
			y = quat_rotation.y,
			z = quat_rotation.z,
			w = quat_rotation.w
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
