var = {}

function init(ecs, entity)

end

function update(ecs, entity)
	local spotlight = entity:get_spot_light_component()

	spotlight.position = Camera.get_position()
	spotlight.direction = Camera.get_direction()
end
