function boss_update(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.social.value = context.social.value - 0.001
	context.loneliness.value = context.loneliness.value - 0.001
	context.fun.value = context.fun.value - 0.001

	local mood_state = affordance_agent.mood_state

	DebugLogger.log_color("boss - emotion",
		mood_state.arousal ..
		", " ..
		mood_state.valence, GUI.vec4.new(1.0, 0.0, 0.0, 1.0))
end

function watch_state(entity)
	return 1.0
end
