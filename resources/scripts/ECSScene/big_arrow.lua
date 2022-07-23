local quat_rotation = Math.euler_to_quat(Math.vec3.new(0, Math.radians(45), 0))

entity = {
	transform = {
		position = { x = 15, y = 70, z = 210 },
		rotation = {
			x = quat_rotation.x,
			y = quat_rotation.y,
			z = quat_rotation.z,
			w = quat_rotation.w
		},
		scale = { x = 3, y = 3, z = 3 }
	},

	model = {
		model_name = "big_arrow",
		material_name = "shiny"
	}
}
