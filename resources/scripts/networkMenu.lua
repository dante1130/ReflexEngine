if get_network_menu() then
	gui_setWindowSize(600, 300, 2)
	gui_setWindowPos(0, 800, 2)
	gui_begin("Network Menu")

	gui_text("--Game is currently NOT paused--")
	local initialise = gui_button("INITIALISE", 150, 50)
	local start = gui_button("Start Server", 150, 50)
	local ip = gui_luaInputText("Enter Server IP (or 127.0.0.1 if local): ")
	local name = gui_luaInputText("Name: ")
	local connect = gui_button("Connect to server", 150, 50)

	local back = gui_button("Exit Menu",150,50)

	if initialise then
		create_network_manager()
	end
	
	if start then
		start_server(true)
	end

	if connect then
		network_client_connect(ip)
	end
	

	if back then
		network_terminate()
		exit_network_menu()
	end


	gui_end()
end