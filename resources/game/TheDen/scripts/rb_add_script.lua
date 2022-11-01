var = {
}

function init(ecs, entity)
	--entity:add_rigidbody_component()
	local rb = entity:get_rigidbody_component()
	rb:add_box_collider(Math.vec3.new(0, 0, 0), Math.vec3.new(0, 0, 0), Math.vec3.new(0.09, 0.9, 0.6), 0.5, 2, 0.5)

	--"Chair"
	--rb:add_box_collider(Math.vec3.new(0, 0, 0), Math.vec3.new(0, 0, 90), Math.vec3.new(0.1, 0.9, 0.9), 0.5, 2, 0.5)
	--rb:add_box_collider(Math.vec3.new(0.4, 0, 0.4), Math.vec3.new(0, 0, 0), Math.vec3.new(0.1, 0.5, 0.1), 0.5, 2, 0.5)
	--rb:add_box_collider(Math.vec3.new(-0.4, 0, 0.4), Math.vec3.new(0, 0, 0), Math.vec3.new(0.1, 0.5, 0.1), 0.5, 2, 0.5)
	--rb:add_box_collider(Math.vec3.new(0.4, 0, -0.4), Math.vec3.new(0, 0, 0), Math.vec3.new(0.1, 0.5, 0.1), 0.5, 2, 0.5)
	--rb:add_box_collider(Math.vec3.new(-0.4, 0, -0.4), Math.vec3.new(0, 0, 0), Math.vec3.new(0.1, 0.5, 0.1), 0.5, 2, 0.5)

	local script = entity:get_script_component()
	script.is_active = false;
end

function update(ecs, entity)
	
end
