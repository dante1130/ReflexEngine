var = {
}

function init(ecs, entity)
	local rb = entity:get_rigidbody_component()
	rb:add_box_collider(Math.vec3.new(0, 0, 0), Math.vec3.new(0, 0, 0), Math.vec3.new(0.08, 0.02, 0.18), 0.5, 0.1, 0.5)

end