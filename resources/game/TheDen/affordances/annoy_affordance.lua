function annoy(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local agent_pos = agent_transform.position

	local affordance_transform = affordance:get_transform_component()
	local affordance_pos = affordance_transform.position

	if (AI.is_in_range(agent_pos, affordance_pos, 1.0)) then
		local agent_context = agent:get_affordance_agent_component().utility.context
		local affordance_context = affordance:get_affordance_agent_component().utility.context

		local sound_pos = Audio.vec3df.new(agent_pos.x, agent_pos.y, agent_pos.z)
		Audio.play_3d_sound("annoy", sound_pos, false, 1.0)

		agent_transform.rotation.y = Math.angle(agent_pos, affordance_pos)
		return
	end

	local path = find_path(agent_pos.x, agent_pos.z, affordance_pos.x, affordance_pos.z)

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.y, path_y)

	agent_transform.position = AI.move_towards(agent_pos, path_pos, 1)
	agent_transform.rotation.y = Math.angle(agent_pos, path_pos)
end

AffordanceSystem.set_affordance("annoy", AffordanceLeaf("Annoy", { "Annoy" }, annoy))
