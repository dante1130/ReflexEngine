var = {
	light_ori_position = Math.vec3.new(-50, 40, 0)
}

function init(ecs, entity)

end

function update(ecs, entity)
	local spotlight_rotation = Math.euler_to_quat(Math.vec3.new(0, Math.radians(0.01), 0))

	local spotlight = entity:get_spot_light_component()
	local pointlight = entity:get_point_light_component()

	spotlight.direction = Math.mul(spotlight_rotation, spotlight.direction)

	local pointlight_translate = Math.mul(Math.normalize(Math.vec3.new(spotlight.direction.x, 0, spotlight.direction.z)), 5)

	pointlight.position = Math.add(var.light_ori_position, pointlight_translate)
end
