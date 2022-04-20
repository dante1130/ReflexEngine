#include "BttController.hpp"

#include <iostream>

BttController::BttController() {
	prev_pos = glm::vec3(0,0,0);
	current_total_indices = 0;
	chunk_size = 0;
	chunk_detail = 0;
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

void BttController::render(std::shared_ptr<Shader> shader) {
	if (!mesh_) return;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, get_origin());
	model = glm::scale(model, scale_);

	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader->GetUsingTexture(), !mesh_->has_color());

	mesh_->RenderMesh();
}

void BttController::getCameraPosition(const glm::vec3& pos) 
{ 
	cam = pos; 
}

bool BttController::load_mesh() {
	if (!heightmap_) {
		std::cout << "Heightmap not loaded!" << std::endl;
		return false;
	}
	
	
	Update(cam);




	return true;
}



void BttController::CreateTerrain(int chunkSize, int chunkDetail, int n) 
{
	std::vector<Btt> temp;
	int offset = 0;
	bool addOn = true;

	chunk_size = chunkSize;
	chunk_detail = chunkDetail;

	/*
	if (heightmap_ == nullptr) {
		std::cout << "No heightmap!" << std::endl;
		return;
	}
	*/

	GenerateVertices(chunkSize, chunkDetail);

	std::cout << "PASSED VERTICES GENEREATION" << std::endl;
	GLuint nsize = (chunkSize - 1);
	GLuint dsize = (chunkDetail - 1);
	GLuint baseOrigin = (chunkDetail + ((dsize) * (nsize))) * dsize;
	std::cout << "BASE: " << baseOrigin << " chunkDetail-1: " << chunkDetail - 1
	          << " chunkSize: " << nsize << std::endl;
	for (int i = 0; i < chunkSize; ++i) {
		for (int j = 0; j < chunkSize; ++j) {

			Btt temp_btt_sw = Btt();
			Btt temp_btt_ne = Btt();
			GLuint origin = baseOrigin + (j * dsize) + (i * baseOrigin);
			glm::vec3 vector_temp_sw;
			glm::vec3 vector_temp_ne;

			//temp_btt.Insert(chunkDetail, flip);

			vector_temp_sw = glm::vec3(origin, (baseOrigin * i) + (j * dsize), origin + dsize);
			temp_btt_sw.Insert(vector_temp_sw, chunkDetail, false);
			temp.push_back(temp_btt_sw);

			vector_temp_ne = glm::vec3((baseOrigin * i) + (j * dsize) + dsize, origin + dsize, (baseOrigin * i) + (j * dsize));
			temp_btt_ne.Insert(vector_temp_ne, chunkDetail, true);
			temp.push_back(temp_btt_ne);

			// along the z-axis
			bttCenters.push_back( glm::vec2(((chunkDetail - 1) * i) + ((chunkDetail - 1)/2), ((chunkDetail - 1) * j) + ((chunkDetail - 1)/2)));

			/*
			std::cout << "BTT " << i << j << "|  offset: " << offset << " center: x: " << bttCenters.at(int((i * chunkSize) + j)).x
			<< " z: " << bttCenters.at((i * chunkSize) + j).y << std::endl;

			std::cout << "Tri " << i << j << " | x : " << vector_temp_sw.x << " y : " << vector_temp_sw.y
			          << " z: " << vector_temp_sw.z << std::endl;
			std::cout << "Tri " << i << j << " | x : " << vector_temp_ne.x
			          << " y : " << vector_temp_ne.y << " z: " << vector_temp_ne.z
			          << std::endl;
					  */
		}
		// adds to the y-axis
		bttMap.push_back(temp);
		temp.clear();
	}

	std::cout << "\n\nPASSED INDICES GENEREATION\n\n" << std::endl;


	for (int k = 0; k < (n * 2 + 1); ++k) {
		distances.push_back(chunkDetail * 1.44 * (k + 1));
		std::cout << "Distance " << k << ": " << distances.at(k) << std::endl;
	}
}

void BttController::TestThings() {
	bool canThing = false;

	for (int i = 0; i < chunk_size; ++i) {
		int iu = i + 1;  // sw triangle, down side check
		int id = i - 1;  // ne triangle, up side check

		for (int j = 0; j < chunk_size; ++j) {
			int jl = (j * 2) - 1;      // sw triangle, left side check
			int jr = (j * 2) + 1;  // ne triangle, right side check

			if (bttMap.at(i).at(j).getLOD() % 2 == 0)
				canThing = true;
			else
				canThing = false;
			// out of bounds checking
			//sw triangle
			if (jl >= 0) {
				if (bttMap.at(i).at(jl).getLOD() == bttMap.at(i).at(j).getLOD() + 1 && canThing) //check left
				{
					bttMap.at(i).at(j * 2).addLeft();
				}
			}  
			if (id >= 0) {
				if (bttMap.at(id).at(j).getLOD() == bttMap.at(i).at(j).getLOD() + 1 && canThing) {  // check down
					bttMap.at(i).at(j * 2).addRight();
				}
			}

			//ne triangle
			if (jr >= chunk_size * 2) {
				if (bttMap.at(i).at(jr).getLOD() == bttMap.at(i).at(j).getLOD() + 1 && canThing) {  //check right
					bttMap.at(i).at(j * 2 - 1).addLeft();
				}
			}
			if (iu >= chunk_size * 2) {
				if (bttMap.at(iu).at(j).getLOD() == bttMap.at(i).at(j).getLOD() + 1 && canThing) { //check up
					bttMap.at(i).at(j * 2 - 1).addRight();
				}
			}
		

			//std::cout << "Tile " << i << j << "| left: " << i << jl
			  //        << " right: " << i << jr << " up: " << iu << j * 2
			    //      << " down: " << id << j * 2 + 1 << std::endl;
		}
	}
}

const GLuint BttController::findLOD(glm::vec3 pos, glm::vec2 center) {
	GLfloat dist = glm::distance(center, glm::vec2(pos.x, pos.z));
	//std::cout << dist << std::endl;
	//std::cout << " Center x: " << center.x << " z: " << center.y
	  //        << "    Pos x: " << pos.x << " z: " << pos.z << std::endl;
	for (int i = 0; i < distances.size(); ++i) {
		if (dist < distances.at(i)) {
			return (distances.size() - i);
		}
	}
	return 1;
}

GLuint* BttController::convertInt(const std::vector<glm::vec3>& temp) {
	GLuint size = temp.size() * GLuint(3);
	GLuint* buffer{new GLuint[size]{}};
	std::cout << "INDEX COUNT:  " << temp.size() << std::endl;
	for (int i = 0; i < temp.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			buffer[(3 * i) + j] = temp.at(i)[j];
		}
	}
	return buffer;
}

GLfloat* BttController::convertFloat(const std::vector<glm::vec3>& temp) {
	GLuint size = temp.size() * GLuint(3);
	GLfloat* buffer{new GLfloat[size]{}};
	std::cout << "VERTEX COUNT:  " << temp.size() << std::endl;
	for (int i = 0; i < temp.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			buffer[(3 * i) + j] = temp.at(i)[j];
		}
	}
	return buffer;
}

const std::vector<glm::vec2>& BttController::getCenters()
{ 
	return bttCenters; 
}

GLuint* BttController::getAllIndices(glm::vec3 pos) {
	std::vector<glm::vec3> stored;
	current_total_indices = 0;
	indices.clear();
	TestThings();

	for (int i = 0; i < chunk_size; ++i) {
		//std::cout << "Break!" << std::endl;
		for (int j = 0; j < chunk_size * 2; ++j) {

				Btt temp = Btt(bttMap.at(i).at(j));
				GLuint lod;
			    int add;
			    if (chunk_size != 1)
				    add = int(j / chunk_size);
			    else
				    add = 0;

			    //std::cout << "ADD: " << add << std::endl;
				lod = findLOD(pos, bttCenters.at((i * chunk_size) + add));
			    //std::cout << "LOD: " << lod << std::endl;
			    //std::cout << "TILE " << i << j << ": " << lod << std::endl;
			    stored = temp.getIndices(lod);
				
				for (int k = 0; k < stored.size(); ++k) {
				    indices.push_back((GLuint)stored.at(k).x);
				    indices.push_back((GLuint)stored.at(k).y);
				    indices.push_back((GLuint)stored.at(k).z);
					
			    }

			stored.clear();
		}
	}

	current_total_indices += indices.size();

	std::cout << "SIZE: " << indices.size() << std::endl;
	return indices.data();
}

void BttController::Update(glm::vec3 position) {

	if (position != prev_pos) {
		mesh_ = std::make_shared<Mesh>();
		getAllIndices(position);
		//std::cout << "CAM| x: " << position.x << " z: " << position.z
		  //        << std::endl;
		/*
		std::cout << "INDEX SIZE: " << indices.size() << std::endl;
		for (int k = 0; k < indices.size(); ++k) {
		    std::cout << "Index " << k << ": ";
		    for(int i = 0; i < 3; ++i) {
		        std::cout << indices[int((k * 3) + i)] << " ";
		    }
		    std::cout << std::endl;
		}
		*/
		mesh_->CreateMesh(vertices.data(), indices.data(), vertices.size(),
		                  indices.size());
	}
	prev_pos = position;
}


void BttController::GenerateVertices(int chunkSize, int chunkDetail) {
	int length = (chunkSize * chunkDetail) - (chunkSize - 1);
	float y = 0.0f;
	//heightmap_[(i * length) + j]
	if (!heightmap_) {
		std::cout << "YO MAMA" << std::endl;
	}

	try {
		for (int i = 0; i < length; ++i) {
			for (int j = 0; j < length; ++j) {
				vertices.push_back((GLfloat)i);
				//heightmap_[(i * length) + j] = 0.0;
				vertices.push_back((GLfloat)heightmap_[(i * length) + j]);
				vertices.push_back((GLfloat)j);

				// Texture coordinates
				vertices.push_back(i / static_cast<GLfloat>(length));
				vertices.push_back(j / static_cast<GLfloat>(length));

				glm::vec3 normal = calculate_terrain_normal(i, j);

				// Normals
				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);
			}
		}
	} catch (std::bad_alloc & exception) {
		std::cerr << "bad_alloc detected: " << exception.what();
	}
	
}