#include "EntitySerializer.hpp"

#include "Controller/GUI/DebugLogger.hpp"

std::ofstream EntitySerializer::save_stream;
std::ofstream EntitySerializer::creation_stream;
size_t EntitySerializer::indent_level = 0;

void EntitySerializer::serialize(const std::filesystem::path& dir_path,
                                 Reflex::Entity& entity) {
	if (!std::filesystem::is_directory(dir_path)) {
		DebugLogger::log("warning",
		                 "EntitySerializer::serialize: " + dir_path.string() +
		                     " is not a directory");
		return;
	}

	std::filesystem::create_directory(dir_path);

	const auto entity_id =
	    std::to_string(static_cast<uint32_t>((entity.get_entity_id())));

	const std::filesystem::path save_file =
	    dir_path / "save/" / entity_id / ".lua";

	creation_stream.open(dir_path / "_MasterCreation.lua", std::ios_base::app);
	creation_stream << "Scene.add_game_object(" << save_file << ")\n";
	creation_stream.close();

	save_stream.open(save_file);
	serialize_entity(entity);
	save_stream.close();
}

void EntitySerializer::serialize_entity(Reflex::Entity& entity) {
	create_table("entity");
	create_var("name", entity.get_name());

	if (entity.any_component<Component::Transform>()) {
		serialize_transform(entity.get_component<Component::Transform>());
	}

	close_table();
}

void EntitySerializer::serialize_transform(
    const Component::Transform& transform) {
	create_table("transform");

	create_table("position");
	create_var<float>("x", transform.position.x, true);
	create_var<float>("y", transform.position.y, true);
	create_var<float>("z", transform.position.z);
	close_table(true);

	create_table("rotation");
	create_var<float>("x", transform.rotation.x, true);
	create_var<float>("y", transform.rotation.y, true);
	create_var<float>("z", transform.rotation.z);
	close_table(true);

	create_table("scale");
	create_var<float>("x", transform.scale.x, true);
	create_var<float>("y", transform.scale.y, true);
	create_var<float>("z", transform.scale.z);
	close_table(true);

	close_table(true);
}

void EntitySerializer::create_table(const std::string& table_name) {
	save_stream << std::string(indent_level++, '\t') << table_name << " = {\n";
}

void EntitySerializer::close_table(bool comma) {
	save_stream << std::string(--indent_level, '\t')
	            << (comma ? "},\n" : "}\n");
}
