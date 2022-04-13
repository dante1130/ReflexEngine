#include "BruteForceTerrain.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void BruteForceTerrain::render(const Shader* shader) {
	if (!mesh_) return;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, get_origin());
	model = glm::scale(model, scale_);

	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader->GetUsingTexture(), !mesh_->has_color());

	mesh_->RenderMesh();
}

bool BruteForceTerrain::load_mesh() {
	if (!heightmap_) {
		std::cout << "Heightmap not loaded!" << std::endl;
		return false;
	}

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	for (size_t z = 0; z < get_length(); ++z) {
		for (size_t x = 0; x < get_width(); ++x) {
			const size_t index = z * get_width() + x;

			// Vertices
			vertices.push_back(x);
			vertices.push_back(get_height(x, z));
			vertices.push_back(z);

			// Texture coordinates
			vertices.push_back(x / static_cast<GLfloat>(get_width()));
			vertices.push_back(z / static_cast<GLfloat>(get_length()));

			// Normals
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);

			// Colours
			GLfloat color = get_height_color(x, z) / 255.0f;

			vertices.push_back(color);
			vertices.push_back(color);
			vertices.push_back(color);

			if (x < get_width() - 1 && z < get_length() - 1) {
				// Indices
				indices.push_back(index);
				indices.push_back(index + get_width());
				indices.push_back(index + get_width() + 1);

				indices.push_back(index);
				indices.push_back(index + get_width() + 1);
				indices.push_back(index + 1);
			}
		}
	}

	mesh_ = std::make_shared<Mesh>();
	mesh_->CreateColorMesh(vertices.data(), indices.data(), vertices.size(),
	                       indices.size());

	return true;
}