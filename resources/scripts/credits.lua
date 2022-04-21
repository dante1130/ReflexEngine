if get_credits() then
	gui_setWindowSize(window_width() / 1.5, window_height() / 1.5, 2)
	gui_setWindowPos(window_width() / 6, window_height() / 6, 1)
	gui_begin("Credits")
	gui_text("Credits")
	gui_image("credits")
	local exit = gui_button("EXIT", 150, 50)
	gui_end()

	if exit then
		exit_game()
	end
end
