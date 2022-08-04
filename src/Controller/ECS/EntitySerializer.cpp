#include "EntitySerializer.hpp"

#include "Controller/GUI/DebugLogger.hpp"

std::ofstream EntitySerializer::save_stream_;
std::ofstream EntitySerializer::creation_stream_;
size_t EntitySerializer::indent_level_ = 0;

void EntitySerializer::serialize(const std::filesystem::path& dir_path,
                                 Reflex::Entity& entity) {
	std::filesystem::create_directory(dir_path);

	const auto entity_id =
	    std::to_string(static_cast<uint32_t>((entity.get_entity_id())));

	const std::filesystem::path save_file =
	    dir_path / "save" / (entity.get_name() + '_' + entity_id + ".lua");

	const auto mode = std::filesystem::is_empty(dir_path) ? std::ios_base::out
	                                                      : std::ios_base::app;

	creation_stream_.open(dir_path / "_MasterCreation.lua", mode);
	creation_stream_ << "Scene.add_game_object(" << save_file << ")\n";
	creation_stream_.close();

	std::filesystem::create_directory(dir_path / "save");

	save_stream_.open(save_file);
	serialize_entity(entity);
	save_stream_.close();
}

void EntitySerializer::serialize_entity(Reflex::Entity& entity) {
	create_table("entity");
	create_var("name", ('"' + entity.get_name() + '"'), true);

	serialize_transform(entity.get_component<Component::Transform>());

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

void EntitySerializer::create_table(const std::string& table_name) {
	save_stream_ << std::string(indent_level_++, '\t') << table_name
	             << " = {\n";
}

void EntitySerializer::close_table(bool comma) {
	save_stream_ << std::string(--indent_level_, '\t')
	             << (comma ? "},\n" : "}\n");
}