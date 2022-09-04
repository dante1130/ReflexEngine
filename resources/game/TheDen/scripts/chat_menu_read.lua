	gui_setWindowSize(300, 400, 4)
	gui_setWindowPos(200, 500, 4)
	gui_begin("Chat reader")

	gui_text("--Game is currently NOT paused--")
	gui_text("Chat Window")
	if chatLog == nil then
		chatLog = "This is the beginning of the chat log\n"
	end
	if network_get_message() ~= " " then
		chatLog = chatLog .. network_get_message()
		--chatLog = chatLog .. "\nValid Message\n"
	end
	gui_text(chatLog)
	
	gui_end()