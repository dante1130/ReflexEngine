variables = {

}

function init(entity)

end

function update(entity)
	if (Input.get_key_state("w"):is_key_hold()) then
		move(Movement.forward, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("a"):is_key_hold()) then
		move(Movement.left, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("s"):is_key_hold()) then
		move(Movement.backward, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("d"):is_key_hold()) then
		move(Movement.right, EngineTime.get_delta_time())
	end

	if (Input.get_key_state("z"):is_key_pressed()) then
		toggle_noclip()
	end
end
