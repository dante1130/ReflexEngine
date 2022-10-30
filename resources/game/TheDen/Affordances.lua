function watch_screen(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local screen_transform = affordance:get_transform_component()

	local angle = Math.angle(agent_transform.position, screen_transform.position)

	agent_transform.rotation.y = angle
end

AffordanceSystem.set_affordance("screen", AffordanceLeaf.new("Watch", { "Watch" }, watch_screen))
