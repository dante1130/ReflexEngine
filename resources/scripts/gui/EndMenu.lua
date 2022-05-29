local x = camera_pos_x()
local z = camera_pos_z()

local completed = false

if x < 28 and z > 200 and z < 220 then
	completed = true
end



if completed then
	if(get_pause_game() == false) then
		local pos = Audio.vec3df.new(camera_pos_x(), camera_pos_y(), camera_pos_z())
  		Audio.play_3d_sound("congrats", pos, false, 5.0)
	end

	set_pause_game(true)

	

	gui_setWindowSize(250, 260, 1)
	gui_setWindowPos(300, 0, 1)
	gui_begin("VICTORY")
	gui_text("Well done! You have made it off\nthe  island without dying.")

	local isPressed = gui_button("Restart game", 200, 50)
	if isPressed == true then
		load_from_scratch(true)
		load_game(true)
	end
	gui_end()
end