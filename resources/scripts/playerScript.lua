if camera_pos_y() < -5 then
	load_game(true)
else
	local time = current_time() - time_since_last_save()
	if time > 30 then
		save_game(true)
		print("Checkpoint - 30 seconds passed")
	end

	time = current_time() - time_since_last_load()
	if time < 5 then
		gui_setWindowSize(300, 100, 1)
		gui_setWindowPos(550, 0, 1)
		gui_begin("YOU DIED")
		gui_text("Reloaded last checkpoint:")
		gui_text(" - Please don't go below sea level")
		gui_text(" - Please don't try to leave the island")
		gui_end()
	end

end