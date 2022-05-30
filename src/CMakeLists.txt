target_sources(${PROJECT_NAME} PRIVATE
    main.cpp

	NetworkManager.cpp

	Model/GameObject/GameObject.hpp
	Model/GameObject/Item.cpp
	Model/GameObject/Water.cpp
	Model/GameObject/Body.cpp
	Model/GameObject/BodyRigid.cpp
	Model/GameObject/PhysicsObject.cpp
	Model/GameObject/ScriptableObject.cpp
	Model/GameObject/Player.cpp
	Model/GameObject/TerrainObject.cpp
	Model/GameObject/SkyboxObject.cpp
	Model/GameObject/DirectionalLightObject.cpp
	Model/GameObject/PointLightObject.cpp
	Model/GameObject/SpotLightObject.cpp
	Model/LightData.hpp
	Model/ModelData.cpp
	Model/GameObject/Projectile.cpp
	Model/GameObject/NetworkedItem.cpp
	
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
	View/Renderer/OpenGL/Objects/Md2Model.cpp
	View/guiManager.cpp

	Controller/ReflexEngine/ReflexEngine.cpp
	Controller/ReflexEngine/EngineTime.cpp
	Controller/ReflexEngine/Window.cpp
	Controller/ReflexEngine/Camera.cpp
	Controller/ResourceManager/ResourceManager.cpp
	Controller/ResourceManager/TextureManager.cpp
	Controller/ResourceManager/ModelManager.cpp
	Controller/ResourceManager/Md2ModelManager.cpp
	Controller/ResourceManager/MaterialManager.cpp
	Controller/ResourceManager/ObjectSaving.cpp
	Controller/Input/InputManager.cpp
	Controller/Input/InputState.cpp
	Controller/Input/Input.hpp
	Controller/Audio/Audio.cpp
	Controller/Audio/AudioStopReceiver.cpp
	Controller/Pathfinding/AStar.cpp
	Controller/Pathfinding/AStarInterface.cpp
	Controller/Terrain/Terrain.cpp
	Controller/Terrain/BTT.cpp
	Controller/Terrain/BttController.cpp
	Controller/Terrain/TexturedTerrain.cpp
	Controller/GameAssetFactory.cpp
	Controller/LuaManager.cpp
	Controller/Physics/Physics.cpp
	Controller/Physics/BodyRigidPhysics.cpp
	Controller/Physics/physicsEntityManager.cpp
	Controller/Physics/collision.cpp
	Controller/GenericFunctions.cpp
	Controller/multiTextureCreator.cpp
	
	AI/messageDispatcher.cpp
	AI/NPC.cpp
	AI/entityManager.cpp
	AI/movement.cpp
	AI/world.cpp
	AI/luaAccessScriptedFSM.cpp
	AI/Counter.cpp
	AI/vector2D.cpp

	

	Game/Scene.hpp
	Game/TestScene.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
