------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
state_global = {}

state_global["enter"] = function(ecs, entity)

end

state_global["execute"] = function(ecs, entity)
	--print("in global state - statemachine.lua")

	--local transform = entity:get_transform_component()
	--local position = transform.position
	--print(position.x)
end

state_global["exit"] = function(ecs, entity)

end

state_global["onMessage"] = function(ecs, entity, msg)
print("Incomming message in global state")
end


-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
state_patrol = {}

state_patrol["enter"] = function(ecs, entity)
  print("entering patrol")
end

state_patrol["execute"] = function(ecs, entity)
  statemachine_helper.change_state(ecs, entity, "state_flee")
end


state_patrol["exit"] = function(ecs, entity)
  print("exiting patrol")
end

state_patrol["onMessage"] = function(ecs, entity, msg)
print("Incomming message in patrol state")
end


-------------------------------------------------------------------------------

-- create the flee state

-------------------------------------------------------------------------------
state_flee = {}

state_flee["enter"] = function(ecs, entity)
  print("entering flee")
end

state_flee["execute"] = function(ecs, entity)
  --print("in flee state - statemachine.lua")
end


state_flee["exit"] = function(ecs, entity)
  print("exiting flee")
end

state_flee["onMessage"] = function(ecs, entity, msg)
print("Incomming message in flee state")
	if(msg.msg == 0) then
		print("Will stop being a baby")
		statemachine_helper.change_state(ecs, entity, "state_patrol")
	end
end


-------------------------------------------------------------------------------

-- create the chad state

-------------------------------------------------------------------------------
state_chad = {}

state_chad["enter"] = function(ecs, entity)
  print("entering chad")
end

state_chad["execute"] = function(ecs, entity)

  local transform = entity:get_transform_component()
  local position = transform.position

  --statemachine_helper.send_area_message(ecs, entity, 100, 0, var)
  --local target = Math.vec3.new(250, position.y, position.z)
  --statemachine_helper.follow_waypoint(entity, target, 10, "terrain")
  statemachine_helper.look_for_enemy(ecs, entity, 90, 100)

end


state_chad["exit"] = function(ecs, entity)

end

state_chad["onMessage"] = function(ecs, entity, msg)
print("Incomming message in chad state")
end