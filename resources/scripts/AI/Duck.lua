local notReady = true
local x
local y
local z

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
	xPos = 90,
	yPos = 5,
	zPos = 40,
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = 0.01,
	xScale = 1,
	yScale = 1,
	zScale = 1,
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
	linearDamping = 0.999,
	angularDamping = 0.999,
	sleep = 1,
	numOfColliders = 1
}

AI = {
	setUpFSM = "setupDuckFSM",
	faction = 2,
	health = 100,
	power = 0.25,
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