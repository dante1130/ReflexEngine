function watch_screen(agent, affordance)
	local agent_transform = agent:get_transform_component()
	local screen_transform = affordance:get_transform_component()

	local angle = Math.angle(agent_transform.position, screen_transform.position)

	agent_transform.rotation.y = angle

	local affordance_agent = agent:get_affordance_agent_component()
	local context = affordance_agent.utility.context

	context.fun.value = context.fun.value + 0.001
end

function duck_watch_screen(agent, affordance)
	watch_screen(agent, affordance)

	local duck_agent = agent:get_affordance_agent_component()
	local context = duck_agent.utility.context

	context.stress.value = context.stress.value - 0.001
end

AffordanceSystem.set_affordance("screen", AffordanceComposite.new("Watch", { "Watch" }, {
	AffordanceLeaf.new("Default watch", {}, watch_screen),
	AffordanceLeaf.new("Duck watch", { "Duck" }, duck_watch_screen)
}))
