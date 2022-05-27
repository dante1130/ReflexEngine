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

  print("leaving global state")

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
  --print("In idle")
  
  local pos = vector2D.new()
  pos:set(camera_pos_x(), camera_pos_z())
  player:set_target_position(pos.x, pos.y)

  local playerX = player:getX()
  local playerZ = player:getZ()

  local distance = vector2Length(pos.x - playerX, pos.y - playerZ)
  if (player.dead) then
    print("dead")
  elseif (distance < 5) then
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
  print("Leaving idle state")


end

state_idle["onMessage"] = function(player, msg)
  if (msg.msg == 2) then
    print(msg.extraInfo)
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
    local targetPos = vector2D.new()
    targetPos:set(100, 100)
    player:sendGroupMessage(0, player.faction, 25, player.id, 1, targetPos)
    player:getFSM():changeState("state_chase")

    print("Enemy spotted")

  end

--[[]
  player:waypointFollow()
  if (player:watchForEnemy()) then
    a = vector2D()
    a:set(400, 400)
    player:sendMessage(0, player:getPlayerID(), 1, 1, a)
    player:getFSM():changeState("state_chase")


  end
]]--
end


state_patrol["exit"] = function(player)

  print("exit patrol state")

end

state_patrol["onMessage"] = function(player, msg)
  if (msg.msg == 1) then
    print("msg recd")
    print(msg.extraInfo.x)
    print(msg.extraInfo.y)
    --player:setEnemyTarget(msg.extraInfo:getX(), msg.extraInfo:getY())
    --player:getFSM():changeState("state_chase")
    --  player:moveToEnemy()
  end

end

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
state_chase = {}


state_chase["enter"] = function(player)


end


state_chase["execute"] = function(player)
  print("In chase")

  if(player:moveToEnemy(1)) then
      print("changing to attack")
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
  print("In attack")

  local vec = vector2D.new()
  vec:set(player:getX(), player:getZ())

  dist = 2--vec:length()

  if(dist > 2) then
    player:getFSM():changeState("state_chase")
  else
    print("Attacking")
    player:sendMessage(0, player.id, player.target_id, 2, player.power)
  end


end


state_attack["exit"] = function(player)



end

state_attack["onMessage"] = function(player, msg)



end