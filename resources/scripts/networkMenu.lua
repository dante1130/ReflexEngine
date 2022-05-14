if get_network_menu() then
	gui_setWindowSize(700, 400, 2)
	gui_setWindowPos(0, 300, 2)
	gui_begin("Network Menu")

	gui_text("--Game is currently NOT paused--")
	local initialise = gui_button("INITIALISE", 150, 50)
	local start = gui_button("Start Server", 150, 50)
	local ip = gui_luaInputText("Enter Server IP: ")
	if network_return_IP() ~= nil then
		fullIP = network_return_IP()
	else
		fullIP = ""
	end
	gui_text(fullIP)
	local username = gui_luaInputText("Username: ")
	if network_return_username() ~= nil then
		fullusername = network_return_username()
	else
		fullusername = ""
	end
	gui_text("Your username is: " .. fullusername)
	local saveUsername = gui_button("Save username", 200, 50)
	local connect = gui_button("Connect to server (127.0.0.1 if on same PC)", 300, 50)
	
	local back = gui_button("Exit Menu",150,50)
	
	network_retain_IP(ip)

	network_retain_username(username)
	
	if initialise then
		create_network_manager(true)
	end
	
	if start then
		start_server(true)
	end

	if(saveUsername) then
		network_set_username()
	end

	if connect then
		network_client_connect()
	end
	
	if network_connection_status() == true then
		gui_text("You are connected!")
	else
		gui_text("You are not connected")
	end
	
	if back then
		network_terminate()
		exit_network_menu(false)
	end


	gui_end()
end