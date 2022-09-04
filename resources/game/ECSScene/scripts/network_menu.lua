gui_setWindowSize(300, 300, 2)
gui_setWindowPos(500, 0, 1)

gui_begin("Network Menu")

gui_text("--This is the network test menu--")
local Init = gui_button("Init", 150, 50)
local Start = gui_button("Start Server", 150, 50)
local ServerIP = gui_luaInputText("Enter Server IP: ")
if network_return_IP() ~= nil then
	fullIP = network_return_IP()
else
	fullIP = ""
end
gui_text(fullIP)
local Connect = gui_button("Connect", 150, 50)
--local Exit = gui_button("Exit Menu", 150, 50)

if (network_connection_status() == true) then
		gui_text("You are connected!")
	else
		gui_text("You are not connected")
end

gui_end()

network_retain_IP(ServerIP)

if (Init) then
	create_network_manager(true)
end


if(Start) then
	start_server(true)
end

if(Connect) then
	network_client_connect()
end

if(network_connection_status()) then
	dofile "game/ECSScene/scripts/network_chat_send_menu.lua"
	dofile "game/ECSScene/scripts/network_chat_read_menu.lua"
end

if(Time.is_paused()==false) then
	network_terminate()
end
