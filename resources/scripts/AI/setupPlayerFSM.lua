           -------------------------------------------------------------------------------

-- Initialise a players FSM
-- this would normally be done at the same time as loading the player data from file

-------------------------------------------------------------------------------
print("At start of setupPlayerFSM")



function setupPlayerFSM(player)
    print("In setupPlayerFSM")
    print(player.id)
    player.id = 7
    player.faction = 1
    print(player.id)
    
    player:getFSM():setGlobalState("state_global")
    player:getFSM():setCurrentState("state_idle")
    print("End of in setupPlayerFSM")
end


print("At end of setupPlayerFSM")