function robot_ai(entity)
	local affordance_agent = entity:get_affordance_agent_component()

	local context = affordance_agent.utility.context
	local mood_state = affordance_agent.mood_state

	mood_state.arousal = mood_state.arousal + 0.001

	print_mood_state(mood_state)
end

function watch_state(entity)
	return 1.0
end
