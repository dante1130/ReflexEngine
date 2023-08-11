if(get_pause_game() == false and getBoolData("load_game", false) == false) then
	gui_setWindowSize(600, 50, 2)
	gui_setWindowPos(0, 0, 2)
	gui_begin("HEALTH")

	local entityMgr = entityManager.new()
	local player = entityMgr.getEntity(0)

	gui_progressBar(player.health)

	gui_end()
end