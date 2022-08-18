#include <catch2/catch_test_macros.hpp>

#include "View/Renderer/OpenGL/Objects/Shader.hpp"
#include "Controller/ReflexEngine/Window.hpp"

TEST_CASE("Shader uniforms") {
	Window window(0, 0);
	window.init();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	SECTION("Default shader uniforms") {
		Shader shader;

		shader.CompileFile("shaders/shader.vert", "shaders/shader.frag");

		REQUIRE(shader.GetModelLocation() != 0);
	}
}
