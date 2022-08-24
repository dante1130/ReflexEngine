var = {
	speed = 4.0
}

function init(ecs, entity)
	Window.set_cursor_visible(true)
	Time.set_pause(true)
	Camera.toggle_noclip()

	entity:add_rigidbody_component()
	local rb = entity:get_rigidbody_component()
	rb:add_box_collider(Math.vec3.new(0, -0.8, 0), Math.vec3.new(0.5, 1.8, 0.5), 0.3, 1)
	rb.linear_drag = 0.3
end

function update(ecs, entity)
	if (Input.get_key_state("v"):is_key_pressed()) then
		Scene.load_scene("duckandcover3")
	end

	if(not Camera.is_noclip() and entity:any_rigidbody_component()) then
		PhysicsMovement(ecs, entity)
	else
		PositionMovement(ecs, entity)
	end

	if (Input.get_key_state("z"):is_key_pressed()) then
		Camera.toggle_noclip()

		if (Camera.is_noclip()) then
			DebugLogger.log_color("warning", "You are cheating!", GUI.vec4.new(1.0, 0.0, 0.0, 1.0))
		end
	end

	if (Input.get_key_state("f11"):is_key_pressed()) then
		Window.set_fullscreen(not Window.is_fullscreen())
	end

	if (Input.get_key_state("escape"):is_key_pressed()) then
		Window.set_cursor_visible(not Window.is_cursor_visible())
		Time.set_pause(not Time.is_paused())
		if (Time.is_paused()) then
			DebugLogger.log("info", "Game is paused.")
		else
			DebugLogger.log("info", "Game is unpaused.")
		end

	end

	if (Input.get_key_state("k"):is_key_pressed()) then
		Renderer.toggle_wireframe()
	end

	if (Input.get_key_state("q"):is_key_pressed()) then
		var.speed = var.speed / 2
	end

	if (Input.get_key_state("e"):is_key_pressed()) then
		var.speed = var.speed * 2
	end

	if (Time.is_paused()) then
		dofile "game/TheDen/scripts/pause_menu.lua"
	end
end


function PositionMovement(ecs, entity)
	local transform_component = entity:get_transform_component()
	local transform = transform_component.position

	Camera.set_position(transform)

	if (Input.get_key_state("w"):is_key_hold()) then
		Camera.move(Movement.forward, Time.get_delta_time() * var.speed)
	end

	if (Input.get_key_state("a"):is_key_hold()) then
		Camera.move(Movement.left, Time.get_delta_time() * var.speed)
	end

	if (Input.get_key_state("s"):is_key_hold()) then
		Camera.move(Movement.backward, Time.get_delta_time() * var.speed)
	end

	if (Input.get_key_state("d"):is_key_hold()) then
		Camera.move(Movement.right, Time.get_delta_time() * var.speed)
	end

	transform_component.position = Camera.get_position()

	if(entity:any_rigidbody_component()) then
		local rb_comp = entity:get_rigidbody_component()
		rb_comp:set_transform(transform_component.position, Math.vec3.new(0, 0, 0))
		rb_comp.velocity = Math.vec3.new(0,0,0)
		rb_comp.angular_velocity = Math.vec3.new(0, 0, 0)
	end
end

function PhysicsMovement(ecs, entity)
	local rb_comp = entity:get_rigidbody_component()
	local speed = 5000 * Time.get_delta_time() * var.speed
	local speed_vec = Math.vec3.new(speed, speed * 0.1, speed)
	local const_direction = Camera.get_direction()
	local direction = const_direction
	
	if (Input.get_key_state("w"):is_key_hold()) then
		direction = Math.mul(const_direction, speed_vec)
		rb_comp:add_force(direction, Apply.LOCAL)
	end

	if (Input.get_key_state("s"):is_key_hold()) then
		direction = Math.mul(const_direction, speed_vec)
		direction = Math.mul(-1, direction)
		rb_comp:add_force(direction, Apply.LOCAL)
	end

	local up_vector = Math.vec3.new(0, 1, 0)
	if(const_direction.x == 0 and const_direction.y == 1 and const_direction.z == 0) then
		up_vector.x = 1
		up_vector.y = 0
	end

	local strafe_vector = Math.cross(const_direction, up_vector)
	if (Input.get_key_state("d"):is_key_hold()) then
		direction = Math.mul(strafe_vector, speed_vec)
		rb_comp:add_force(direction, Apply.LOCAL)
	end

	if (Input.get_key_state("a"):is_key_hold()) then
		direction = Math.mul(strafe_vector, speed_vec)
		direction = Math.mul(-1, direction)
		rb_comp:add_force(direction, Apply.LOCAL)
	end

	local velocity = rb_comp.velocity
	local velocity_y = velocity.y
	velocity.y = 0
	local ratio = Math.length(velocity) / var.speed
	if (ratio > 1) then
		velocity = Math.div(velocity, ratio)
		velocity.y = velocity_y
		rb_comp.velocity = velocity
	end


	rb_comp.angular_velocity = Math.vec3.new(0, 0, 0)
	local transform_component = entity:get_transform_component()
	local transform = transform_component.position
	rb_comp:set_transform(transform, Math.vec3.new(0, 0, 0))
	Camera.set_position(transform)
end