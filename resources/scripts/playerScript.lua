if camera_pos_y() < 2 then
	if current_time() > 10 then
		local check = current_time() - time_since_last_load()
		if check > 5 then
			--load_game(true)
		end
	end	
else
	local time = current_time() - time_since_last_save()
	if time > 30 then
		save_game(true)
		print("Checkpoint - 30 seconds passed")
	end

	time = current_time() - time_since_last_load()
	if time < 10 then
		gui_setWindowSize(300, 100, 1)
		gui_setWindowPos(550, 0, 1)
		gui_begin("SAVE LOADED ")
		gui_text("Reloaded last checkpoint:")
		gui_text(" - Please don't go below sea level")
		gui_text(" - Please don't try to leave the island")
		gui_end()
	end

end