------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
state_global = {}

state_global["enter"] = function(ecs, entity)

end

state_global["execute"] = function(ecs, entity)
	print(var.health)
	print(var.faction)
	print(var.damage)
	print("in global state - statemachine.lua")

	local transform = entity:get_transform_component()
	local position = transform.position
	print(position.x)
end

state_global["exit"] = function(ecs, entity)

end

state_global["onMessage"] = function(ecs, entity)

end


-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
state_patrol = {}

state_patrol["enter"] = function(ecs, entity)

end

state_patrol["execute"] = function(ecs, entity)
  print("in patrol state - statemachine.lua")
  statemachine_helper.change_state(ecs, entity, "state_flee")
  print("asdfasddfstatemachine.lua")
end


state_patrol["exit"] = function(ecs, entity)
  print("exiting patrol")
end

state_patrol["onMessage"] = function(ecs, entity)

end


-------------------------------------------------------------------------------

-- create the flee state

-------------------------------------------------------------------------------
state_flee = {}

state_flee["enter"] = function(ecs, entity)
  print("entering flee")
end

state_flee["execute"] = function(ecs, entity)
  print("in flee state - statemachine.lua")
end


state_flee["exit"] = function(ecs, entity)

end

state_flee["onMessage"] = function(ecs, entity)

end