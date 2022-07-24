var = {}

function init(entity)

end

function update(entity)
	if (Input.get_key_state("w"):is_key_hold()) then
		Camera.move(Movement.forward, Time.get_delta_time())
	end

	if (Input.get_key_state("a"):is_key_hold()) then
		Camera.move(Movement.left, Time.get_delta_time())
	end

	if (Input.get_key_state("s"):is_key_hold()) then
		Camera.move(Movement.backward, Time.get_delta_time())
	end

	if (Input.get_key_state("d"):is_key_hold()) then
		Camera.move(Movement.right, Time.get_delta_time())
	end

	if (Input.get_key_state("z"):is_key_pressed()) then
		Camera.toggle_noclip()
	end

	if (Input.get_key_state("f11"):is_key_pressed()) then
		Window.set_fullscreen(not Window.is_fullscreen())
	end

	if (Input.get_key_state("escape"):is_key_pressed()) then
		Window.close()
	end

	if (not Camera.is_noclip()) then
		local transform = entity:get_transform_component()

		transform.position = Camera.get_position()
		transform.position.y = 1 + Terrain.get_height("terrain", transform.position, Math.vec3.new(2, 0.05, 2))

		Camera.set_position(transform.position)
	end
end
