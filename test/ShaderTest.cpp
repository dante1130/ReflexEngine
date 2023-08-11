#include <catch2/catch_test_macros.hpp>

#include "View/Renderer/OpenGL/Objects/Shader.hpp"
#include "Controller/ReflexEngine/Window.hpp"

bool is_valid_uniform(GLint uniform_location) {
	return uniform_location != -1 && uniform_location != GL_INVALID_VALUE &&
	       uniform_location != GL_INVALID_OPERATION;
}

TEST_CASE("Shader uniforms", "[OpenGL]") {
	Window window(1, 1);
	window.init();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	SECTION("Default shader uniforms") {
		Shader shader;

		shader.CompileFile("shaders/shader.vert", "shaders/shader.frag");

		REQUIRE(is_valid_uniform(shader.GetProjectionLocation()));
		REQUIRE(is_valid_uniform(shader.GetModelLocation()));
		REQUIRE(is_valid_uniform(shader.GetViewLocation()));
		REQUIRE(is_valid_uniform(shader.GetEyePositionLocation()));
		REQUIRE(is_valid_uniform(shader.GetAmbientIntensityLocation()));
		REQUIRE(is_valid_uniform(shader.GetAmbientIntensityColor()));
		REQUIRE(is_valid_uniform(shader.GetDiffuseIntensityLocation()));
		REQUIRE(is_valid_uniform(shader.GetDirectionLocation()));
		REQUIRE(is_valid_uniform(shader.GetSpecularIntensityLocation()));
		REQUIRE(is_valid_uniform(shader.GetShininessLocation()));
		REQUIRE(is_valid_uniform(shader.GetUsingTexture()));
		REQUIRE(is_valid_uniform(shader.get_using_detailmap()));
	}

	SECTION("Skybox shader uniforms") {
		Shader shader;

		shader.CompileFile("shaders/skybox.vert", "shaders/skybox.frag");

		REQUIRE(is_valid_uniform(shader.GetProjectionLocation()));
		REQUIRE(is_valid_uniform(shader.GetViewLocation()));
	}

	SECTION("Directional shadow shader uniforms") {
		Shader shader;

		shader.CompileFile("shaders/directional_shadow_map.vert",
		                   "shaders/directional_shadow_map.frag");

		REQUIRE(is_valid_uniform(shader.GetModelLocation()));
		REQUIRE(is_valid_uniform(shader.get_uniform_light_transform()));
	}

	SECTION("Omnidirectional shadow shader uniforms") {
		Shader shader;

		shader.CompileFile("shaders/omni_shadow_map.vert",
		                   "shaders/omni_shadow_map.frag");

		REQUIRE(is_valid_uniform(shader.GetModelLocation()));
		REQUIRE(is_valid_uniform(shader.GetFarPlaneLocation()));
		REQUIRE(is_valid_uniform(shader.GetOmniLightPosLocation()));
	}

	SECTION("React shader uniforms") {
		Shader shader;

		shader.CompileFile("shaders/react.vert", "shaders/react.frag");

		REQUIRE(is_valid_uniform(shader.GetProjectionLocation()));
		REQUIRE(is_valid_uniform(shader.GetViewLocation()));
	}
}
