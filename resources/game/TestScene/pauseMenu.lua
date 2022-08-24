local paused = get_pause_game()
if paused then
	gui_setWindowSize(300, 300, 1)
	gui_setWindowPos(0, 0, 1)


	gui_begin("Pause Menu")

	gui_text("--Game is currently paused--")
	local unpause = gui_button("UNPAUSE", 150, 50)
	local save = gui_button("SAVE", 150, 50)
	local load = gui_button("LOAD", 150, 50)
	local credits = gui_button("EXIT", 150, 50)
	gui_text("gui frame rate: " .. gui_guiFrameRate())

	if unpause then
		set_pause_game(false)
	end

	if save then
		setBoolData("save_game", true)
		setIntData("last_save_time", current_time())
	end

	if load then
		setBoolData("load_game", true)
		setIntData("last_load_time", current_time())
	end

	if credits then
		setBoolData("show_credits", true)
	end


	gui_end()
end
