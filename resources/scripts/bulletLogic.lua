if(collision) then
	remove_obj = true;
end


if(floor_contact) then
	time_alive_left = time_alive_left - delta_time
	remove_colliders()
	freeze_projectile()
end

if(time_alive_left < 0) then
	remove_obj = true;
end