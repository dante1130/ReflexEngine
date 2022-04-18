#pragma once

//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <vector>

#include "Mesh.hpp"
#include "BTT.hpp"


class BttController {
		public:

			BttController();

			~BttController();

			void AddHeightMap(std::vector<float> hmap);
		
			void AddHeightMap(GLfloat* hmap);

			void CreateTerrain(int chunkSize, int chunkDetail, glm::vec3 position);
			
			void TestThings();

			void Update(glm::vec3 player);

			const GLuint* getAllIndices(glm::vec3 pos);
		
		private:
	
			void GenerateVertices(int chunkSize, int chunkDetail);

			const GLuint findLOD(glm::vec3 pos, glm::vec2 center);
		
			const GLuint* convertInt(const std::vector<glm::vec3>& temp);

			const GLfloat* convertFloat(const std::vector<glm::vec3>& temp);

			std::vector<std::vector<Btt>> bttMap; //all binary trees containing indices
			std::vector<glm::vec2> bttCenters; //all
			std::vector<glm::vec3> vertices;

			std::vector<GLfloat> heightMap;
	        std::vector<GLfloat> distances;
			
			Mesh mesh;

			glm::vec3 prev_pos;
			GLuint current_total_indices;
	        GLuint chunk_size;
	        GLuint chunk_detail;
};