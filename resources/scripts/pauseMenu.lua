gui_setWindowSize(300, 300, 1)
gui_setWindowPos(0, 0, 1)


gui_begin("Pause Menu")

gui_text("--Game is currently paused--")
local unpause = gui_button("UNPAUSE", 150, 50)
local save = gui_button("SAVE", 150, 50)
local load = gui_button("LOAD", 150, 50)
local exit = gui_button("EXIT", 150, 50)
gui_text("gui frame rate: " .. gui_guiFrameRate())

if unpause then
	--Call unpause method
end

if save then
	--Call save method
end

if load then
	--Call load method
end

if exit then
	--Call exit method
end


gui_end()