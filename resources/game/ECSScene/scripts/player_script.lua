var = {
	speed = 1.0
}

function init(ecs, entity)

end

function update(ecs, entity)
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

	if (not Camera.is_noclip()) then
		local transform = entity:get_transform_component()

		transform.position = Camera.get_position()
		transform.position.y = 1 + Terrain.get_height("terrain", transform.position, Math.vec3.new(2, 0.05, 2))

		Camera.set_position(transform.position)
	end

	if (Time.is_paused()) then
		dofile "game/ECSScene/scripts/pause_menu.lua"
		dofile "game/ECSScene/scripts/network_menu.lua"
	end
end
