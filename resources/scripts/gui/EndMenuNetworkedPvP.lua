local x = get_network_pos_x()
local z = get_network_pos_z()

local completed = false

if x < 28 and z > 200 and z < 220 then
	completed = true
end



if completed then

	set_pause_game(true)

	

	gui_setWindowSize(250, 260, 1)
	gui_setWindowPos(300, 0, 1)
	gui_begin("Defeat!")
	gui_text("You Lost! Your opponent made it off\nthe  island without dying.")

	local isPressed = gui_button("Restart game", 200, 50)
	if isPressed == true then
		load_from_scratch(true)
		load_game(true)
	end
	gui_end()
end