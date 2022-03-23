#pragma once

class Renderer {
public:
	virtual void init() = 0;

	virtual void draw() = 0;

	virtual void toggle_wireframe() = 0;

	virtual ~Renderer() = default;
};
