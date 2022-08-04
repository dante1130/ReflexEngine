#pragma once

#include <fstream>
#include <filesystem>

#include "Controller/ECS/Entity.hpp"

#include "Model/Components/Transform.hpp"

class EntitySerializer {
public:
	static void serialize(const std::filesystem::path& dir_path,
	                      Reflex::Entity& entity);

private:
	static std::ofstream save_stream_;
	static std::ofstream creation_stream_;
	static size_t indent_level_;

	static void serialize_entity(Reflex::Entity& entity);
	static void serialize_transform(const Component::Transform& transform);

	static void create_table(const std::string& table_name);
	static void close_table(bool comma = false);

	template <typename T>
	static void create_var(const std::string& var_name, const T& var_value,
	                       bool comma = false);
};

template <typename T>
void EntitySerializer::create_var(const std::string& var_name,
                                  const T& var_value, bool comma) {
	save_stream_ << std::string(indent_level_, '\t') << var_name << " = "
	             << var_value << (comma ? ",\n" : "\n");
}