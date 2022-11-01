function eat(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local agent_pos = agent_transform.position

	local affordance_transform = affordance:get_transform_component()
	local affordance_pos = affordance_transform.position

	if (AI.is_in_range(agent_pos, affordance_pos, 1.0)) then
		local context = agent:get_affordance_agent_component().utility.context

		context.stress.value = context.stress.value - 0.001
		context.hunger.value = context.hunger.value - 0.005

		agent_transform.rotation.y = Math.angle(agent_pos, affordance_pos)
		return
	end

	local path = find_path(agent_pos.x, agent_pos.z, affordance_pos.x, affordance_pos.z)

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.y, path_y)

	agent_transform.position = AI.move_towards(agent_pos, path_pos, 1)
	agent_transform.rotation.y = Math.angle(agent_pos, path_pos)
end

AffordanceSystem.set_affordance("eat", AffordanceLeaf("Eat", { "Eat" }, eat))
