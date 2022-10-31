function robot_ai(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local mood_state = affordance_agent.mood_state

	DebugLogger.log("robot - emotion",
		mood_state.arousal ..
		", " ..
		mood_state.valence)
end

function watch_state(entity)
	return 1.0
end
