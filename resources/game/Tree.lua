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
	xRotation = 1,
	yRotation = 0,
	zRotation = 0,
	angle = 1,
	xScale = 0.0004,
	yScale = 0.0006,
	zScale = 0.0004,
	modelName = "tree",
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
	savable = true,
	numOfColliders = 1
}

collider1 = {
	colliderType = "Capsule",
	xPos = 0,
	yPos = 0,
	zPos = 0,
	radius = 0.5,
	height = 2,
	bounciness = 0.5,
	friction = 0.5
}