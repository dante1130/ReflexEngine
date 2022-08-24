var = {}

function init(ecs, entity)
	local transform = entity:get_transform_component()

	local boat_pos = Audio.vec3df.new(transform.position.x, transform.position.y, transform.position.z)

	Audio.play_3d_sound("duckandcover", boat_pos, true, 5.0)
end

function update(ecs, entity)

end
