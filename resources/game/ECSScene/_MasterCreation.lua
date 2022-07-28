dofile "game/ECSScene/_Materials.lua"
dofile "game/ECSScene/_statemachine.lua"

Scene.add_game_object("game/ECSScene/game_objects/Cat.lua")
Scene.add_game_object("game/ECSScene/game_objects/moonlight.lua")
Scene.add_game_object("game/ECSScene/game_objects/player.lua")
Scene.add_game_object("game/ECSScene/game_objects/flashlight.lua")
Scene.add_game_object("game/ECSScene/game_objects/boat.lua")
Scene.add_game_object("game/ECSScene/game_objects/escape_boat.lua")
Scene.add_game_object("game/ECSScene/game_objects/lighthouse.lua")
Scene.add_game_object("game/ECSScene/game_objects/water.lua")
Scene.add_game_object("game/ECSScene/game_objects/big_arrow.lua")
Scene.add_game_object("game/ECSScene/game_objects/terrain.lua")

--AI game objects
Scene.add_game_object("game/ECSScene/game_objects/AI/duck.lua")
Scene.add_game_object("game/ECSScene/game_objects/AI/duckTwo.lua")



Skybox.use_skybox("nightsky")
