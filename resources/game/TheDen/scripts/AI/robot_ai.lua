function robot_update(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.social.value = context.social.value - 0.001
	context.cheeky.value = context.cheeky.value + 0.001
	context.fun.value = context.fun.value - 0.001
end

function watch_state(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context
	local mood_state = affordance_agent.mood_state

	return (1 - context.fun.value) * (1 - mood_state.valence)
end
