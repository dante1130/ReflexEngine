if get_credits() then
	gui_setWindowSize(1600, 900, 1)
	gui_setWindowPos(160, 80, 1)
	gui_begin("Credits")
	gui_text("Credits")
	gui_image("credits")
	local exit = gui_button("EXIT", 150, 50)
	gui_end()

	if exit then
		exit_game()
	end
end
