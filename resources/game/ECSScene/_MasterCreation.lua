dofile "game/ECSScene/_Materials.lua"
dofile "game/ECSScene/_statemachine.lua"

add_game_object("game/ECSScene/game_objects/Cat.lua")
add_game_object("game/ECSScene/game_objects/moonlight.lua")
add_game_object("game/ECSScene/game_objects/player.lua")
add_game_object("game/ECSScene/game_objects/flashlight.lua")
add_game_object("game/ECSScene/game_objects/boat.lua")
add_game_object("game/ECSScene/game_objects/escape_boat.lua")
add_game_object("game/ECSScene/game_objects/lighthouse.lua")
add_game_object("game/ECSScene/game_objects/water.lua")
add_game_object("game/ECSScene/game_objects/big_arrow.lua")
add_game_object("game/ECSScene/game_objects/terrain.lua")


--AI game objects
add_game_object("game/ECSScene/game_objects/AI/duck.lua")

Skybox.use_skybox("nightsky")
