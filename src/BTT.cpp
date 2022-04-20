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

Btt::~Btt() { destroyTree(); }

void Btt::destroyTree() {
	destroyTree(bttNode);
	leftSideTriangles.clear();
	rightSideTriangles.clear();
	leftTriangle = nullptr;
	rightTriangle = nullptr;
}

void Btt::destroyTree(Node* node) {
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
		if (bttNode != nullptr) destroyTree(bttNode);
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

void Btt::setAdjacentTriangles(Btt** left, Btt** right) {
	// std::cout << "left: " << left->lod << " right: " << right->lod <<
	// std::endl;
	leftTriangle = *left;
	rightTriangle = *right;
}

void Btt::setLeftTriangle(Btt* left) {
	leftTriangle = left;
	std::cout << " Left: " << leftTriangle->currentLod << std::endl;
}

void Btt::setRightTriangle(Btt* right) {
	rightTriangle = right;
	std::cout << " Right: " << rightTriangle->currentLod << std::endl;
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

	if (bttNode->lod < depth) {
		Insert(bttNode);
	}
}

void Btt::Insert(unsigned int size, bool isFlip) {
	if (size < 1) return;
	if (bttNode != nullptr) return;

	isFlipped = isFlip;
	bttNode = new Node();
	// Order: Origin (point opposite hypotenus), Left, Right
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

Node* Btt::getRoot() { return bttNode; }

unsigned int Btt::getLOD() { return currentLod; }

void Btt::Insert(Node* node) {
	// find midpoint of hypotenus
	GLuint mid = findMid(node->point.y, node->point.z);
	node->left =
	    createNode(node->lod, glm::vec3(mid, node->point.x, node->point.y));
	node->right =
	    createNode(node->lod, glm::vec3(mid, node->point.z, node->point.x));

	if (node->lod + 1 < depth) {
		Insert(node->left);
		Insert(node->right);
	}
}

GLuint Btt::findMid(unsigned int p1, unsigned int p2) { return (p1 + p2) / 2; }

Node* Btt::createNode(const unsigned int& lod, const glm::vec3& data) {
	Node* temp = new Node();

	temp->point = data;
	temp->lod = lod + 1;

	return temp;
}

const GLuint Btt::getIndexSize() { return sizeOfIndexArray; }

const GLuint* Btt::convertInt(const std::vector<glm::vec3>& temp) {
	GLuint size = getIndexSize() * GLuint(3);
	GLuint* buffer{new GLuint[size]{}};
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

const std::vector<glm::vec3>& Btt::getCurrentIndices() {
	return currentIndices;
}
const std::vector<glm::vec3>& Btt::getIndices(const int level) {
	currentIndices.clear();
	//  leftSideTriangles.clear();
	//  rightSideTriangles.clear();

	currentLod = level;
	if (level > depth) {
		std::cout << "ERROR: level exceeds depth" << std::endl;
		return currentIndices;
	} else if (level <= 0) {
		std::cout << "ERROR: level is zero or less" << std::endl;
		return currentIndices;
	}

	if (bttNode->lod == level) {
		currentIndices.push_back(bttNode->point);
	} else {
		getIndices(bttNode, level);
	}

	sizeOfIndexArray = currentIndices.size();
	return currentIndices;
}

void Btt::addLeft() {
	for (int i = 0; i < bigLeftTriangles.size(); ++i) {
		currentIndices.erase(currentIndices.begin() + bigLeftTriangles.at(i));
	}
	for (int j = 0; j < leftSideTriangles.size(); ++j) {
		currentIndices.push_back(leftSideTriangles.at(j));
	}
}

void Btt::addRight() {
	for (int i = 0; i < bigRightTriangles.size(); ++i) {
		currentIndices.erase(currentIndices.begin() + bigRightTriangles.at(i));
	}
	for (int j = 0; j < rightSideTriangles.size(); ++j) {
		currentIndices.push_back(rightSideTriangles.at(j));
	}
}

const void Btt::getIndices(Node* node, int level) {
	// std::cout << "NODE VALUE:  " << node->lod << "  LEVEL: " << level <<
	// std::endl;

	if ((node->lod + 1) < level) {
		getIndices(node->left, level);
		getIndices(node->right, level);
	} else {
		currentIndices.push_back(node->left->point);
		currentIndices.push_back(node->right->point);

		if (((int)node->lod + 1) % 2 == 0) {
			addToLeft(node->left, currentIndices.size() - 1);
			addToLeft(node->right, currentIndices.size() - 1);
			addToRight(node->left, currentIndices.size());
			addToRight(node->right, currentIndices.size());
		}
	}
}

void Btt::addToLeft(Node* node, const int& i) {
	GLuint diff;

	if (!isFlipped) {
		diff = (bttNode->point.x - bttNode->point.y) / (depth - 1);

		if ((int)node->point.y % (int)diff == 0 &&
		    (int)node->point.z % (int)diff == 0) {
			leftSideTriangles.push_back(node->point);
			bigLeftTriangles.push_back(i);
		}

	} else {
		diff = (bttNode->point.y - bttNode->point.x) / (depth - 1);

		if (((int)(node->point.y - (depth - 1)) % (int)diff == 0) &&
		    ((int)(node->point.z - (depth - 1)) % (int)diff == 0)) {
			leftSideTriangles.push_back(node->point);
			bigLeftTriangles.push_back(i);
		}
	}
}

void Btt::addToRight(Node* node, const int& i) {
	int min;
	int max;

	if (!isFlipped) {
		min = int(bttNode->point.z - (depth - 1));
		max = int(bttNode->point.z);
	} else {
		min = int(bttNode->point.z);
		max = int(bttNode->point.z + (depth - 1));
	}

	if ((int(node->point.y) >= min && int(node->point.y) < max) &&
	    (int(node->point.z) >= min && int(node->point.z) < max)) {
		rightSideTriangles.push_back(node->point);
		bigRightTriangles.push_back(i);
	}
}
