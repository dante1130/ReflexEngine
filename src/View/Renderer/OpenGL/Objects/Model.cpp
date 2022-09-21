#include "Model.hpp"

bool Model::LoadModel(const std::string& fileName) {
	Assimp::Importer importer;

	const aiScene* scene =
	    importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs |
	                                    aiProcess_GenSmoothNormals |
	                                    aiProcess_JoinIdenticalVertices);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
	    !scene->mRootNode) {
		std::cout << "Model (" << fileName
		          << ") failed to load: " << importer.GetErrorString();
		return false;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return true;
}

void Model::RenderModel() const {
	if (m_meshVec.size() == 0) return;

	for (size_t i = 0; i < m_meshVec.size(); ++i) {
		GLuint materialIndex = m_meshToTex.at(i);

		if (materialIndex < m_textureVec.size() &&
		    m_textureVec.at(materialIndex)) {
			m_textureVec.at(materialIndex)->use_texture();
		}

		m_meshVec.at(i)->render_mesh();
	}
}

void Model::RenderModelTwo() const {
	if (m_meshVec.size() == 0) return;

	for (size_t i = 0; i < m_meshVec.size(); ++i) {
		m_meshVec.at(i)->render_mesh();
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
			vertices.insert(vertices.end(), {1.0f, 0.0f});
		}

		// Normals
		vertices.insert(
		    vertices.end(),
		    {-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
	}

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; ++j) {
			indices.emplace_back(face.mIndices[j]);
		}
	}
	//std::cout << "Load Mesh Runs!" << std::endl;
	Mesh* newMesh = new Mesh();
	newMesh->create_mesh(vertices.data(), indices.data(), vertices.size(),
	                     indices.size());

	m_meshVec.emplace_back(newMesh);
	m_meshToTex.emplace_back(mesh->mMaterialIndex);
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
				int idx = std::string(path.data).rfind('\\');
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
			m_textureVec.at(i)->LoadTextureA();
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
