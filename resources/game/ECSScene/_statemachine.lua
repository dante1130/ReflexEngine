-------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
state_global = {}

state_global["enter"] = function()

end

state_global["execute"] = function()
print("in global state - statemachine.lua")
end

state_global["exit"] = function()

end

state_global["onMessage"] = function()

end


-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
state_patrol = {}

state_patrol["enter"] = function()

end

state_patrol["execute"] = function()
  print("in patrol state - statemachine.lua")
end


state_patrol["exit"] = function()

end

state_patrol["onMessage"] = function()

end