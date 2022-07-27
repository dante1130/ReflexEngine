------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
state_global = {}

state_global["enter"] = function(registry, entity)

end

state_global["execute"] = function(registry, entity)
print(var.health)
print(var.faction)
print(var.damage)
print("in global state - statemachine.lua")

local transform = entity:get_transform_component()
local position = transform.position
print(position.x)
end

state_global["exit"] = function(registry, entity)

end

state_global["onMessage"] = function(registry, entity)

end


-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
state_patrol = {}

state_patrol["enter"] = function(registry, entity)

end

state_patrol["execute"] = function(registry, entity)
  print("in patrol state - statemachine.lua")
  statemachine_helper.change_state(registry, entity, "state_flee")
  print("asdfasddfstatemachine.lua")
end


state_patrol["exit"] = function(registry, entity)
  print("exiting patrol")
end

state_patrol["onMessage"] = function(registry, entity)

end


-------------------------------------------------------------------------------

-- create the flee state

-------------------------------------------------------------------------------
state_flee = {}

state_flee["enter"] = function(registry, entity)
  print("entering flee")
end

state_flee["execute"] = function(registry, entity)
  print("in flee state - statemachine.lua")
end


state_flee["exit"] = function(registry, entity)

end

state_flee["onMessage"] = function(registry, entity)

end