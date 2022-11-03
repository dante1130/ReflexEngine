function study(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local agent_pos = agent_transform.position

	local affordance_transform = affordance:get_transform_component()
	local affordance_pos = affordance_transform.position

	local affordance_agent = agent:get_affordance_agent_component()

	if (is_at_destination(agent_pos.x, agent_pos.z, affordance_pos.x, affordance_pos.z)) then
		local context = affordance_agent.utility.context

		context.social.value = context.social.value - 0.001
		context.stress.value = context.stress.value - 0.005
		context.hunger.value = context.hunger.value - 0.005
		context.fun.value = context.fun.value - 0.005

		agent_transform.rotation.y = Math.angle(Math.vec3.new(1, 0, 0), Math.sub(affordance_pos, agent_pos))

		if (affordance_agent.is_first_run) then
			DebugLogger.log(agent:get_name(), "Studying...")
			affordance_agent.is_first_run = false
		end

		return
	end

	affordance_agent.accumulator = 0.0

	local path = find_path(agent_pos.x, agent_pos.z, affordance_pos.x, affordance_pos.z)
	if (path:size() == 0) then
		return
	end

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.y, path_y)

	agent_transform.position = AI.move_towards(agent_pos, path_pos, 2)
	agent_transform.rotation.y = Math.angle(Math.vec3.new(1, 0, 0), Math.sub(path_pos, agent_pos))
end

AffordanceSystem.set_affordance("study", AffordanceLeaf.new("Study", { "Study" }, study))
