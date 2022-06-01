local x = random_generator(1, 240)
local z = random_generator(1, 240)


baseObject = {
	type = "PhysicsObject",
	xPos = x,
	yPos = get_y_coord_on_floor(x, z),
	zPos = z,
	xRotation = 1,
	yRotation = 0,
	zRotation = 0,
	angle = 1,
	xScale = 0.1,
	yScale = 0.1,
	zScale = 0.1,
	modelName = "rock",
	material_name = "shiny",
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
	numOfColliders = 2
}

collider1 = {
	colliderType = "Box",
	xPos = 0,
	yPos = 0,
	zPos = 0,
	xBox = 1,
	yBox = 1,
	zBox = 1,
	bounciness = 0.5,
	friction = 0.5
}

collider2 = {
	colliderType = "Capsule",
	xPos = 0,
	yPos = 0,
	zPos = 0,
	height = 2,
	radius = 1.5,
	bounciness = 0.5,
	friction = 0.5
}