var = {
}

function init(ecs, entity)
	local rb = entity:get_rigidbody_component()
	rb:add_box_collider(Math.vec3.new(0, 0, 0), Math.vec3.new(0, 0, 0), Math.vec3.new(0.3, 0.05, 0.3), 0.5, 2, 0.25)

	local script = entity:get_script_component()
	script.is_active = false;
end
