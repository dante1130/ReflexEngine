var = {
}

function init(ecs, entity)
	--entity:add_rigidbody_component()
	local rb = entity:get_rigidbody_component()
	rb:add_sphere_collider(Math.vec3.new(0, 0, 0), Math.vec3.new(0, 0, 0), 0.05, 0.5, 0.1, 0.85)
end

function update(ecs, entity)
	local transform_component = entity:get_transform_component()
	local transform = transform_component.position
	local update = false

	if (Input.get_key_state("f"):is_key_pressed()) then
		DebugLogger.log_color("Physics", "Firing projectile!", GUI.vec4.new(1.0, 0.0, 0.0, 1.0))
		local rb_component = entity:get_rigidbody_component()
		rb_component:add_force(Math.vec3.new(0, 0, 2), Apply.LOCAL)
	end

	if (Input.get_key_state("g"):is_key_pressed()) then
		transform = Math.add(transform, Math.vec3.new(0, 0, 0.01))
		update = true
	end

	if (Input.get_key_state("j"):is_key_pressed()) then
		transform = Math.add(transform, Math.vec3.new(0, 0, -0.01))
		update = true
	end

	if (Input.get_key_state("y"):is_key_pressed()) then
		transform = Math.add(transform, Math.vec3.new(0, 0.01, 0))
		update = true
	end

	if (Input.get_key_state("h"):is_key_pressed()) then
		transform = Math.add(transform, Math.vec3.new(0, -0.01, 0))
		update = true
	end

	if (update == true) then
		transform_component.position = transform
	end
end
