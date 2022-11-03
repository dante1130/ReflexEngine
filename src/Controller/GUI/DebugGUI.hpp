#pragma once

namespace DebugGUI {
/**
 * @brief Draws the debug gui window.
 *
 */
void draw();

/**
 * @brief Draws the options for changing the physics debug renderer
 *
 */
auto draw_physics_debug_render_options() -> void;

}  // namespace DebugGUI
