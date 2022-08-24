var = {}

function init(ecs, entity)

end

function update(ecs, entity)
	local spotlight = entity:get_spot_light_component()

	spotlight.position = Camera.get_position()
	spotlight.direction = Camera.get_direction()

	spotlight.position.y = spotlight.position.y - 0.3;
end
