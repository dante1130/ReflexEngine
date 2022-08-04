#pragma once

#include <fstream>
#include <filesystem>

#include "Controller/ECS/Entity.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Md2Animation.hpp"

/**
 * @class EntitySerializer
 * @brief Serializer for ECS entities to Lua files in a directory.
 */
class EntitySerializer {
public:
	/**
	 * @brief Serialize all the entities in the ECS to a directory.
	 *
	 * @param dir_path The directory path to save the entities to.
	 * @param ecs The ECS to serialize the entities from.
	 */
	static void serialize(const std::filesystem::path& dir_path, ECS& ecs);

	/**
	 * @brief Serialize an entity to a directory.
	 *
	 * @param dir_path The directory path to save the entity to.
	 * @param entity The entity to serialize.
	 * @param overwrite Whether to overwrite the file or append to it.
	 */
	static void serialize(const std::filesystem::path& dir_path,
	                      Reflex::Entity& entity, bool overwrite = false);

private:
	/// The output stream for the entity save file.
	static std::ofstream save_stream_;
	/// The output stream for the creation file.
	static std::ofstream creation_stream_;
	/// The indent level of the Lua table.
	static size_t indent_level_;

	/**
	 * @brief Serialize an entity to the save output stream.
	 *
	 * @param entity The entity to serialize.
	 */
	static void serialize_entity(Reflex::Entity& entity);

	/**
	 * @brief Serialize the transform component to the save output stream.
	 *
	 * @param transform The transform component to serialize.
	 */
	static void serialize_transform(const Component::Transform& transform);

	/**
	 * @brief Serialize the mesh component to the save output stream.
	 *
	 * @param mesh The mesh component to serialize.
	 */
	static void serialize_mesh(const Component::Mesh& mesh);

	/**
	 * @brief Serialize the model component to the save output stream.
	 *
	 * @param model The model component to serialize.
	 */
	static void serialize_model(const Component::Model& model);

	/**
	 * @brief Serialize the md2 animation component to the save output stream.
	 *
	 * @param md2 The md2 animation component to serialize.
	 */
	static void serialize_md2(const Component::Md2Animation& md2);

	/**
	 * @brief Writes the beginning of a Lua table to the output stream,
	 * increments the indent level.
	 *
	 * @param table_name The name of the table.
	 */
	static void create_table(const std::string& table_name);

	/**
	 * @brief Writes the end of a Lua table to the output stream,
	 * decrements the indent level.
	 *
	 * @param comma Whether to write a comma after, false by default.
	 */
	static void close_table(bool comma = false);

	/**
	 * @brief Writes a Lua variable initialization to the output stream.
	 *
	 * @tparam T The type of the variable.
	 * @param var_name The name of the variable.
	 * @param var_value The value of the variable.
	 * @param comma Whether to write a comma after, false by default.
	 */
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