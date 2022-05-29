           -------------------------------------------------------------------------------

-- Initialise a players FSM
-- this would normally be done at the same time as loading the player data from file

-------------------------------------------------------------------------------

function setupPlayerFSM(player)
    player:getFSM():setGlobalState("state_global")
    player:getFSM():setCurrentState("state_player")
end

function setupDuckFSM(player)
    player:getFSM():setGlobalState("state_global")
    player:getFSM():setCurrentState("state_patrol")
end

function setupGhostFSM(player)
    player:getFSM():setGlobalState("state_global")
    player:getFSM():setCurrentState("state_ghost_idle")
end