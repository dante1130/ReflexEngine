baseObject = {
	type = "Projectile",
	xPos = camera_pos_x() + camera_look_x() * 2,
	yPos = camera_pos_y() + camera_look_y() * 2,
	zPos = camera_pos_z() + camera_look_z() * 2,
	xRotation = camera_look_x(),
	yRotation = camera_look_x(),
	zRotation = camera_look_x(),
	angle = -90,
	savable = true,
	xScale = 0.01,
	yScale = 0.01,
	zScale = 0.01,
	modelName = "rock",
	material_name = "shiny",
	rbType = 2,
	gravity = 1,
	xForce = camera_look_x() * 25,
	yForce = camera_look_y() * 25,
	zForce = camera_look_z() * 25,
	xTorque = random_generator(-10, 20),
	yTorque = random_generator(-10, 20),
	zTorque = random_generator(-10, 20),
	linearDamping = 0.1,
	angularDamping = 0.1,
	sleep = 1,
	numOfColliders = 1,
	timeAliveLeft = 20,
	damage = 1,
	logic = "scripts/bulletLogic.lua",
	toDelete = 0,
	floorContact = 0
}

collider1 = {
	colliderType = "Sphere",
	xPos = 0,
	yPos = 0,
	zPos = 0,
	radius = 0.1,
	bounciness = 0.5,
	friction = 0.5
}
