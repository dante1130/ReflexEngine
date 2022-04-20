target_sources(${PROJECT_NAME} PRIVATE
    main.cpp

	AStar.cpp
	AStarInterface.cpp
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
	Model/GameObject/Player.cpp
	
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
	Controller/ReflexEngine/Window.cpp
	Controller/ReflexEngine/Camera.cpp
	Controller/ResourceManager/ResourceManager.cpp
	Controller/ResourceManager/TextureManager.cpp
	Controller/ResourceManager/ModelManager.cpp
	Controller/ResourceManager/MaterialManager.cpp
	Controller/ResourceManager/ObjectSaving.cpp
	Controller/Input/InputManager.cpp
	Controller/Input/InputState.cpp
	Controller/Input/Input.hpp
	Controller/LuaManager.cpp
	Controller/Physics.cpp
	Controller/BodyRigidPhysics.cpp
	Controller/GuiLuaAccess.cpp
	Controller/GenericFunctions.cpp
	Controller/multiTextureCreator.cpp
	
	Game/Scene.hpp
	Game/TestScene.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
