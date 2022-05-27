-------------------------------------------------------------------------------

-- create the flee state

-------------------------------------------------------------------------------
state_flee = {}


state_flee["enter"] = function(player)



end


state_flee["execute"] = function(player)



end


state_flee["exit"] = function(player)


end

state_flee["onMessage"] = function(player, msg)


end

-------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
state_global = {}


state_global["enter"] = function(player)
  print("Entering global state")


end


state_global["execute"] = function(player)
  --print("in global")
  if(player.health < 0) then
    player.dead = true
  end

end


state_global["exit"] = function(player)

end

state_global["onMessage"] = function(player, msg)

  return false

end

-------------------------------------------------------------------------------

-- create the idle state

-------------------------------------------------------------------------------
state_idle = {}


state_idle["enter"] = function(player)
  print("Entering idle state")



end


state_idle["execute"] = function(player)
  if(player.dead == true) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Idle -> Death")
    player:getFSM():changeState("state_death")
  end

  local pos = vector2D.new()
  pos:set(camera_pos_x(), camera_pos_z())
  player:set_target_position(pos.x, pos.y)

  local playerX = player:getX()
  local playerZ = player:getZ()

  local distance = vector2Length(pos.x - playerX, pos.y - playerZ)


  if (distance < 5) then
    player:moveNPC(camera_pos_x(), camera_pos_z(), 0.1)
  else
    --player:pathfindToPoint(playerX, playerZ, pos.x, pos.y)
    --player:followWaypoint(false)
    if(player:followWaypoint(false)) then
      player:pathfindToPoint(playerX, playerZ, pos.x, pos.y)
    end
  end
end


state_idle["exit"] = function(player)

end

state_idle["onMessage"] = function(player, msg)
  if (msg.msg == 2) then
    player.health = player.health - msg.extraInfo
  end


end

-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
state_patrol = {}


state_patrol["enter"] = function(player)



end


state_patrol["execute"] = function(player)
  if(player:watchForEnemy(10)) then
    print("Enemy spotted")

    local target = entityManager.getEntity(player.target_id)
    local targetPos = vector2D.new()
    targetPos:set(target:getX(), target:getZ())

    print("Entity: ", player.id, " | Faction: ", player.faction, " | Patrol -> Chase")
    player:sendGroupMessage(0, player.faction, 25, player.id, 1, targetPos)
    player:getFSM():changeState("state_chase")
  end
end


state_patrol["exit"] = function(player)

end

state_patrol["onMessage"] = function(player, msg)
  if (msg.msg == 1) then
    player:set_target_position(msg.extraInfo.x, msg.extraInfo.y)
    player.target_id = -1
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Patrol -> Search")
    player:getFSM():changeState("state_search")
  end

end

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
state_chase = {}


state_chase["enter"] = function(player)


end


state_chase["execute"] = function(player)
  --print("In chase")

  if(player:moveToEnemy(1)) then
      print("Entity: ", player.id, " | Faction: ", player.faction, " | Chase -> Attack")
      player:getFSM():changeState("state_attack")
  end


end


state_chase["exit"] = function(player)



end

state_chase["onMessage"] = function(player, msg)



end


-------------------------------------------------------------------------------

-- create the attack state

-------------------------------------------------------------------------------
state_attack = {}

state_attack["enter"] = function(player)


end

state_attack["execute"] = function(player)
  player:stopMovement();

  local entityMgr = entityManager.new()
  local target = entityMgr.getEntity(player.target_id)

  if(target.dead == true) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Attack -> Patrol")
    player:getFSM():changeState("state_patrol")
  end

  local vec = vector2D.new()
  vec:set(player:getX() - target:getX(), player:getZ() - target:getZ())


  dist = vec:length()

  if(dist > 2) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Attack -> Chase")
    player:getFSM():changeState("state_chase")
  else
    player:sendMessage(0, player.id, player.target_id, 2, player.power)
  end


end


state_attack["exit"] = function(player)



end

state_attack["onMessage"] = function(player, msg)



end


-------------------------------------------------------------------------------

-- create the search state

-------------------------------------------------------------------------------
state_search = {}


state_search["enter"] = function(player)

end


state_search["execute"] = function(player)

  if(player.target_id == -1) then
    local pos = player:get_target_position()
    player:pathfindToPoint(player:getX(), player:getZ(), pos.x, pos.y)
    player.target_id = -2
  end

  if(player:watchForEnemy(10)) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Search -> Chase")
    player:getFSM():changeState("state_chase")
  end

  if(player:followWaypoint(false)) then
    if(player:numberOfWaypoints() == 0) then
      print("Entity: ", player.id, " | Faction: ", player.faction, " | Search -> Patrol")
      player:getFSM():changeState("state_patrol")
    end
  end

end

state_search["exit"] = function(player)



end

state_search["onMessage"] = function(player, msg)
  if (msg.msg == 1) then
    print(msg.extraInfo.x)
    print(msg.extraInfo.y)
    player.target_id = -1
    player:set_target_position(msg.extraInfo:getX(), msg.extraInfo:getY())
    player:getFSM():changeState("state_search")
  end


end

-------------------------------------------------------------------------------

-- create the death state

-------------------------------------------------------------------------------
state_death = {}


state_death["enter"] = function(player)

end


state_death["execute"] = function(player)
  player:stopMovement()


end


state_death["exit"] = function(player)


end

state_death["onMessage"] = function(player, msg)


end