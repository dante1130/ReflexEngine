gui_setWindowSize(300, 300, 2)
gui_setWindowPos(300, 500, 1)

gui_begin("Chat reader")
	gui_text("Chat Window")
	if chatLog == nil then
		chatLog = "This is the beginning of the chat log\n"
	end
	if network_get_message() ~= " " then
		chatLog = chatLog .. network_get_message()
	end
	gui_text(chatLog)

gui_end()
