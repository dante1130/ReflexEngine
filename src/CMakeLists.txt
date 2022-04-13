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
	Terrain.cpp
	BruteForceTerrain.cpp
	TexturedTerrain.cpp

	guiManager.cpp

	Model/GameObject/GameObject.hpp
	Model/GameObject/Item.cpp

	View/Renderer/OpenGL/OpenGL.cpp

	Controller/ReflexEngine/ReflexEngine.cpp

	Game/Scene.hpp
	Game/TestScene.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
