local notReady = true
local x
local y
local z
local angle = random_generator(1, 360)

while notReady do
	x = random_generator(1, 240)
	z = random_generator(1, 240)
	y = get_y_coord_on_floor(x, z)
	if(y > 3) then
		notReady = false
	end
end

baseObject = {
	type = "NPC",
	xPos = x,
	yPos = y,
	zPos = z,
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = angle,
	xScale = 0.01,
	yScale = 0.01,
	zScale = 0.01,
	modelName = "ghost_A",
	model_texture = "ghost_A",
	material_name = "shiny",
	animate = 0,
	loopAnimation = 1,
	rbType = 2,
	gravity = 0,
	xForce = 0,
	yForce = 0,
	zForce = 0,
	xTorque = 0,
	yTorque = 0,
	zTorque = 0,
	linearDamping = 0.999,
	angularDamping = 0.999,
	sleep = 1,
	savable = true,
	numOfColliders = 1
}

AI = {
	setUpFSM = "setupGhostFSM",
	faction = 2,
	health = 100,
	power = 0.25,
	moveSpeed = 2
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