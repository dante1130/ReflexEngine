var = {}

function init(entity)

end

function update(entity)
	local spotlight = entity:get_spot_light_component()

	spotlight.position.x = camera_pos_x()
	spotlight.position.y = camera_pos_y()
	spotlight.position.z = camera_pos_z()

	spotlight.direction.x = camera_look_x()
	spotlight.direction.y = camera_look_y()
	spotlight.direction.z = camera_look_z()
end
