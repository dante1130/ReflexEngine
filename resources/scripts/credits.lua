if get_credits() then
    gui_setWindowSize(640, 480, 2)
    gui_setWindowPos(320, 0, 1)
    gui_begin("Credits")
    gui_text("Credits")
    gui_image("credits")
    local exit = gui_button("EXIT", 150, 50)
    gui_end()

    if exit then
        exit_game()
    end
end