target_sources(${PROJECT_NAME} PRIVATE
    main.cpp

	AStar.cpp
	AStarInterface.cpp
	Camera.cpp
	Window.cpp
	Terrain.cpp
	BruteForceTerrain.cpp
	TexturedTerrain.cpp
	GameAssetFactory.cpp
	guiManager.cpp

	Model/GameObject/GameObject.hpp
	Model/GameObject/Item.cpp
	Model/GameObject/Water.cpp
	Model/GameObject/Body.cpp
	Model/GameObject/BodyRigid.cpp
	Model/GameObject/PhysicsObject.cpp
	Model/GameObject/ScriptableObject.cpp
	
	View/Renderer/OpenGL/OpenGL.cpp
	View/Renderer/OpenGL/Objects/Light.cpp
	View/Renderer/OpenGL/Objects/DirectionalLight.cpp
	View/Renderer/OpenGL/Objects/PointLight.cpp
	View/Renderer/OpenGL/Objects/SpotLight.cpp
	View/Renderer/OpenGL/Objects/Material.cpp
	View/Renderer/OpenGL/Objects/Mesh.cpp
	View/Renderer/OpenGL/Objects/Model.cpp
	View/Renderer/OpenGL/Objects/Shader.cpp
	View/Renderer/OpenGL/Objects/ShadowMap.cpp
	View/Renderer/OpenGL/Objects/OmniShadowMap.cpp
	View/Renderer/OpenGL/Objects/Skybox.cpp
	View/Renderer/OpenGL/Objects/Texture.cpp

	Controller/ReflexEngine/ReflexEngine.cpp
	Controller/ResourceManager/ResourceManager.cpp
	Controller/ResourceManager/TextureManager.cpp
	Controller/ResourceManager/ModelManager.cpp
	Controller/LuaManager.cpp
	Controller/Physics.cpp
	Controller/BodyRigidPhysics.cpp
	Controller/MaterialLuaController.cpp
	Controller/GuiLuaAccess.cpp
	Controller/GenericFunctions.cpp
	Controller/ResourceManager/ObjectSaving.cpp

	Game/Scene.hpp
	Game/TestScene.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
