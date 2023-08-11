if getBoolData("should_shoot", false) == true then
	if current_time() - getFloatData("last_shot", 0) > getFloatData("shot_delay", 0.25) then
		addGameObject("scripts/bullet.lua")
		setBoolData("should_shoot", false)
		setFloatData("last_shot", current_time())
	end
end
