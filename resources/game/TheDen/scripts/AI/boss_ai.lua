function boss_update(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.social.value = context.social.value - 0.001
	context.loneliness.value = context.loneliness.value - 0.001
	context.fun.value = context.fun.value - 0.001
end

function watch_state(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	local score = 1.0

	if (context.fun.value < -0.5) then
		score = score + 1.0
	end

	return score
end

function talk_state(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	local score = 0.0

	if (context.loneliness.value < 0.0) then
		score = score + 2.0
	end
	if (context.social.value < 0.0) then
		score = score + 1.0
	end

	return score
end
