#include "Model.hpp"

Model::Model() {}

bool Model::LoadModel(const std::string& fileName) {
	Assimp::Importer importer;

	const aiScene* scene =
	    importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs |
	                                    aiProcess_GenSmoothNormals |
	                                    aiProcess_JoinIdenticalVertices);
	if (!scene) {
		std::cout << "Model (" << fileName
		          << ") failed to load: " << importer.GetErrorString();
		return false;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return true;
}

void Model::RenderModel() const {
	for (size_t i = 0; i < m_meshVec.size(); ++i) {
		GLuint materialIndex = m_meshToTex[i];

		if (materialIndex < m_textureVec.size() &&
		    m_textureVec[materialIndex]) {
			m_textureVec[materialIndex]->UseTexture();
		}

		m_meshVec[i]->RenderMesh();
	}
}

void Model::LoadNode(aiNode* node, const aiScene* scene) {
	for (size_t i = 0; i < node->mNumMeshes; ++i)
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);

	for (size_t i = 0; i < node->mNumChildren; ++i)
		LoadNode(node->mChildren[i], scene);
}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	for (size_t i = 0; i < mesh->mNumVertices; ++i) {
		// Vertices
		vertices.insert(
		    vertices.end(),
		    {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});

		// Texture coordinates
		if (mesh->mTextureCoords[0]) {
			vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x,
			                                 mesh->mTextureCoords[0][i].y});
		} else {
			vertices.insert(vertices.end(), {0.0f, 0.0f});
		}

		// Normals
		vertices.insert(
		    vertices.end(),
		    {-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
	}

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(),
	                    indices.size());

	m_meshVec.push_back(newMesh);
	m_meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene* scene) {
	m_textureVec.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; ++i) {
		aiMaterial* material = scene->mMaterials[i];

		m_textureVec[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path;

			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) ==
			    AI_SUCCESS) {
				int idx = std::string(path.data).rfind("\\");
				std::string fileName = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + fileName;
				m_textureVec[i] = new Texture(texPath.c_str());

				if (!m_textureVec[i]->LoadTexture()) {
					std::cout << "Failed to load texture at " << texPath;
					delete m_textureVec[i];
					m_textureVec[i] = nullptr;
				}
			}
		}

		if (!m_textureVec[i]) {
			m_textureVec[i] = new Texture("Textures/plain.png");
			m_textureVec[i]->LoadTextureA();
		}
	}
}

void Model::ClearModel() {
	for (auto& mesh : m_meshVec) {
		if (mesh) {
			delete mesh;
			mesh = nullptr;
		}
	}

	for (auto& texture : m_textureVec) {
		if (texture) {
			delete texture;
			texture = nullptr;
		}
	}
}

Model::~Model() { ClearModel(); }