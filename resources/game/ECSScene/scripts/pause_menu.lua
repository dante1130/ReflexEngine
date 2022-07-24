gui_setWindowSize(300, 300, 1)
gui_setWindowPos(0, 0, 1)

gui_begin("Pause Menu")

gui_text("--Game is currently paused--")
local unpause = gui_button("UNPAUSE", 150, 50)
local save = gui_button("SAVE", 150, 50)
local load = gui_button("LOAD", 150, 50)
local credits = gui_button("EXIT", 150, 50)
gui_text("gui frame rate: " .. gui_guiFrameRate())

gui_end()

if (unpause) then
	Window.set_cursor_visible(false)
	Time.set_pause(false)
end

if (credits) then
	setBoolData("show_credits", true)
end

if (getBoolData("show_credits", false)) then
	dofile "game/ECSScene/scripts/credits_menu.lua"
end
