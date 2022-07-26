#pragma once

#include <reactphysics3d/reactphysics3d.h>

#include "View/Renderer/OpenGL/Objects/Shader.hpp"
#include "View/Renderer/OpenGL/Objects/Mesh.hpp"

class ColliderRenderer {
public:
	ColliderRenderer() = default;

	void update(const reactphysics3d::DebugRenderer& debug_renderer);

	void draw(const Shader& shader);

private:
	Mesh line_mesh_;
	Mesh triangle_mesh_;
};