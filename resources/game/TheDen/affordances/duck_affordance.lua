function talk(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local affordance_transform = affordance:get_transform_component()

	agent_transform.rotation.y = Math.angle(agent_transform.position, affordance_transform.position)

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	if (AI.is_in_range(agent_transform.position, affordance_transform.position, 2.0)) then
		context.social.value = context.social.value + 0.0025
		context.loneliness.value = context.loneliness.value + 0.005

		if (affordance_agent.is_first_run) then
			DebugLogger.log(agent:get_name(), "Hey duck! I missed your company.")
			affordance_agent.is_first_run = false
		end
		return
	end
end

function talk_move(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local affordance_transform = affordance:get_transform_component()

	local agent_pos = agent_transform.position
	local affordance_pos = affordance_transform.position

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	local theater_pos = Math.vec3.new(59.63, agent_pos.y, -4.709)

	if (is_at_destination(agent_pos.x, agent_pos.z, theater_pos.x, theater_pos.z)) then
		if (affordance_agent.is_first_run) then
			local sound_pos = Audio.vec3df.new(agent_pos.x, agent_pos.y, agent_pos.z)
			Audio.play_3d_sound("quack", sound_pos, false, 1.0)
			affordance_agent.is_first_run = false
		end

		agent_transform.rotation.y = Math.angle(Math.vec3.new(1, 0, 0), Math.sub(affordance_pos, agent_pos))
		context.social.value = context.social.value + 0.005
		context.stress.value = context.stress.value + 0.001

		return
	end

	affordance_agent.accumulator = 0.0

	local path = find_path(agent_pos.x, agent_pos.z, theater_pos.x, theater_pos.z)
	if (path:size() == 0) then
		return
	end

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.y, path_y)

	agent_transform.position = AI.move_towards(agent_pos, path_pos, 2)
	agent_transform.rotation.y = Math.angle(Math.vec3.new(1, 0, 0), Math.sub(path_pos, agent_pos))
end

function annoy(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local agent_pos = agent_transform.position

	local affordance_transform = affordance:get_transform_component()
	local affordance_pos = affordance_transform.position

	if (is_at_destination(agent_pos.x, agent_pos.z, affordance_pos.x, affordance_pos.z)) then
		local affordance_agent = agent:get_affordance_agent_component()

		local agent_context = affordance_agent.utility.context
		local affordance_context = affordance:get_affordance_agent_component().utility.context

		affordance_agent.accumulator = 5.0

		agent_context.cheeky.value = 1.0
		affordance_context.stress.value = affordance_context.stress.value - 0.5

		local sound_pos = Audio.vec3df.new(agent_pos.x, agent_pos.y, agent_pos.z)
		Audio.play_3d_sound("annoy", sound_pos, false, 1.0)
		DebugLogger.log(agent:get_name(), "Hahaha!")
		DebugLogger.log(affordance:get_name(), "Hey! Stop that!")

		agent_transform.rotation.y = Math.angle(Math.vec3.new(1, 0, 0), Math.sub(affordance_pos, agent_pos))

		return
	end

	local path = find_path(agent_pos.x, agent_pos.z, affordance_pos.x, affordance_pos.z)
	if (path:size() == 0) then
		return
	end

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.y, path_y)

	agent_transform.position = AI.move_towards(agent_pos, path_pos, 2)
	agent_transform.rotation.y = Math.angle(Math.vec3.new(1, 0, 0), Math.sub(path_pos, agent_pos))
end

AffordanceSystem.set_affordance("duck", AffordanceComposite.new("Duck", {}, {
	AffordanceComposite.new("Talk", { "Talk" }, {
		AffordanceLeaf.new("Non-moving talk", {}, talk),
		AffordanceLeaf.new("Moving talk", { "Move" }, talk_move)
	}),
	AffordanceLeaf.new("Annoy", { "Annoy" }, annoy)
}))
