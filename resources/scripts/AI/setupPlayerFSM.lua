           -------------------------------------------------------------------------------

-- Initialise a players FSM
-- this would normally be done at the same time as loading the player data from file

-------------------------------------------------------------------------------
print("At start of setupPlayerFSM")



function setupPlayerFSM(player)
    print("In setupPlayerFSM")
    
    player:getFSM():setGlobalState("state_global")
    player:getFSM():setCurrentState("state_idle")
end

function setupDuckFSM(player)
    print("Setting up Duck FSM")

    player:getFSM():setGlobalState("state_global")
    player:getFSM():setCurrentState("state_patrol")
end

function setupHumanFSM(player)
    print("Setting up Human FSM")

    player:getFSM():setGlobalState("state_global")
    player:getFSM():setCurrentState("state_patrol")
end


print("At end of setupPlayerFSM")