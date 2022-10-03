var = {
}

function init(ecs, entity)
	--entity:add_rigidbody_component()
	local rb = entity:get_rigidbody_component()
	rb:add_sphere_collider(Math.vec3.new(0, 0, 0), 2, 0.5, 0.5)
end

function update(ecs, entity)

end
