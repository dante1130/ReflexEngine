var = {
	loneliness = 0.5
}

function print_mood_state(mood_state)
	DebugLogger.log("boss - emotion",
		mood_state.joy_sadness ..
		", " ..
		mood_state.trust_disgust ..
		", " ..
		mood_state.fear_anger ..
		", " ..
		mood_state.surprise_anticipation)
end

function boss_update(entity)
	local affordance_agent = entity:get_affordance_agent_component()

	local context = affordance_agent.utility.context
	local mood_state = affordance_agent.mood_state

	mood_state.joy_sadness = mood_state.joy_sadness + (-context.loneliness * Time.get_delta_time()) * 0.01

	print_mood_state(mood_state)
end

function watch_state(entity)
	return 1.0
end
