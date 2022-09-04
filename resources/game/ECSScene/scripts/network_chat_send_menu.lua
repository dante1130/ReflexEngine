gui_setWindowSize(300, 300, 2)
gui_setWindowPos(0, 500, 1)

gui_begin("Chat sender")

local message = gui_luaInputText("Message: ")
if network_return_message() ~= nil then
	savedMessage = network_return_message()
else
	savedMessage = ""
end
gui_text(savedMessage)
local send = gui_button("Send", 300, 50)


network_retain_message(message)

if send then
	network_send_message()
end

gui_end()
