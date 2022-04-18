#include "BTT.hpp"


Btt::Btt()  /// Default constructor
{
	bttNode = nullptr;
	leftTriangle = nullptr;
	rightTriangle = nullptr;
	isFlipped = false;
	depth = 0;
	currentLod = 0;
	sizeOfIndexArray = 0;
}

Btt::~Btt() 
{ 
	destroyTree(); 
}


void Btt::destroyTree() 
{
	destroyTree(bttNode);
	leftSideTriangles.clear();
	rightSideTriangles.clear();
	leftTriangle = nullptr;
	rightTriangle = nullptr;
}

void Btt::destroyTree(Node* node) 
{
	if (node != nullptr) {
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
	}
}


Btt::Btt(const Btt& treeCopy) {

	this->depth = treeCopy.depth;
	this->currentLod = treeCopy.currentLod;
	this->isFlipped = treeCopy.isFlipped;
	this->sizeOfIndexArray = treeCopy.sizeOfIndexArray;
	this->leftSideTriangles = treeCopy.leftSideTriangles;
	this->rightSideTriangles = treeCopy.rightSideTriangles;

	if (treeCopy.bttNode == nullptr)
		bttNode = nullptr;
	else {
		copyTree(bttNode, treeCopy.bttNode);
	}
}

Btt& Btt::operator=(const Btt& treeCopy) {
	if (this != &treeCopy) {
		if (bttNode != nullptr) 
			destroyTree(bttNode);
		if (treeCopy.bttNode == nullptr)
			bttNode = nullptr;
		else
			copyTree(bttNode, treeCopy.bttNode);
	}

	return *this;
}


void Btt::copyTree(Node*& nodeCopy, Node* node) {
	if (node == nullptr) {
		nodeCopy = nullptr;
	} else {
		nodeCopy = createNode(node->lod - 1, node->point);
		copyTree(nodeCopy->left, node->left);
		copyTree(nodeCopy->right, node->right);
	}
}

void Btt::setAdjacentTriangles(Node* left, Node* right) {
	leftTriangle = left;
	rightTriangle = right;
}

void Btt::Insert(const glm::vec3& temp, unsigned int size, bool isFlip) {
	if (size < 1) return;
	if (bttNode != nullptr) return;

	isFlipped = isFlip;
	bttNode = new Node();
	// Order: Origin (point opposite hypotenus), Left, Right
	bttNode->point = glm::vec3(temp.x, temp.y, temp.z);

	depth = size;
	bttNode->lod = 1;

	//std::cout << "Size: " << depth << std::endl;

	if (bttNode->lod < depth) {
		Insert(bttNode);
	}
	//std::cout << "PASSED" << std::endl;
}

void Btt::Insert(unsigned int size, bool isFlip) {
	if (size < 1) 
		return;
	if (bttNode != nullptr)
		return;

	isFlipped = isFlip;
	bttNode = new Node();
	//Order: Origin (point opposite hypotenus), Left, Right
	if (!isFlipped)
		bttNode->point = glm::vec3((size * (size - 1)), 0, (size * size) - 1);
	else
		bttNode->point = glm::vec3(size - 1, (size * size) - 1, 0);

	depth = size;
	bttNode->lod = 1;

	std::cout << "Size: " << depth << std::endl;
	
	if (bttNode->lod < depth) {
		Insert(bttNode);
	}
	std::cout << "PASSED" << std::endl;
}

Node* Btt::getRoot() {
	return bttNode; 
}

void Btt::Insert(Node* node) {

	// find midpoint of hypotenus
	GLuint mid = findMid(node->point.y, node->point.z);
	node->left = createNode(node->lod, glm::vec3(mid, node->point.x, node->point.y));
	node->right = createNode(node->lod, glm::vec3(mid, node->point.z, node->point.x));


	if (node->lod + 1 < depth) {
		Insert(node->left);
		Insert(node->right);
	}
}

GLuint Btt::findMid(unsigned int p1, unsigned int p2) {

	return (p1 + p2) / 2;
}

Node* Btt::createNode(const unsigned int& lod, const glm::vec3& data) {
	Node* temp = new Node();

	temp->point = data;
	temp->lod = lod + 1;

	return temp;
}

const GLuint Btt::getIndexSize() { 
	return sizeOfIndexArray; 
}

const GLuint* Btt::convertInt(const std::vector<glm::vec3>& temp) {
	
	GLuint size = getIndexSize() * GLuint(3);
	GLuint* buffer{new GLuint[size]{}};
	//std::cout << "INDEX COUNT:  " << getIndexSize() << std::endl;
	for (int i = 0; i < temp.size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			buffer[(3 * i) + j] = temp.at(i)[j];
		}
	}
	return buffer;
}

const GLuint* Btt::getIndicesCoverted(const int level) {
	return convertInt(getIndices(level));
}

const std::vector<glm::vec3>& Btt::getIndices(const int level) 
{
	std::vector<glm::vec3> temp;

	leftSideTriangles.clear();
	rightSideTriangles.clear();


	currentLod = level;
	if (level > depth) {
		std::cout << "ERROR: level exceeds depth" << std::endl;
		return temp;
	} else if (level <= 0) {
		std::cout << "ERROR: level is zero or less" << std::endl;
		return temp;
	}


	if (bttNode->lod == level) {
		temp.push_back(bttNode->point);
		//std::cout << "TRUE!" << std::endl;
	} else {
		getIndices(bttNode, temp, level);
	}

	sizeOfIndexArray = temp.size();
	//for (int i = 0; i < temp.size(); ++i)
		//std::cout << "Index " << i << ": " << temp[i].x << " " << temp[i].y << " " << temp[i].z << std::endl;
	/*
	std::cout << "LEFT SIDE: " << std::endl;
	for (int j = 0; j < leftSideTriangles.size(); ++ j) {
		std::cout << "Index " << j << ": " << leftSideTriangles[j]->point.x
		          << " " << leftSideTriangles[j]->point.y << " "
		          << leftSideTriangles[j]->point.z << std::endl;
	}
	std::cout << "RIGHT SIDE: " << std::endl;
	for (int k = 0; k < rightSideTriangles.size(); ++k) {
		std::cout << "Index " << k << ": " << rightSideTriangles[k]->point.x
		          << " " << rightSideTriangles[k]->point.y << " "
		          << rightSideTriangles[k]->point.z << std::endl;
	}
	*/
	return temp;
}

const void Btt::getIndices(Node* node, std::vector<glm::vec3>& temp, int level) {
	std::cout << "NODE VALUE:  " << node->lod << "  LEVEL: " << level << std::endl;
	if ((node->lod + 1) < level) {
		getIndices(node->left, temp, level);
		getIndices(node->right, temp, level);
	} else {
		temp.push_back(node->left->point);
		temp.push_back(node->right->point);

		if (((int)node->lod + 1) % 2 == 0) {
			std::cout << "Were in" << std::endl;
			addToLeft(node->left);
			addToLeft(node->right); 
			addToRight(node->left);
			addToRight(node->right);
		}
	}
}

void Btt::addToLeft(Node* node) { 
	GLuint diff;
	
	if (!isFlipped) {
		diff = (bttNode->point.x - bttNode->point.y) / (depth -1); 
		std::cout << "Not Flipped| Diff : " << diff << " depth-1: " << (depth - 1) << std::endl;
		if ((int)node->point.y % (int)diff == 0 &&
		    (int)node->point.z % (int)diff == 0) {
			leftSideTriangles.push_back(node);
		}
	}else {
		diff = (bttNode->point.y - bttNode->point.x) / (depth - 1); 
		std::cout << "Flipped| Diff : " << diff << " depth-1: " << (depth - 1) << std::endl;
		if ((int)node->point.y - (depth - 1) % (int)diff == 0 &&
		    (int)node->point.z - (depth - 1) % (int)diff == 0) {
			Node* temp = new Node(node);
			leftSideTriangles.push_back(node);
			std::cout << "Passed1" << std::endl;
		}
	}
}

void Btt::addToRight(Node* node) { 
	GLuint min;
	GLuint max;
	if (!isFlipped) {
		min = bttNode->point.z - (depth - 1);
		max = bttNode->point.z;
	}else {
		min = bttNode->point.z;
		max = bttNode->point.z + (depth - 1);
	}

	if (((int)node->point.y >= min && (int)node->point.y < max) &&
	    ((int)node->point.z >= min &&(int) node->point.z < max)) {
		rightSideTriangles.push_back(node);
		std::cout << "Passed2" << std::endl;
	}
}
