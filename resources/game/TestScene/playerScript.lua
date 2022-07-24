if camera_pos_y() < 2.5 then
	if get_pause_game() == false then
		local check = current_time() - getIntData("last_load_time", -5)
		if check > 5 then
			setIntData("last_load_time", current_time())
			setBoolData("load_game", true)
		end
	end
else
	local time = current_time() - getIntData("last_save_time", -15)
	if time > 15 then
		setIntData("last_save_time", current_time())
		setBoolData("save_game", true)
		print("Checkpoint - 15 seconds passed since last encounter")
	end

	time = current_time() - getIntData("last_load_time", -5)
	if time < 10 then
		gui_setWindowSize(300, 100, 1)
		gui_setWindowPos(700, 0, 1)
		gui_begin("SAVE LOADED ")
		gui_text("Reloaded last checkpoint:")
		gui_text(" - Please don't go below sea level")
		gui_text(" - Please don't try to leave the island")
		gui_end()
	end

end
