var = {

}

function init(ecs, entity)

end

function update(ecs, entity)
	local spotlight_rotation = Math.euler_to_quat(Math.vec3.new(0, Math.radians(0.01), 0))

	local spotlight = entity:get_spot_light_component()

	spotlight.direction = Math.mul(spotlight_rotation, spotlight.direction)
end
