var = {
}

function init(ecs, entity)
	local rb = entity:get_rigidbody_component()
	rb:add_box_collider(Math.vec3.new(0, -0.12, 0), Math.vec3.new(0, 0, 0), Math.vec3.new(0.38, 0.034, 0.27), 0.5, 2, 0.25)
	rb:add_box_collider(Math.vec3.new(0, 0.01, -0.135), Math.vec3.new(0, 0, 0), Math.vec3.new(0.38, 0.24, 0.034), 0.5, 0.5, 0.25)
end