var = {}

function init(entity)

end

function update(entity)
	if (Input.get_key_state("w"):is_key_hold()) then
		Camera.move(Movement.forward, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("a"):is_key_hold()) then
		Camera.move(Movement.left, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("s"):is_key_hold()) then
		Camera.move(Movement.backward, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("d"):is_key_hold()) then
		Camera.move(Movement.right, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("z"):is_key_pressed()) then
		Camera.toggle_noclip()
	end

	if (Input.get_key_state("escape"):is_key_pressed()) then
		Scene.load("main_menu")
	end

	local transform = entity:get_transform_component()

	transform.position = Camera.get_position()

	transform.position.y = Terrain.get_height("terrain", transform.position, Math.vec3.new(1, 0.05, 1))

	Camera.set_position(transform.position)
end
