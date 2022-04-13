#pragma once

/**
 * @class Renderer
 * @brief An abstract class to represent a renderer, this can be derived into
 * other renderers such as OpenGL or DirectX.
 */
class Renderer {
public:
	/**
	 * @brief Initializes the renderer.
	 */
	virtual void init() = 0;

	/**
	 * @brief Draws the scene using the renderer.
	 */
	virtual void draw() = 0;

	/**
	 * @brief Toggles between normal and wireframe rendering.
	 */
	virtual void toggle_wireframe() = 0;

	/**
	 * @brief Destructor.
	 */
	virtual ~Renderer() = default;
};
