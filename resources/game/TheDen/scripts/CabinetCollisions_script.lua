var = {
}

function init(ecs, entity)
	if(not entity:any_rigidbody_component()) then
		entity:add_rigidbody_component()
	end
	local rb = entity:get_rigidbody_component()
	rb.type = 0
	rb:add_box_collider(Math.vec3.new(0, 0, 0), Math.vec3.new(0, 0, 0), Math.vec3.new(4.98, 3.1, 1.8), 0.5, 0.5, 1)

	local script = entity:get_script_component()
	script.is_active = false;
end

function update(ecs, entity)
	
end
