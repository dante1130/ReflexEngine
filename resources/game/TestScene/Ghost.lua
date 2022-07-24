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
	type = "PhysicsObject",
	xPos = x,
	yPos = y,
	zPos = z,
	xRotation = 0,
	yRotation = 1,
	zRotation = 0,
	angle = random_generator(1, 359),
	xScale = 0.01,
	yScale = 0.01,
	zScale = 0.01,
	modelName = "ghost",
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