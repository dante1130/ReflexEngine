#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <numbers>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "CommonValues.hpp"

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Material.hpp"
#include "SpotLight.hpp"
#include "Model.hpp"
#include "Skybox.hpp"

class ReflexEngine
{
public:

private:
	static Window mainWindow;

	static Shader* shader;
	static Shader* directionalShadowShader;
	static Shader* omniShadowShader;

	
};