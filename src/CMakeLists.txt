target_sources(${PROJECT_NAME} PRIVATE
    main.cpp

	AStar.cpp
	AStarInterface.cpp
	Camera.cpp
	Light.cpp
	DirectionalLight.cpp
	PointLight.cpp
	SpotLight.cpp
	Material.cpp
	Mesh.cpp
	Model.cpp
	Shader.cpp
	ShadowMap.cpp
	OmniShadowMap.cpp
	Skybox.cpp
	Texture.cpp
	Window.cpp

	guiManager.cpp

	GameObject/GameObject.hpp
	GameObject/Item.cpp
	GameObject/Water.cpp

	Renderer/OpenGL/OpenGL.cpp

	Game/Scene.hpp
	Game/TestScene.cpp

	ReflexEngine/ReflexEngine.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
