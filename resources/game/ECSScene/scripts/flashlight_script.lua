var = {}

function init(entity)

end

function update(entity)
	local spotlight = entity:get_spot_light_component()

	spotlight.position = Camera.get_position()
	spotlight.direction = Camera.get_direction()
end
