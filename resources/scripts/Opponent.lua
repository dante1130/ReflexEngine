local x
local y
local z

if get_receiving_data() then
	x = get_network_pos_x()
	z = get_network_pos_y()
	y = get_network_pos_z()
else
	x = 50
	y = 100
	z = 50
end


baseObject = {
	type = "Item",
	xPos = get_network_pos_x(),
	yPos = get_network_pos_y(),
	zPos = get_network_pos_z(),
	xRotation = 1,
	yRotation = 0,
	zRotation = 0,
	angle = 90,
	xScale = 0.1,
	yScale = 0.1,
	zScale = 0.1
}

item = {
	modelName = "ghost",
	material_name = "shiny"
}
