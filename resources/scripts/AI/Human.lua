baseObject = {
	type = "NPC",
	xPos = 90,
	yPos = 5,
	zPos = 45,
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = 90,
	xScale = 0.001,
	yScale = 0.001,
	zScale = 0.001,
	modelName = "duck_A",
	material_name = "shiny",
	animate = 1,
	loopAnimation = 1,
	rbType = 2,
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
	setUpFSM = "setupHumanFSM",
	faction = 1,
	health = 100,
	power = 1,
	moveSpeed = 3
}

collider1 = {
	colliderType = "Capsule",
	xPos = 0,
	yPos = 0,
	zPos = 0,
	radius = 0.25,
	height = 3,
	bounciness = 0.5,
	friction = 0.5
}