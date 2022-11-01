function watch_screen(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local screen_transform = affordance:get_transform_component()

	agent_transform.rotation.y = Math.angle(agent_transform.position, screen_transform.position)

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.fun.value = context.fun.value + 0.005
end

function duck_watch_screen(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local agent_pos = agent_transform.position

	local theater_pos = Math.vec3.new(59.63, agent_pos.y, -5.709)

	if (Math.distance(agent_pos, theater_pos) < 1.0) then
		watch_screen(agent, affordance)
		context.stress.value = context.stress.value - 0.005
		return
	end

	local path = find_path(agent_pos.x, agent_pos.z, theater_pos.x, theater_pos.z)

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.y, path_y)

	agent_transform.position = AI.move_towards(agent_pos, path_pos, 1)
	agent_transform.rotation.y = Math.angle(agent_pos, path_pos)
end

AffordanceSystem.set_affordance("screen", AffordanceComposite.new("Watch", { "Watch" }, {
	AffordanceLeaf.new("Default watch", {}, watch_screen),
	AffordanceLeaf.new("Duck watch", { "Duck" }, duck_watch_screen)
}))
