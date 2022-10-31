function talk(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local screen_transform = affordance:get_transform_component()

	local angle = Math.angle(agent_transform.position, screen_transform.position)

	agent_transform.rotation.y = angle

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.social.value = context.social.value + 0.005
end

function talk_move(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local affordance_transform = affordance:get_transform_component()

	local agent_pos = agent_transform.position
	local affordance_pos = affordance_transform.position

	agent_transform.rotation.y = Math.angle(agent_pos, affordance_pos)

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	local astar = Scene.get_astar()
	local path = astar:find_path(agent_pos.x, agent_pos.z, affordance_pos.x, affordance_pos.z)

	if path:size() == 0 or Math.distance(agent_pos, affordance_pos) then
		context.social.value = context.social.value + 0.005
		return
	end

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.z, path_y)

	AI.move_towards(agent, path_pos, 1)
end

AffordanceSystem.set_affordance("talk", AffordanceComposite.new("Talk", { "Talk" }, {
	AffordanceLeaf.new("Non-moving talk", {}, talk),
	AffordanceLeaf.new("Moving talk", { "Move" }, talk_move)
}))
