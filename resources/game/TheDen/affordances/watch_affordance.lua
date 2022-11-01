function watch_screen(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local screen_transform = affordance:get_transform_component()

	local angle = Math.angle(agent_transform.position, screen_transform.position)

	agent_transform.rotation.y = angle

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.fun.value = context.fun.value + 0.005
end

function duck_watch_screen(agent, affordance)
	local theater_pos = Math.vec3.new(58.63, 0, -5.709)

	local agent_transform = agent:get_transform_component()
	local agent_pos = agent_transform.position

	local astar = Scene.get_astar()
	local path = astar:find_path(agent_pos.x, agent_pos.z, theater_position.x, theater_position.z)

	if path:size() == 0 then
		watch_screen(agent, affordance)
		context.stress.value = context.stress.value - 0.005
		return
	end

	local path_x, path_y = path:at(1)
	local path_pos = Math.vec3.new(path_x, agent_pos.z, path_y)

	agent_transform.position = AI.move_towards(agent_pos, path_pos, 1)
end

AffordanceSystem.set_affordance("screen", AffordanceComposite.new("Watch", { "Watch" }, {
	AffordanceLeaf.new("Default watch", {}, watch_screen),
	AffordanceLeaf.new("Duck watch", { "Duck" }, duck_watch_screen)
}))
