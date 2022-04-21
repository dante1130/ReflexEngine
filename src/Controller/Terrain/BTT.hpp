#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

struct Node {
	
	glm::vec3 point; ///Holds indices for given triangle

	// Children of triangle
	Node* left;
	Node* right;

	unsigned int lod; ///Level of detail for given triangle
};

/**
 * @class Binary Triangle Tree class
 */
class Btt {
public:
	Btt();  /// Default constructor

	Btt(const Btt& other); ///Copy constructor for BTT

	Btt& operator=(const Btt& treeCopy);  /// equals operator overloader for BTT

	~Btt(); ///Deconstructor for BTT 

	/**
	 * @brief	Creates a BTT based of given indices, detail size and whether
	 * BTT is North-East type or South-West type (i.e is it flipped)
	 *
	 * @param	temp - starting indices, indices of largest triangle (level of
	 * detail 1)
	 * @param	size - length/width of a tile (in vertices)
	 * @param	isFlip -  indicates whether given BTT is North-East or South-West
	 * triangle type triangle type or South-West triangle type
	 *
	 * @return void
	 */
	void Insert(const glm::vec3& temp, unsigned int size, bool isFlip);

	/**
	 * @brief	Returns all indices needed for a given level of detail
	 *
	 * @param	level - Level of detail needed for BTT
	 *
	 * @return vector of indices for triangles
	 */
	const std::vector<glm::vec3>& getIndices(const int level);

	/**
	 * @brief	Gets the size of current indices
	 *
	 * @return 	size of current indices
	 */
	const GLuint getIndexSize();

	/**
	 * @brief	Gets the current level of detail
	 *
	 * @return  returns current level of detail
	 */
	unsigned int getLOD();

	/**
	 * @brief	Destroys a node of tree
	 *
	 * @return void
	 */
	void destroyTree();

	/**
	 * @brief	Gets all the current indices stored in BTT
	 *
	 * @return all of the currently used indices
	 */
	const std::vector<glm::vec3>& getCurrentIndices();

	/**
	 * @brief	Adds lower levels of detail triangles that touch left edges
	 * to current indices, used for removing t-junctions
	 *
	 * @return void
	 */
	void addLeft();

	/**
	 * @brief	Adds lower levels of detail triangles that touch left edges
	 * to current indices, used for removing t-junctions
	 *
	 * @return void
	 */
	void addRight();

private:
	/**
	 * @brief	Creates a node to add into BTT
	 *
	 * @param	lod - level of detail
	 * @param 	data - indices for a given triangle
	 *
	 * @return pointer to created node
	 */
	Node* createNode(const unsigned int& lod, const glm::vec3& data);

	/**
	 * @brief	Searches through tree and creates copies of nodes
	 *
	 * @param	nodeCopy - pointer address of original node
	 * @param	node - pointer to new tree/tree nodes being created
	 *
	 * @return void
	 */
	void copyTree(Node*& nodeCopy, Node* node);

	/**
	 * @brief	Inserts a node into BTT
	 *
	 * @param	node - current node being used
	 *
	 * @return void
	 */
	void Insert(Node* node);

	/**
	 * @brief	Gets the indices for a given node and adds to current indices
	 *
	 * @param	node - current node being used
	 * @param	level - level of detail being used for extraction
	 *
	 * @return void
	 */
	const void getIndices(Node* node, int level);

	/**
	 * @brief	Deletes a given node of a tree
	 *
	 * @param	node - current node being used
	 *
	 * @return void
	 */
	void destroyTree(Node* node);

	/**
	 * @brief	Finds the midpoint between two indices
	 *
	 * @param	p1 - left most indice
	 * @param	p2 - right most indice
	 *
	 * @return void
	 */
	GLuint findMid(unsigned int p1, unsigned int p2);

	/**
	 * @brief	Checks if a triangle should be added to left side triangles
	 *
	 * @param	node - current node being used
	 * @param 	i - the index of node in current indices
	 *
	 * @return void
	 */
	void addToLeft(Node* node, const int& i);

	/**
	 * @brief	Checks if a triangle should be added to left side triangles
	 *
	 * @param	node - current node being used
	 * @param 	i - the index of node in current indices
	 *
	 * @return void
	 */
	void addToRight(Node* node, const int& i);

	Node* bttNode;				/// Holds indices for all triangles

	Btt* leftTriangle;			/// BTT touching left side of main triangle (origin and left)
	Btt* rightTriangle;			/// BTT touching right side of main triangle (origin and right)

	
	std::vector<glm::vec3> leftSideTriangles;	/// Stores triangles touching left side (only stores for certain LOD)
	std::vector<glm::vec3> rightSideTriangles;	/// Stores triangles touching right side (only stores for certain LOD)
	std::vector<glm::vec3> currentIndices;		/// Current indices being used
	std::vector<int> bigLeftTriangles;			/// Holds indexs for left side triangles inside current indices
	std::vector<int> bigRightTriangles;			/// Holds indexs for right side triangles inside current indices

	unsigned int currentLod;					/// The current level of detail
	unsigned int depth;							/// Stores total depth
	bool isFlipped;								/// Whether BTT is North-East or South-West triangle type
};
