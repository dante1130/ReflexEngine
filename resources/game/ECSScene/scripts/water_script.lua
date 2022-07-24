var = {
	water_position = Math.vec3.new(0, 2.5, 0),
	offset_multiplier = Math.vec3.new(1.1, 1.2, 1.7),
	intensity = Math.vec3.new(5, 10, 5),
	time = 0.0,
}

function init(entity)

end

function update(entity)
	var.time = var.time + Time.get_delta_time()

	local water_movement = Math.div(Math.sin(Math.mul(var.time, var.offset_multiplier)), var.intensity)

	local transform = entity:get_transform_component()

	transform.position = Math.add(var.water_position, water_movement)
end
