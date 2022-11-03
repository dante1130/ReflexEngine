var = {
}

function init(ecs, entity)
	if(not entity:any_rigidbody_component()) then
		entity:add_rigidbody_component()
	end
	local rb = entity:get_rigidbody_component()
	rb.type = 0
	LoadOBJCollider(rb, "models/TheDenCollisions.obj")

	local script = entity:get_script_component()
	script.is_active = false;
end

function update(ecs, entity)

end
