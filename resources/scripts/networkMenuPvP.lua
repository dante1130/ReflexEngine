if get_pvp_network_menu() then
	gui_setWindowSize(700, 400, 2)
	gui_setWindowPos(0, 300, 2)
	gui_begin("PvP Network Menu")

	gui_text("--Game is not really paused (but it may be)--")
	gui_text("This menu IS DIFFERENT to the chat network menu")
	local initialise = gui_button("INITIALISE", 150, 50)
	local start = gui_button("Start Server", 150, 50)
	local ip = gui_luaInputText("Enter Server IP: ")
	if network_return_IP() ~= nil then
		fullIP = network_return_IP()
	else
		fullIP = ""
	end
	gui_text(fullIP)
	local connect = gui_button("Connect to server (127.0.0.1 if on same PC)", 300, 50)
	
	local back = gui_button("Exit Menu (but stay connected)", 150,50)
	local kill_session = gui_button("End Session",150,50)
	
	network_retain_IP(ip)
	
	if initialise then
		create_network_manager(true)
	end
	
	if start then
		start_server(true)
	end

	if connect then
		network_client_connect()
	end
	
	if network_pvp_connection_status() == true then
		gui_text("You are connected!")
	else
		gui_text("You are not connected")
	end
	
	if back then
		exit_pvp_network_menu(false)
	end

	if kill_session then
		network_terminate()
		exit_pvp_network_menu(false)
	end


	gui_end()
end