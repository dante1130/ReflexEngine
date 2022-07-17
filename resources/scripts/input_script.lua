if (Input.get_key_state("escape"):is_key_pressed()) then
	set_pause_game(not get_pause_game())
end

if (Input.get_key_state("n"):is_key_pressed()) then
	exit_network_menu(not get_network_menu())
end

if (Input.get_key_state("p"):is_key_pressed()) then
	exit_pvp_network_menu(not get_pvp_network_menu())
end

if (Input.get_key_state("m"):is_key_pressed()) then
	setBoolData("help_menu", not getBoolData("help_menu", false))
end

if (Input.get_key_state("x"):is_key_pressed()) then
	setBoolData("show_credits", not getBoolData("show_credits", false))
end

if (Input.get_key_state("k"):is_key_pressed()) then
	Renderer.toggle_wireframe()
end

if (not get_pause_game()) then
	set_move_dir_x(0)
	set_move_dir_y(0)
	set_move_dir_z(0)

	if (Input.get_key_state("w"):is_key_hold()) then
		calculate_direction(Movement.forward)
	end

	if (Input.get_key_state("a"):is_key_hold()) then
		calculate_direction(Movement.left)
	end

	if (Input.get_key_state("s"):is_key_hold()) then
		calculate_direction(Movement.backward)
	end

	if (Input.get_key_state("d"):is_key_hold()) then
		calculate_direction(Movement.right)
	end

	if (Input.get_key_state("z"):is_key_pressed()) then
		toggle_noclip()
	end

	if (Input.get_mouse_key_state("mouse1"):is_key_pressed()) then
		setBoolData("should_shoot", true)
	end
end
