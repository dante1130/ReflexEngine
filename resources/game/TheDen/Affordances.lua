function watch_screen(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local screen_transform = affordance:get_transform_component()

	local angle = Math.angle(agent_transform.position, screen_transform.position)

	agent_transform.rotation.y = angle

	local agent_affordance = agent:get_affordance_agent_component()
	local agent_mood_state = agent_affordance.mood_state

	agent_mood_state.arousal = agent_mood_state.arousal + 0.004
end

AffordanceSystem.set_affordance("screen", AffordanceLeaf.new("Watch", { "Watch" }, watch_screen))
