-------------------------------------------------------------------------------

-- create the flee state

-------------------------------------------------------------------------------
state_player = {}


state_player["enter"] = function(player)
end


state_player["execute"] = function(player)
  if(player.dead) then
    load_game(true)
  end

  local pos = vector2D.new()
  pos:set(camera_pos_x(), camera_pos_z())
  player:setPos(pos)
  player:stopMovement()
end


state_player["exit"] = function(player)
end

state_player["onMessage"] = function(player, msg)
  if (msg.msg == 2) then
    player.health = player.health - msg.extraInfo
    player:sendGroupMessage(0, player.faction, 200, player.id, 3, 0)
  elseif(msg.msg == 4) then
    player.health = player.health + msg.extraInfo
  end

end


-------------------------------------------------------------------------------

-- create the medic idle state

-------------------------------------------------------------------------------
state_medic_idle = {}


state_medic_idle["enter"] = function(player)

end


state_medic_idle["execute"] = function(player)
  if(player.dead == true) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Medic Idle -> Death", " | Reason: Health 0")
    player:getFSM():changeState("state_death")
  end

  local pos = vector2D.new()
  pos:set(camera_pos_x(), camera_pos_z())
  player:set_target_position(pos.x, pos.y)

  local playerX = player:getX()
  local playerZ = player:getZ()

  local distance = vector2Length(pos.x - playerX, pos.y - playerZ)

  if (distance < 10) then
    if(distance > 5) then
      player:moveNPC(camera_pos_x(), camera_pos_z(), 0.1)
    else
      player:stopMovement()
    end
  else
    if(player:followWaypoint(false)) then
      player:pathfindToPoint(playerX, playerZ, pos.x, pos.y)
    end
  end
end


state_medic_idle["exit"] = function(player)

end

state_medic_idle["onMessage"] = function(player, msg)
  if (msg.msg == 2) then
    player.health = player.health - msg.extraInfo
  elseif(msg.msg == 3) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Medic Idle -> Medic Active", " | Reason: Help called")
    player:getFSM():changeState("state_medic_active")
  end


end

-------------------------------------------------------------------------------

-- create the medic active state

-------------------------------------------------------------------------------
state_medic_active = {}


state_medic_active["enter"] = function(player)

end


state_medic_active["execute"] = function(player)
  if(player.dead == true) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Medic Active -> Death", " | Reason: Health 0")
    player:getFSM():changeState("state_death")
  end

  local pos = vector2D.new()
  pos:set(camera_pos_x(), camera_pos_z())
  player:set_target_position(pos.x, pos.y)

  local playerX = player:getX()
  local playerZ = player:getZ()

  local distance = vector2Length(pos.x - playerX, pos.y - playerZ)

  if (distance < 10) then
    if(distance < 3) then
      player:sendGroupMessage(0, player.faction, 3, player.id, 1, 10)
      print("Entity: ", player.id, " | Faction: ", player.faction, " | Medic Active -> Medic Idle", " | Reason: Player healed")
      player:getFSM():changeState("state_medic_idle")
    else
      player:moveNPC(camera_pos_x(), camera_pos_z(), 0.1)
    end
  else
    if(player:followWaypoint(false)) then
      player:pathfindToPoint(playerX, playerZ, pos.x, pos.y)
    end
  end
end


state_medic_active["exit"] = function(player)

end

state_medic_active["onMessage"] = function(player, msg)
  if (msg.msg == 2) then
    player.health = player.health - msg.extraInfo
  end


end

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

end


state_global["execute"] = function(player)
  --print("in global")
  if(player.health <= 0) then
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

end


state_idle["execute"] = function(player)
  if(player.dead == true) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Idle -> Death", " | Reason: Health 0")
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
local animation = player:getAnimation();
animation:shouldAnimate(false)

end


state_patrol["execute"] = function(player)
  if(player:watchForEnemy(10)) then
    local target = entityManager.getEntity(player.target_id)
    local targetPos = vector2D.new()
    targetPos:set(target:getX(), target:getZ())

    print("Entity: ", player.id, " | Faction: ", player.faction, " | Patrol -> Chase", " | Reason: Enemy spotted")
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
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Patrol -> Search", " | Reason: Telegram recieved about target")
    player:getFSM():changeState("state_search")

  elseif (msg.msg == 5) then
    local pos = vector2D.new()
    pos:set(msg.extraInfo.x - player:getX(), msg.extraInfo.y - player:getZ())

    local dist = pos:length()
    if(dist < 15) then
      player.target_id = -1 
      player:set_target_position(msg.extraInfo.x, msg.extraInfo.y)
      print("Entity: ", player.id, " | Faction: ", player.faction, " | Patrol -> Search", " | Reason: I heard something")
      player:getFSM():changeState("state_search")
    end
  end

end

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
state_chase = {}


state_chase["enter"] = function(player)
local animation = player:getAnimation();
animation:shouldAnimate(true)
animation:setFPS(24)
animation:shouldLoop(true)
animation:setAnimation(animation_types.run)

end


state_chase["execute"] = function(player)
  --print("In chase")

  if(player:watchForEnemy(15) == false) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Chase -> Patrol", " | Reason: Target lost")
    player:getFSM():changeState("state_patrol")
  end

  player.moveSpeed = player.moveSpeed * 1.5
  if(player:moveToEnemy(1.5)) then
      print("Entity: ", player.id, " | Faction: ", player.faction, " | Chase -> Attack", " | Reason: In attack range")
      player:getFSM():changeState("state_attack")
  end

    player.moveSpeed = player.moveSpeed / 1.5

end


state_chase["exit"] = function(player)
local animation = player:getAnimation();
animation:setFPS(12)
end

state_chase["onMessage"] = function(player, msg)



end


-------------------------------------------------------------------------------

-- create the attack state

-------------------------------------------------------------------------------
state_attack = {}

state_attack["enter"] = function(player)
local animation = player:getAnimation();
animation:shouldAnimate(true)
animation:shouldLoop(false)
animation:setFPS(80)

end

state_attack["execute"] = function(player)
  player:stopMovement();

  local entityMgr = entityManager.new()
  local target = entityMgr.getEntity(player.target_id)

  if(target.dead == true) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Attack -> Patrol", " | Reason: Target died")
    player:getFSM():changeState("state_patrol")
  end

  local vec = vector2D.new()
  vec:set(player:getX() - target:getX(), player:getZ() - target:getZ())


  dist = vec:length()

  local animation = player:getAnimation();

  if(dist > 3 and animation:isRunning() == false) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Attack -> Chase", " | Reason: Out of attack range")
    player:getFSM():changeState("state_chase")
  else
    if(animation:isRunning() == false) then
      animation:setAnimation(animation_types.attack)
      animation:setFPS(80)
      player:sendMessage(0, player.id, player.target_id, 2, player.power)
    end
  end


end


state_attack["exit"] = function(player)
local animation = player:getAnimation();
animation:shouldLoop(true)


end

state_attack["onMessage"] = function(player, msg)



end


-------------------------------------------------------------------------------

-- create the search state

-------------------------------------------------------------------------------
state_search = {}


state_search["enter"] = function(player)
local animation = player:getAnimation();
animation:shouldAnimate(true)
animation:shouldLoop(true)
animation:setAnimation(animation_types.run)


end


state_search["execute"] = function(player)

  if(player.target_id == -1) then
    local pos = player:get_target_position()
    player:pathfindToPoint(player:getX(), player:getZ(), pos.x, pos.y)
    player.target_id = -2
  end

  if(player:watchForEnemy(10)) then
    print("Entity: ", player.id, " | Faction: ", player.faction, " | Search -> Chase", " | Reason: Target spoted")
    player:getFSM():changeState("state_chase")
  end

  if(player:followWaypoint(false)) then
    if(player:numberOfWaypoints() == 0) then
      print("Entity: ", player.id, " | Faction: ", player.faction, " | Search -> Patrol", " | Reason: Target not found")
      player:getFSM():changeState("state_patrol")
    end
  end

end

state_search["exit"] = function(player)



end

state_search["onMessage"] = function(player, msg)
  if (msg.msg == 1) then
    player.target_id = -1
    player:set_target_position(msg.extraInfo:getX(), msg.extraInfo:getY())

  elseif (msg.msg == 5) then
    local pos = vector2D.new()
    pos:set(msg.extraInfo.x - player:getX(), msg.extraInfo.y - player:getZ())

    local dist = pos:length()
    if(dist < 15) then
      player.target_id = -1 
      player:set_target_position(msg.extraInfo.x, msg.extraInfo.y)
    end
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