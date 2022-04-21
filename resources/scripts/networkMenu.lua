if get_network_menu() then
	gui_setWindowSize(700, 400, 2)
	gui_setWindowPos(0, 800, 2)
	gui_begin("Network Menu")

	gui_text("--Game is currently NOT paused--")
	local initialise = gui_button("INITIALISE", 150, 50)
	local start = gui_button("Start Server", 150, 50)
	local ip = gui_luaInputText("Enter Server IP: ")
	if ip ~= nil or ip ~='' or ip ~= '\0' then
		fullIP = ip
	else
		fullIP = ""
	end
	gui_text(fullIP)
	local name = gui_luaInputText("Name: ")
	local connect = gui_button("Connect to server", 150, 50)
	local connectLocal = gui_button("Connect to local server (if on same PC)", 200, 50)
	
	local back = gui_button("Exit Menu",150,50)
	
	network_retain_IP(ip)
	
	if initialise then
		create_network_manager()
	end
	
	if start then
		start_server(true)
	end

	if connect then
		network_client_connect(fullIP)
	end
	
	if connectLocal then
		network_client_connect("127.0.0.1")
	end
	
	if network_connection_status() == true then
		gui_text("You are connected!")
	else
		gui_text("You are not connected")
	end
	
	if back then
		network_terminate()
		exit_network_menu()
	end


	gui_end()
end