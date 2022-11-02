function talk(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local affordance_transform = affordance:get_transform_component()

	agent_transform.rotation.y = Math.angle(agent_transform.position, affordance_transform.position)

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	if (AI.is_in_range(agent_transform.position, affordance_transform.position, 3.0)) then
		context.social.value = context.social.value + 0.0025
		context.loneliness.value = context.loneliness.value + 0.005
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
		if (affordance_agent.accumulator == 0.0) then
			local sound_pos = Audio.vec3df.new(agent_pos.x, agent_pos.y, agent_pos.z)
			Audio.play_3d_sound("quack", sound_pos, false, 1.0)
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

AffordanceSystem.set_affordance("talk", AffordanceComposite.new("Talk", { "Talk" }, {
	AffordanceLeaf.new("Non-moving talk", {}, talk),
	AffordanceLeaf.new("Moving talk", { "Move" }, talk_move)
}))
