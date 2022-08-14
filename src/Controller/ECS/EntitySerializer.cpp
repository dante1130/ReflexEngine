#include "EntitySerializer.hpp"

#include "Controller/GUI/DebugLogger.hpp"

std::ofstream EntitySerializer::save_stream_;
std::ofstream EntitySerializer::creation_stream_;
size_t EntitySerializer::indent_level_ = 0;

void EntitySerializer::serialize(const std::filesystem::path& dir_path,
                                 ECS& ecs) {
	auto& registry = ecs.get_registry();

	bool is_first = true;

	registry.each([&ecs, &dir_path, is_first](auto entity_id) mutable {
		auto& entity = ecs.get_entity(entity_id);

		if (!is_first) {
			serialize(dir_path, entity);
		} else {
			serialize(dir_path, entity, true);
			is_first = false;
		}
	});
}

void EntitySerializer::serialize(const std::filesystem::path& dir_path,
                                 Reflex::Entity& entity, bool overwrite) {
	std::filesystem::create_directory(dir_path);

	const auto entity_id =
	    std::to_string(static_cast<uint32_t>((entity.get_entity_id())));

	const std::filesystem::path save_file =
	    dir_path / "save" / (entity.get_name() + '_' + entity_id + ".lua");

	const auto mode = overwrite ? std::ios_base::trunc : std::ios_base::app;

	creation_stream_.open(dir_path / "_SaveCreation.lua", mode);
	creation_stream_ << "Scene.add_game_object(" << save_file << ")\n";
	creation_stream_.close();

	std::filesystem::create_directory(dir_path / "save");

	save_stream_.open(save_file);
	serialize_entity(entity);
	save_stream_.close();
}

void EntitySerializer::serialize_entity(Reflex::Entity& entity) {
	create_table("entity");
	create_var("name", '"' + entity.get_name() + '"', true);

	serialize_transform(entity.get_component<Component::Transform>());

	if (entity.any_component<Component::Mesh>()) {
		serialize_mesh(entity.get_component<Component::Mesh>());
	}

	if (entity.any_component<Component::Script>()) {
		serialize_script(entity.get_component<Component::Script>());
	}

	if (entity.any_component<Component::Model>()) {
		serialize_model(entity.get_component<Component::Model>());
	}

	if (entity.any_component<Component::Md2Animation>()) {
		serialize_md2(entity.get_component<Component::Md2Animation>());
	}

	if (entity.any_component<Component::Terrain>()) {
		serialize_terrain(entity.get_component<Component::Terrain>());
	}

	if (entity.any_component<Component::DirectionalLight>()) {
		serialize_directional_light(
		    entity.get_component<Component::DirectionalLight>());
	}

	if (entity.any_component<Component::PointLight>()) {
		serialize_point_light(entity.get_component<Component::PointLight>());
	}

	if (entity.any_component<Component::SpotLight>()) {
		serialize_spot_light(entity.get_component<Component::SpotLight>());
	}

	close_table();
}

void EntitySerializer::serialize_transform(
    const Component::Transform& transform) {
	create_table("transform");

	create_table("position");
	create_var("x", transform.position.x, true);
	create_var("y", transform.position.y, true);
	create_var("z", transform.position.z);
	close_table(true);

	create_table("rotation");
	create_var("x", transform.rotation.x, true);
	create_var("y", transform.rotation.y, true);
	create_var("z", transform.rotation.z);
	close_table(true);

	create_table("scale");
	create_var("x", transform.scale.x, true);
	create_var("y", transform.scale.y, true);
	create_var("z", transform.scale.z);
	close_table(true);

	close_table(true);
}

void EntitySerializer::serialize_script(const Component::Script& script) {
	create_table("script");
	create_var("lua_script", '"' + script.lua_script + '"');
	close_table(true);
}

void EntitySerializer::serialize_mesh(const Component::Mesh& mesh) {
	create_table("mesh");
	create_var("mesh_name", '"' + mesh.mesh_name + '"', true);
	create_var("texture_name", '"' + mesh.texture_name + '"', true);
	create_var("material_name", '"' + mesh.material_name + '"');
	close_table(true);
}

void EntitySerializer::serialize_model(const Component::Model& model) {
	create_table("model");
	create_var("model_name", '"' + model.model_name + '"', true);
	create_var("material_name", '"' + model.material_name + '"');
	close_table(true);
}

void EntitySerializer::serialize_md2(const Component::Md2Animation& md2) {
	create_table("md2_animation");
	create_var("md2_name", '"' + md2.md2_name + '"', true);
	create_var("texture_name", '"' + md2.texture_name + '"', true);
	create_var("material_name", '"' + md2.material_name + '"');
	close_table(true);
}

void EntitySerializer::serialize_terrain(const Component::Terrain& terrain) {
	create_table("terrain");
	create_var("terrain_name", '"' + terrain.terrain_name + '"', true);
	create_var("texture_name", '"' + terrain.texture_name + '"', true);
	create_var("material_name", '"' + terrain.material_name + '"', true);
	create_var("detailmap_name", '"' + terrain.detailmap_name + '"');
	close_table(true);
}

void EntitySerializer::serialize_directional_light(
    const Component::DirectionalLight& light) {
	create_table("directional_light");

	create_var("shadow_width", light.shadow_width, true);
	create_var("shadow_height", light.shadow_height, true);

	create_table("color");
	create_var("r", light.color.r, true);
	create_var("g", light.color.g, true);
	create_var("b", light.color.b);
	close_table(true);

	create_var("ambient_intensity", light.ambient_intensity, true);
	create_var("diffuse_intensity", light.diffuse_intensity, true);

	create_table("direction");
	create_var("x", light.direction.x, true);
	create_var("y", light.direction.y, true);
	create_var("z", light.direction.z);
	close_table();

	close_table(true);
}

void EntitySerializer::serialize_point_light(
    const Component::PointLight& light) {
	create_table("point_light");

	create_var("shadow_width", light.shadow_width, true);
	create_var("shadow_height", light.shadow_height, true);
	create_var("near_plane", light.near_plane, true);
	create_var("far_plane", light.far_plane, true);

	create_table("color");
	create_var("r", light.color.r, true);
	create_var("g", light.color.g, true);
	create_var("b", light.color.b);
	close_table(true);

	create_var("ambient_intensity", light.ambient_intensity, true);
	create_var("diffuse_intensity", light.diffuse_intensity, true);

	create_table("position");
	create_var("x", light.position.x, true);
	create_var("y", light.position.y, true);
	create_var("z", light.position.z);
	close_table(true);

	create_var("constant", light.constant, true);
	create_var("linear", light.linear, true);
	create_var("quadratic", light.quadratic);

	close_table(true);
}

void EntitySerializer::serialize_spot_light(const Component::SpotLight& light) {
	create_table("spot_light");

	create_var("shadow_width", light.shadow_width, true);
	create_var("shadow_height", light.shadow_height, true);
	create_var("near_plane", light.near_plane, true);
	create_var("far_plane", light.far_plane, true);

	create_table("color");
	create_var("r", light.color.r, true);
	create_var("g", light.color.g, true);
	create_var("b", light.color.b);
	close_table(true);

	create_var("ambient_intensity", light.ambient_intensity, true);
	create_var("diffuse_intensity", light.diffuse_intensity, true);

	create_table("position");
	create_var("x", light.position.x, true);
	create_var("y", light.position.y, true);
	create_var("z", light.position.z);
	close_table(true);

	create_table("direction");
	create_var("x", light.direction.x, true);
	create_var("y", light.direction.y, true);
	create_var("z", light.direction.z);
	close_table(true);

	create_var("constant", light.constant, true);
	create_var("linear", light.linear, true);
	create_var("quadratic", light.quadratic, true);
	create_var("edge", light.edge);

	close_table(true);
}

void EntitySerializer::create_table(const std::string& table_name) {
	save_stream_ << std::string(indent_level_++, '\t') << table_name
	             << " = {\n";
}

void EntitySerializer::close_table(bool comma) {
	save_stream_ << std::string(--indent_level_, '\t')
	             << (comma ? "},\n" : "}\n");
}