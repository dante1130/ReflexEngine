gui_setWindowSize(250, 250, 2)
gui_setWindowPos(600, 0, 2)
gui_begin("IMPORTANT")
gui_text("There once was a man named Daniel")

local isOpen = gui_collapsingHeader("Collapsable header")
if isOpen == true then
	gui_text("What is up gammerz")
end

gui_progressBar(55)
local frameRate = gui_guiFrameRate()
gui_text("gui frame rate: " .. frameRate)

local isPressed = gui_button("PRESS ME", 150, 20)
if isPressed == true then
	gui_text("WHY DID YOU PRESS ME?")
end

local input = gui_luaInputText("Enter here: ")
gui_text("Player input = " .. input)

checkBoxBool = false
checkBoxBool = gui_luaCheckbox("Check box", checkBoxBool)
if checkBoxBool then
	gui_text("Box has been checked")
end

cbool = false
cbool = gui_luaCheckbox("box", cbool)
if cbool then
	gui_text("Box has been checked")
end

gui_end()
