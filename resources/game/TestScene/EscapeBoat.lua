baseObject = {
	type = "PhysicsObject",
	xPos = 12,
	yPos = 2.5,
	zPos = 210,
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = 50,
	savable = true,
	xScale = 1,
	yScale = 1,
	zScale = 1,
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
