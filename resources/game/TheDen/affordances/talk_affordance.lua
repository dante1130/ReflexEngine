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
	talk(agent, affordance)

	local duck_agent = agent:get_affordance_agent_component()
	local context = duck_agent.utility.context

	context.stress.value = context.stress.value - 0.005
end

AffordanceSystem.set_affordance("talk", AffordanceComposite.new("Talk", { "Talk" }, {
	AffordanceLeaf.new("Non-moving talk", {}, talk),
	AffordanceLeaf.new("Moving talk", { "Move" }, talk_move)
}))
