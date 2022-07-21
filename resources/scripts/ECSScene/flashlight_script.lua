variables = {

}

function init(entity)

end

function update(entity)
	local transform = entity:get_transform_component()

	transform.position.x = camera_pos_x()
	transform.position.y = camera_pos_y()
	transform.position.z = camera_pos_z()

	local spotlight = entity:get_spot_light_component()

	spotlight.direction.x = camera_look_x()
	spotlight.direction.y = camera_look_y()
	spotlight.direction.z = camera_look_z()
end
