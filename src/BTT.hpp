#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>


struct Node {
	// holds indexes
	glm::vec3 point;

	// Children of triangle
	Node* left;
	Node* right;

	unsigned int lod;

};

using Function = void (*)(glm::vec3&);

class Btt {
	public:
		Btt();  /// Default constructor

		Btt(const Btt& other);

		Btt& operator=(const Btt& treeCopy);

		~Btt();
	   
		void Insert(unsigned int size, bool isFlip);

		void Insert(const glm::vec3& temp, unsigned int size, bool isFlip);

		std::vector<glm::vec3> getIndices(const int level); 

		const GLuint* getIndicesCoverted(const int level);

		const GLuint getIndexSize();

		Node* getRoot();

		unsigned int getLOD();

		void destroyTree();

		void setAdjacentTriangles(Btt** left, Btt** right);//x

		void setLeftTriangle(Btt* left); //x

		void setRightTriangle(Btt* right);//x

		const std::vector<glm::vec3>& getCurrentIndices(); 

		void addLeft();

		void addRight();

	private:
		
		Node* createNode(const unsigned int& lod, const glm::vec3& data);

		//Node* createLeft(Node* parent, GLuint midpoint);

		//Node* createRight(Node* parent, GLuint midpoint);

		void copyTree(Node*& nodeCopy, Node* node);

		void Insert(Node* node);

		const void getIndices(Node* node, int level); 
		
		void destroyTree(Node* node);

		GLuint findMid(unsigned int p1, unsigned int p2);

		const GLuint* convertInt(const std::vector<glm::vec3>& temp);

		void addToLeft(Node* node, const int& i);

		void addToRight(Node* node, const int& i);

		Node* bttNode; // holds indices for triangles

		Btt* leftTriangle; //touching left side of main triangle (origin and left)
	    Btt* rightTriangle; //touching right side of main triangle (origin and right)

		 // vectors of triangles that hypotenus touch main triangle smaller sides
		std::vector<glm::vec3> leftSideTriangles;
	    std::vector<glm::vec3> rightSideTriangles;
	    std::vector<glm::vec3> currentIndices;
	    std::vector<int> bigLeftTriangles;
	    std::vector<int> bigRightTriangles;

	    unsigned int currentLod;
		unsigned int depth; // stores depth
	    bool isFlipped;
	    GLuint sizeOfIndexArray;
};