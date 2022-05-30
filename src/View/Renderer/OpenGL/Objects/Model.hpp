#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Texture.hpp"

/**
 * @class Model
 * @brief A model class representing a Mesh with a texture.
 * Models are loaded in using the 3D object library Assimp.
 */
class Model {
public:
	/**
	 * @brief Construct a new Model object
	 */
	Model();

	/**
	 * @brief Loads a new model from a 3D object file format.
	 *
	 * @param fileName The name of the file to load.
	 */
	bool LoadModel(const std::string& fileName);

	/**
	 * @brief Renders the model.
	 */
	void RenderModel() const;

	/**
	 * @brief Renders the model.
	 */
	void RenderModelTwo() const;

	/**
	 * @brief Clears the model.
	 */
	void ClearModel();

	/**
	 * @brief Destroy the Model object
	 */
	~Model();

private:
	/**
	 * @brief Recursive function to traverse the node and load the meshes.
	 *
	 * @param node The node to load.
	 * @param scene The scene to load from.
	 */
	void LoadNode(aiNode* node, const aiScene* scene);

	/**
	 * @brief Loads in a mesh.
	 *
	 * @param mesh The mesh to load.
	 * @param scene The scene to load from.
	 */
	void LoadMesh(aiMesh* mesh, const aiScene* scene);

	/**
	 * @brief Loads in the material/texture.
	 *
	 * @param scene The scene to load from.
	 */
	void LoadMaterials(const aiScene* scene);

	/// A vector of the meshes.
	std::vector<Mesh*> m_meshVec;

	/// A vector of the textures.
	std::vector<Texture*> m_textureVec;

	/// A vector of the mesh to texture mapping.
	std::vector<GLuint> m_meshToTex;
};
