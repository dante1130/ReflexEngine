
local paused = get_pause_game()
if paused then
	gui_setWindowSize(300, 300, 1)
	gui_setWindowPos(0, 0, 1)


	gui_begin("Pause Menu")

	gui_text("--Game is currently paused--")
	local unpause = gui_button("UNPAUSE", 150, 50)
	local save = gui_button("SAVE", 150, 50)
	local load = gui_button("LOAD", 150, 50)
	local exit = gui_button("EXIT", 150, 50)
	gui_text("gui frame rate: " .. gui_guiFrameRate())

	if unpause then
		set_pause_game(false)
	end

	if save then
		save_game(true)
	end

	if load then
		load_game(true)
	end

	if exit then
		exit_game()
	end


	gui_end()
end