#include "BttController.hpp"

#include <iostream>

BttController::BttController() {
	prev_pos = glm::vec3(0, 0, 0);
	current_total_indices = 0;
	chunk_size = 0;
	chunk_detail = 0;
	firstRun = true;
}

BttController::~BttController() {
	for (int i = 0; i < bttMap.size(); ++i) {
		bttMap.at(i).clear();
	}
	bttMap.clear();
	bttCenters.clear();
	vertices.clear();
	distances.clear();
	current_total_indices = 0;
	chunk_size = 0;
	chunk_detail = 0;
}

void BttController::render(const Shader& shader) {
	if (!mesh_) return;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, get_origin());
	model = glm::scale(model, scale_);

	glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader.GetUsingTexture(), false);
	glUniform1i(shader.get_using_detailmap(), true);

	texture_->UseTexture();
	detailmap->UseTexture();

	mesh_->RenderMesh();
}

void BttController::getCameraPosition(const glm::vec3& pos) { cam = pos; }

bool BttController::load_mesh() {
	if (!heightmap_) {
		std::cout << "Heightmap not loaded!" << std::endl;
		return false;
	}

	Update(cam);

	return true;
}

void BttController::CreateTerrain(int chunkSize, int chunkDetail, int n) {
	std::vector<Btt> temp;
	int offset = 0;
	bool addOn = true;

	chunk_size = chunkSize;
	chunk_detail = chunkDetail;

	GenerateVertices(chunkSize, chunkDetail);

	std::cout << "PASSED VERTICES GENEREATION" << std::endl;
	GLuint nsize = (chunkSize - 1);
	GLuint dsize = (chunkDetail - 1);
	GLuint baseOrigin = (chunkDetail + ((dsize) * (nsize))) * dsize;

	for (int i = 0; i < chunkSize; ++i) {
		for (int j = 0; j < chunkSize; ++j) {
			Btt temp_btt_sw = Btt();
			Btt temp_btt_ne = Btt();
			GLuint origin = baseOrigin + (j * dsize) + (i * baseOrigin);
			glm::vec3 vector_temp_sw;
			glm::vec3 vector_temp_ne;

			// temp_btt.Insert(chunkDetail, flip);

			vector_temp_sw = glm::vec3(origin, (baseOrigin * i) + (j * dsize),
			                           origin + dsize);
			temp_btt_sw.Insert(vector_temp_sw, chunkDetail, false);
			temp.push_back(temp_btt_sw);

			vector_temp_ne =
			    glm::vec3((baseOrigin * i) + (j * dsize) + dsize,
			              origin + dsize, (baseOrigin * i) + (j * dsize));
			temp_btt_ne.Insert(vector_temp_ne, chunkDetail, true);
			temp.push_back(temp_btt_ne);

			// along the z-axis
			bttCenters.push_back(
			    glm::vec2(((chunkDetail - 1) * i) + ((chunkDetail - 1) / 2),
			              ((chunkDetail - 1) * j) + ((chunkDetail - 1) / 2)));
		}
		// adds to the y-axis
		bttMap.push_back(temp);
		temp.clear();
	}

	std::cout << "\n\nPASSED INDICES GENEREATION\n\n" << std::endl;

	for (int k = 0; k < (n * 2 + 1); ++k) {
		distances.push_back(chunkDetail * 2.5 * (k + 1));
		std::cout << "Distance " << k << ": " << distances.at(k) << std::endl;
	}
}

void BttController::checkTJunction() {
	bool canThing = false;

	for (int i = 0; i < chunk_size; ++i) {
		int iu = i + 1;  // sw triangle, down side check
		int id = i - 1;  // ne triangle, up side check

		for (int j = 0; j < chunk_size; ++j) {
			int jl = (j * 2) - 1;  // sw triangle, left side check
			int jr = (j * 2) + 1;  // ne triangle, right side check

			if (bttMap.at(i).at(j).getLOD() % 2 == 0)
				canThing = true;
			else
				canThing = false;
			// out of bounds checking
			// sw triangle
			if (jl >= 0) {
				if (bttMap.at(i).at(jl).getLOD() ==
				        bttMap.at(i).at(j).getLOD() + 1 &&
				    canThing)  // check left
				{
					bttMap.at(i).at(j * 2).addLeft();
				}
			}
			if (id >= 0) {
				if (bttMap.at(id).at(j).getLOD() ==
				        bttMap.at(i).at(j).getLOD() + 1 &&
				    canThing) {  // check down
					bttMap.at(i).at(j * 2).addRight();
				}
			}

			// ne triangle
			if (jr >= chunk_size * 2) {
				if (bttMap.at(i).at(jr).getLOD() ==
				        bttMap.at(i).at(j).getLOD() + 1 &&
				    canThing) {  // check right
					bttMap.at(i).at(j * 2 - 1).addLeft();
				}
			}
			if (iu >= chunk_size * 2) {
				if (bttMap.at(iu).at(j).getLOD() ==
				        bttMap.at(i).at(j).getLOD() + 1 &&
				    canThing) {  // check up
					bttMap.at(i).at(j * 2 - 1).addRight();
				}
			}

			// std::cout << "Tile " << i << j << "| left: " << i << jl
			//         << " right: " << i << jr << " up: " << iu << j * 2
			//       << " down: " << id << j * 2 + 1 << std::endl;
		}
	}
}

const GLuint BttController::findLOD(glm::vec3 pos, glm::vec2 center) {
	// GLfloat dist =
	//     glm::distance(center, glm::vec2(pos.x + height_map_size, pos.z));
	GLfloat dist = abs((pos.x + height_map_size) - center.x);
	// GLfloat dist =
	//    glm::distance(center, glm::vec2(pos.x + height_map_size, pos.z));
	//  std::cout << dist << std::endl;
	//    std::cout << " Center x: " << center.x << " z: " << center.y
	//              << "    Pos x: " << pos.x << " z: " << pos.z << std::endl;
	for (int i = 0; i < distances.size(); ++i) {
		if (dist < distances.at(i)) {
			return (distances.size() - i);
		}
	}
	return 1;
}

const std::vector<glm::vec2>& BttController::getCenters() { return bttCenters; }

void BttController::getAllIndices(glm::vec3 pos) {
	std::vector<glm::vec3> stored;
	current_total_indices = 0;
	indices.clear();
	// TestThings();

	// float total_time = glfwGetTime();
	// float time_in_lod = 0, tempTime;
	// float time_in_get_indices = 0;
	// float constructor_time = 0, constructor_temp_time;
	GLuint lod;
	int add;

	for (int i = 0; i < chunk_size; ++i) {
		// std::cout << "Break!" << std::endl;

		for (int j = 0; j < chunk_size * 2; ++j) {
			// constructor_temp_time = glfwGetTime();
			// constructor_time += glfwGetTime() - constructor_temp_time;
			if (chunk_size != 1)
				add = int(j / chunk_size);
			else
				add = 0;

			// std::cout << "ADD: " << add << std::endl;
			// tempTime = glfwGetTime();
			lod = findLOD(pos, bttCenters.at((i * chunk_size) + add));
			// time_in_lod += glfwGetTime() - tempTime;

			// tempTime = glfwGetTime();
			//    0.01 seconds --> 0.007
			stored = bttMap.at(i).at(j).getIndices(lod);
			// time_in_get_indices += glfwGetTime() - tempTime;

			// 0.005 seconds
			for (int k = 0; k < stored.size(); ++k) {
				indices.emplace_back(stored.at(k).x);
				indices.emplace_back(stored.at(k).y);
				indices.emplace_back(stored.at(k).z);
			}
		}
	}

	// std::cout << "total time: " << glfwGetTime() - total_time <<
	// std::endl; std::cout << "lod time: " << time_in_lod << std::endl;
	// std::cout << "get indicies time: " << time_in_get_indices << std::endl;
	// std::endl; std::cout << "constructor time: " << constructor_time <<
	// std::endl;

	current_total_indices += indices.size();

	// std::cout << "SIZE: " << indices.size() << std::endl;
}

void BttController::Update(glm::vec3 position) {
	if (firstRun) {
		position.x += 0.1;
		firstRun = false;
	}

	if (position.x != prev_pos.x || position.z != prev_pos.z) {
		mesh_ = std::make_shared<Mesh>();
		getAllIndices(position);
		mesh_->CreateMesh(vertices.data(), indices.data(), vertices.size(),
		                  indices.size());
	}
	prev_pos = position;
}

void BttController::GenerateVertices(int chunkSize, int chunkDetail) {
	int length = chunk_detail + ((chunk_detail - 1) * (chunk_size - 1));

	if (!heightmap_) {
		std::cout << "No heightmap detected!" << std::endl;
	}

	try {
		for (int i = 0; i < length; ++i) {
			for (int j = 0; j < length; ++j) {
				// vertices
				vertices.push_back((GLfloat)i);
				vertices.push_back((GLfloat)heightmap_[(j * length) + i]);
				vertices.push_back((GLfloat)j);

				// Texture coordinates
				vertices.push_back(i / static_cast<GLfloat>(length));
				vertices.push_back(j / static_cast<GLfloat>(length));

				glm::vec3 normal = calculate_terrain_normal(i, j);

				// Normals
				vertices.push_back(-normal.x);
				vertices.push_back(-normal.y);
				vertices.push_back(-normal.z);
			}
		}
	} catch (std::bad_alloc& exception) {
		std::cerr << "bad_alloc detected: " << exception.what();
	}
}

void BttController::set_height_map_size(float size) { height_map_size = size; }

void BttController::set_texture_id(GLuint id) {
	texture_ = std::make_shared<Texture>();
	texture_->set_texture_id(id);
}

bool BttController::load_texture(const char* file_name) {
	texture_ = std::make_shared<Texture>(file_name);
	return texture_->LoadTextureA();
}

bool BttController::load_detailmap(const char* file_name) {
	detailmap = std::make_shared<Texture>(file_name);
	detailmap->set_texture_unit(GL_TEXTURE3);
	return detailmap->LoadTexture();
}
