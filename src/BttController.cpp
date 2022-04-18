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
	mesh.~Mesh();
	heightMap.clear();
	distances.clear();
	current_total_indices = 0;
	chunk_size = 0;
	chunk_detail = 0;
}



void BttController::CreateTerrain(int chunkSize, int chunkDetail, glm::vec3 position) 
{
	std::vector<Btt> temp;
	int offset = 0;
	bool addOn = true;

	chunk_size = chunkSize;
	chunk_detail = chunkDetail;

	/*
	if (heightMap.size() == 0) {
		std::cout << "No heightmap!" << std::endl;
		return;
	}
	*/

	GenerateVertices(chunkSize, chunkDetail);

	std::cout << "PASSED VERTICES GENEREATION" << std::endl;
	GLuint nsize = (chunkSize - 1);
	GLuint baseOrigin = ((chunkDetail * chunkSize) - nsize) * nsize;
	std::cout << "BASE: " << baseOrigin << std::endl;
	for (int i = 0; i < chunkSize; ++i) {
		for (int j = 0; j < chunkSize; ++j) {

			Btt temp_btt_sw = Btt();
			Btt temp_btt_ne = Btt();
			GLuint origin = baseOrigin + (j * nsize) + (i * baseOrigin);
			glm::vec3 vector_temp_sw;
			glm::vec3 vector_temp_ne;

			//temp_btt.Insert(chunkDetail, flip);

			vector_temp_sw = glm::vec3(origin, (baseOrigin * i) + (j * nsize),
				                origin + nsize);
			temp_btt_sw.Insert(vector_temp_sw, chunkDetail, false);
			temp.push_back(temp_btt_sw);

			vector_temp_ne = glm::vec3((baseOrigin * i) + (j * nsize) + nsize,
				                origin + nsize, (baseOrigin * i) + (j * nsize));
			temp_btt_ne.Insert(vector_temp_ne, chunkDetail, true);
			temp.push_back(temp_btt_ne);

			// along the z-axis
			bttCenters.push_back( glm::vec2((chunkDetail * j) + (chunkDetail / 2), (chunkDetail * i) + (chunkDetail / 2)));

			std::cout << "BTT " << i << j << "|  offset: " << offset << " center: x: " << bttCenters.at(int((i * chunkSize) + j)).x
			<< " z: " << bttCenters.at((i * chunkSize) + j).y << std::endl;

			std::cout << "Tri " << i << j << " | x : " << vector_temp_sw.x << " y : " << vector_temp_sw.y
			          << " z: " << vector_temp_sw.z << std::endl;
			std::cout << "Tri " << i << j << " | x : " << vector_temp_ne.x
			          << " y : " << vector_temp_ne.y << " z: " << vector_temp_ne.z
			          << std::endl;
		}
		// adds to the y-axis
		bttMap.push_back(temp);
		temp.clear();
	}

	std::cout << "\n\nPASSED INDICES GENEREATION\n\n" << std::endl;
	
	// temp variables for adjacent triangles
	Node* left = nullptr;
	Node* right = nullptr;
	Node* up = nullptr;
	Node* down = nullptr;
	
	// links neighbour triangles to btts
	for (int i = 0; i < chunkSize; ++i) {
		int iu = i + 1;  // sw triangle, down side check
		int id = i - 1;  // ne triangle, up side check

		for (int j = 0; j < chunkSize; ++j) {
			int jl = (j * 2) - 1;      // sw triangle, left side check
			int jr = (j * 2 + 1) + 1;  // ne triangle, right side check

			// out of bounds checking
			if (jl >= 0)
				left = bttMap.at(i).at(jl).getRoot();  // links to left side of tile
			if(jr < chunkSize * 2)
				right = bttMap.at(i).at(jr).getRoot(); //links to right side of tile
			if(iu < chunkSize)
				up = bttMap.at(iu).at(j * 2).getRoot(); //links to tile above
			if(id >= 0)
				down = bttMap.at(id).at(j * 2 + 1).getRoot(); //links to tile below
		
			bttMap.at(i).at(j * 2).setAdjacentTriangles(left, down);
			bttMap.at(i).at(j * 2 + 1).setAdjacentTriangles(right, up);

			std::cout << "Tile " << i << j << "| left: " <<  i << jl
			          << " right: " <<i << jr << " up: " << iu << j*2 << " down: " << id << j * 2 + 1 << std::endl;
		}

		// sets all pointers to null
		left = nullptr;
		right = nullptr;
		up = nullptr;
		down = nullptr;
	}

	std::cout << "\n\nTILE LINKING PASSED!\n\n" << std::endl;

	for (int k = 0; k < chunkDetail; ++k) {
		distances.push_back(chunkDetail * 1.44 * k);
		std::cout << "Distance " << k << ": " << distances.at(k) << std::endl;
	}
}

void TestThings() {

}

const GLuint BttController::findLOD(glm::vec3 pos, glm::vec2 center) {
	for (int i = 0; i < distances.size(); ++i) {
		if (glm::distance(glm::vec2(pos.x, pos.z), center) < distances.at(i))
			return ((distances.size() - 1) - i);
	}
}

const GLuint* BttController::convertInt(const std::vector<glm::vec3>& temp) {
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

const GLfloat* BttController::convertFloat(const std::vector<glm::vec3>& temp) {
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

const GLuint* BttController::getAllIndices(glm::vec3 pos) {
	std::vector<glm::vec3> start;
	std::vector<glm::vec3> stored;
	current_total_indices = 0;

	for (int i = 0; i < chunk_size; ++i) {
		for (int j = 0; j < chunk_size; ++j) {
			try {
				Btt temp = Btt(bttMap.at(i).at(j));
				stored = temp.getIndices(2);
			} catch (std::bad_alloc& exception) {
				std::cout << "Error 1: " << exception.what() << std::endl;
			}
			try {
				for (int k = 0; k < stored.size(); ++k) {
					start.push_back(stored.at(k));
					std::cout << "pass" << std::endl;
					std::cout << "INDICE " << i << j << " NO: " << k << " | "
					          << start.at(start.size() - 1).x
					          << " y : " << start.at(start.size() - 1).y
					          << " z: " << start.at(start.size() - 1).z
					          << std::endl;
				}
			} catch (std::bad_alloc& exception) {
				std::cout << "Error 2: " << exception.what() << std::endl;
			}
			// findLOD(pos, bttCenters.at((i * unsigned int(chunk_size)) + j))

			current_total_indices += stored.size();
			stored.clear();
		}
	}

	return convertInt(start);
}

void BttController::Update(glm::vec3 position) {
	if (position != prev_pos) {
		mesh.CreateMesh(convertFloat(vertices), getAllIndices(position), vertices.size(),
		               current_total_indices);
	}
	//mesh.RenderMesh();
}


void BttController::GenerateVertices(int chunkSize, int chunkDetail) {
	int length = (chunkSize * chunkDetail) - (chunkSize - 1);
	bool addOn = false;
	float y = 0.0f;
	// heightMap[(i * length) + j]
	try {
		for (int i = 0; i < length; ++i) {
			for (int j = 0; j < length; ++j) {
				vertices.push_back(glm::vec3(i, y, j));
			}
		}

		for (int l = 0; l < vertices.size(); ++l) {
			std::cout << "v" << l << "| x: " << vertices.at(l).x
			          << " y: " << vertices.at(l).y
			          << " z: " << vertices.at(l).z << std::endl;
		}
	} catch (std::bad_alloc & exception) {
		std::cerr << "bad_alloc detected: " << exception.what();
	}
	
}