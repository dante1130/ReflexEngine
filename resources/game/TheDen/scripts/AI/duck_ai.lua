function duck_update(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.hunger.value = context.hunger.value - 0.001
	context.stress.value = context.stress.value - 0.001
	context.fun.value = context.fun.value - 0.001
	context.social.value = context.social.value - 0.001
end

function watch_state(entity)
	local affordance_agent = entity:get_affordance_agent_component()

	local context = affordance_agent.utility.context
	local mood_state = affordance_agent.mood_state

	local score = 0.0

	if (context.stress.value < -0.5) then
		score = score + 1.0
	end
	if (context.fun.value < -0.5) then
		score = score + 2.0
	end
	if (mood_state.arousal < -0.5) then
		score = score + 0.5
	end
	if (mood_state.valence < -0.5) then
		score = score + 0.5
	end

	return score
end

function talk_state(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context
	local mood_state = affordance_agent.mood_state

	local score = 0.0

	if (context.social.value < -0.5) then
		score = score + 2.0
	end
	if (mood_state.arousal < -0.5) then
		score = score + 0.5
	end
	if (mood_state.valence < -0.5) then
		score = score + 0.5
	end

	return score
end

function eat_state(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	local score = 0.0

	if (context.hunger.value < -0.5) then
		score = score + 3.0
	end

	return score
end

function study_state(entity)
	local affordance_agent = entity:get_affordance_agent_component()
	local context = affordance_agent.utility.context
	local mood_state = affordance_agent.mood_state

	local score = 0.0

	if (context.stress.value > 0.0) then
		score = score + 2.0
	end
	if (context.fun.value > 0.0) then
		score = score + 1.0
	end
	if (context.social.value > 0.5) then
		score = score + 0.25
	end
	if (mood_state.arousal > 0.5) then
		score = score + 0.25
	end
	if (mood_state.valence > 0.5) then
		score = score + 0.25
	end

	return score
end
