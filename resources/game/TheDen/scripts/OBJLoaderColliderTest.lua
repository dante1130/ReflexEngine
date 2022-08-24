var = {
}

function init(ecs, entity)
	entity:add_rigidbody_component()
	local rb = entity:get_rigidbody_component()
	rb.type = 0
	LoadOBJCollider(rb, "models/untitled.obj")
end

function update(ecs, entity)

end
