baseObject = {
	type = "NPC",
	xPos = camera_pos_x(),
	yPos = 5,
	zPos = camera_pos_z(),
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = 90,
	xScale = 0.0001,
	yScale = 0.0001,
	zScale = 0.0001,
	modelName = "ghost",
	model_texture = "duck_A",
	material_name = "shiny",
	animate = 0,
	loopAnimation = 1,
	rbType = 1,
	gravity = 0,
	xForce = 0,
	yForce = 0,
	zForce = 0,
	xTorque = 0,
	yTorque = 0,
	zTorque = 0,
	linearDamping = 0,
	angularDamping = 0,
	sleep = 1,
	numOfColliders = 0
}

AI = {
	setUpFSM = "setupPlayerFSM",
	faction = 1,
	health = 100,
	power = 1,
	moveSpeed = 0
}