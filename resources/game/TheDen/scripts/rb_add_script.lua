var = {
}

function init(ecs, entity)
	--entity:add_rigidbody_component()
	local rb = entity:get_rigidbody_component()
	rb:add_box_collider(Math.vec3.new(0, 0, 0), Math.vec3.new(0.3, 0.3, 2), 0.5, 0.5, 2, 0.85)
end

function update(ecs, entity)
	
end
