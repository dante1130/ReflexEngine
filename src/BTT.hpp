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

	
	Node() { 
		point = glm::vec3(0, 0, 0);
		left = nullptr;
		right = nullptr;
		lod = 0;
	}

	Node(const Node*& other) { 
		point = other->point;
		lod = other->lod;
		left = other->left;
		right = other->right;
	}

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

		const std::vector<glm::vec3>& getIndices(const int level); 

		const GLuint* getIndicesCoverted(const int level);

		const GLuint getIndexSize();

		Node* getRoot();

		void destroyTree();

		void setAdjacentTriangles(Node* left, Node* right);

	private:
		
		Node* createNode(const unsigned int& lod, const glm::vec3& data);

		//Node* createLeft(Node* parent, GLuint midpoint);

		//Node* createRight(Node* parent, GLuint midpoint);

		void copyTree(Node*& nodeCopy, Node* node);

		void Insert(Node* node);

		const void getIndices(Node* node, std::vector<glm::vec3>& temp, int level); 
		
		void destroyTree(Node* node);

		GLuint findMid(unsigned int p1, unsigned int p2);

		const GLuint* convertInt(const std::vector<glm::vec3>& temp);

		void addToLeft(Node* node);

		void addToRight(Node* node);

		
		Node* bttNode; // holds indices for triangles

		Node* leftTriangle; //touching left side of main triangle (origin and left)
	    Node* rightTriangle; //touching right side of main triangle (origin and right)

		 // vectors of triangles that hypotenus touch main triangle smaller sides
		std::vector<Node*> leftSideTriangles;
	    std::vector<Node*> rightSideTriangles;

	    unsigned int currentLod;
		unsigned int depth; // stores depth
	    bool isFlipped;
	    GLuint sizeOfIndexArray;
};