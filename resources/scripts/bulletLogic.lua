if(collision) then
	remove_obj = true;
end


if(floor_contact) then
	time_alive_left = time_alive_left - delta_time
	remove_colliders()
	freeze_projectile()

	if(damage == 1) then
		local pos = vector2D.new()
		pos:set(xPos, zPos)
		local player = entityManager.getEntity(0)
		player:sendGroupMessage(0, 2, 500, 0, 5, pos)
	end

	damage = 10
end



if(time_alive_left < 0) then
	remove_obj = true;
end