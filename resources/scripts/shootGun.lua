if get_if_should_shoot() == true then
	addGameObject("scripts/bullet.lua")
	set_if_should_shoot(false)
	set_last_shot()
end
