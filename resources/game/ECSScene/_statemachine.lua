------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
state_global = {}

state_global["enter"] = function(entity)

end

state_global["execute"] = function(entity)
print(var.health)
print(var.faction)
print(var.damage)
print("in global state - statemachine.lua")

local transform = entity:get_transform_component()
local position = transform.position
print(position.x)
end

state_global["exit"] = function(entity)

end

state_global["onMessage"] = function(entity)

end


-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
state_patrol = {}

state_patrol["enter"] = function(entity)

end

state_patrol["execute"] = function(entity)
  print("in patrol state - statemachine.lua")

  local statemachine = entity:get_statemachine_component()
  statemachine:change_state("state_flee")
end


state_patrol["exit"] = function(entity)
  print("exiting patrol")
end

state_patrol["onMessage"] = function(entity)

end


-------------------------------------------------------------------------------

-- create the flee state

-------------------------------------------------------------------------------
state_flee = {}

state_flee["enter"] = function(entity)
  print("entering flee")
end

state_flee["execute"] = function(entity)
  print("in flee state - statemachine.lua")
end


state_flee["exit"] = function(entity)

end

state_flee["onMessage"] = function(entity)

end