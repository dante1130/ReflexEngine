baseObject = {
	type = "PhysicsObject",
	xPos = 100,
	yPos = 2.5,
	zPos = 75,
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = -180,
	xScale = 0.5,
	yScale = 0.5,
	zScale = 0.5,
	modelName = "boat",
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
	numOfColliders = 1
}

local boat_pos = Audio.vec3df.new(baseObject.xPos, baseObject.yPos, baseObject.zPos)
Audio.play_3d_sound("duckandcover", boat_pos, true, 5.0)

collider1 = {
	colliderType = "Box",
	xPos = 0,
	yPos = 0,
	zPos = 0,
	xBox = 5,
	yBox = 3,
	zBox = 3,
	bounciness = 0.5,
	friction = 0.5
}
