baseObject = {
	type = "NPC",
	xPos = 90,
	yPos = 5,
	zPos = 45,
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = 90,
	xScale = 1,
	yScale = 1,
	zScale = 1,
	modelName = "human",
	material_name = "shiny",
	animate = 1,
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
	numOfColliders = 1
}

AI = {
	setUpFSM = "setupPlayerFSM",
	faction = 1,
	health = 100,
	power = 1
}

collider1 = {
	colliderType = "Capsule",
	xPos = 0,
	yPos = 0,
	zPos = 0,
	radius = 0.1,
	height = 1.5,
	bounciness = 0.5,
	friction = 0.5
}