var = {
	offset_multiplier = Math.vec3.new(1.1, 1.2, 1.7),
	intensity = Math.vec3.new(5, 10, 5),
	time = 0.0
}

function init(entity)

end

function update(entity)
	local transform = entity:get_transform_component()

	var.time = var.time + EngineTime.get_delta_time()

	transform.position = Math.div(Math.sin(Math.mul(var.time, var.offset_multiplier)), var.intensity)
end
