var = {
}

function init(ecs, entity)
	if(not entity:any_rigidbody_component()) then
		entity:add_rigidbody_component()
	end
	local rb = entity:get_rigidbody_component()
	rb.type = 0
	LoadOBJCollider(rb, "models/TheDenCollisions.obj")
end

function update(ecs, entity)

end
