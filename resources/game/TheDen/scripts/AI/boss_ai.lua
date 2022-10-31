function print_mood_state(mood_state)
	DebugLogger.log("boss - emotion",
		mood_state.arousal ..
		", " ..
		mood_state.valence)
end

function boss_update(entity)
	local affordance_agent = entity:get_affordance_agent_component()

	local context = affordance_agent.utility.context
	local mood_state = affordance_agent.mood_state

	mood_state.arousal = mood_state.arousal + (context.loneliness.value * context.loneliness.arousal_weight)

	print_mood_state(mood_state)
end

function watch_state(entity)
	return 1.0
end
