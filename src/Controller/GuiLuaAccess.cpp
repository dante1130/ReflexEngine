#include "GuiLuaAccess.hpp"

void guiLuaAccess::exposeGui() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("gui_begin", gui::begin);
	lua.set_function("gui_end", gui::end);
	lua.set_function("gui_setWindowPos", gui::setWindowPos);
	lua.set_function("gui_setWindowSize", gui::setWindowSize);
	lua.set_function("gui_checkbox", gui::checkbox);
	lua.set_function("gui_sliderFloat", gui::sliderFloat);
	lua.set_function("gui_sliderInt", gui::sliderInt);
	lua.set_function("gui_sliderAngle", gui::sliderAngle);
	lua.set_function("gui_colourEdit3", gui::colourEdit3);
	lua.set_function("gui_colourEdit4", gui::colourEdit4);
	lua.set_function("gui_inputText", gui::inputText);
	lua.set_function("gui_collapsingHeader", gui::collapsingHeader);
	lua.set_function("gui_progressBar", gui::progressBar);

	// lua.set_function("gui_button", gui::button);
	//  lua.set_function("gui_plotLines", gui::plotLines);
}
