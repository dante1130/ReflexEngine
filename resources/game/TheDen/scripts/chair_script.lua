var = {
}

function init(ecs, entity)
	local rb = entity:get_rigidbody_component()
	rb:add_box_collider(Math.vec3.new(0, 0.06, -0.05), Math.vec3.new(0, 0, 0), Math.vec3.new(0.54, 0.05, 0.4), 0.5, 2, 0.25)
	rb:add_box_collider(Math.vec3.new(0.262, -0.15, -0.29), Math.vec3.new(9, 0, 0), Math.vec3.new(0.02, 0.43, 0.02), 0.5, 3, 0.25)
	rb:add_box_collider(Math.vec3.new(-0.262, -0.15, -0.29), Math.vec3.new(9, 0, 0), Math.vec3.new(0.02, 0.43, 0.02), 0.5, 3, 0.25)
	rb:add_box_collider(Math.vec3.new(0.262, -0.14, 0.23), Math.vec3.new(-15, 0, 0), Math.vec3.new(0.02, 0.45, 0.02), 0.5, 3, 0.25)
	rb:add_box_collider(Math.vec3.new(-0.262, -0.14, 0.23), Math.vec3.new(-15, 0, 0), Math.vec3.new(0.02, 0.45, 0.02), 0.5, 3, 0.25)

	--local script = entity:get_script_component()
	--script.is_active = false;
end

function update(ecs, entity)

	if (Input.get_key_state("f"):is_key_pressed()) then
		local rb_comp = entity:get_rigidbody_component()
		local force_vector = Math.vec3.new(0, 0, -1000)
		rb_comp:add_force(force_vector, Apply.LOCAL)
	end

end
