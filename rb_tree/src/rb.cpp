#include "trees/rb.hpp"
#include <iostream>

namespace trees {

RB::RB() : root(nullptr) {
	// Constructor
}

void RB::balance(RBNode* node) {
	// Check for violations and balance the tree
	while (node != root && node->getParent()->getColor() == NodeColor::RED) {
		// If parent is red, check the uncle node
		RBNode* uncle = nullptr;
		if (node->getParent()->isLeft()) {
			uncle = node->getParent()->getParent()->getRight();
		} else {
			uncle = node->getParent()->getParent()->getLeft();
		}

		if (uncle != nullptr && uncle->getColor() == NodeColor::RED) {
			// Case 1: Uncle is red (Recoloring)
			node->getParent()->setColor(NodeColor::BLACK);
			uncle->setColor(NodeColor::BLACK);
			node->getParent()->getParent()->setColor(NodeColor::RED);
			node = node->getParent()->getParent();  // Move to the grandparent
		} else {
			// Case 2, 3, 4: Uncle is black or null (Rotations)
			RotationType rType = getRotationType(node);
			if (rType == RotationType::case_1) {
				// Left rotation
				node = node->getParent();
				rotateLeft(node);
			} else if (rType == RotationType::case_2) {
				// Right rotation
				node = node->getParent();
				rotateRight(node);
			} else if (rType == RotationType::case_3) {
				// Left-right rotation
				rotateLeft(node);
				rotateRight(node->getParent());
			} else if (rType == RotationType::case_4) {
				// Right-left rotation
				rotateRight(node);
				rotateLeft(node->getParent());
			}
		}
	}
	root->setColor(NodeColor::BLACK);  // Ensure root is always black
}

RotationType RB::getRotationType(RBNode* node) {
	// Determine the rotation type based on node and its parent/uncle
	if (node->isLeft() && node->getParent()->isLeft()) {
		return RotationType::case_1; // Left-Left
	} else if (node->isRight() && node->getParent()->isRight()) {
		return RotationType::case_2; // Right-Right
	} else if (node->isLeft() && node->getParent()->isRight()) {
		return RotationType::case_3; // Left-Right
	} else {
		return RotationType::case_4; // Right-Left
	}
}

void RB::rotateLeft(RBNode* node) {
	// Perform left rotation on the node
	RBNode* rightChild = node->getRight();
	node->setRight(rightChild->getLeft());

	if (rightChild->getLeft() != nullptr) {
		rightChild->getLeft()->setParent(node);
	}

	rightChild->setParent(node->getParent());
	if (node->getParent() == nullptr) {
		root = rightChild;
	} else if (node->isLeft()) {
		node->getParent()->setLeft(rightChild);
	} else {
		node->getParent()->setRight(rightChild);
	}

	rightChild->setLeft(node);
	node->setParent(rightChild);
}

void RB::rotateRight(RBNode* node) {
	// Perform right rotation on the node
	RBNode* leftChild = node->getLeft();
	node->setLeft(leftChild->getRight());

	if (leftChild->getRight() != nullptr) {
		leftChild->getRight()->setParent(node);
	}

	leftChild->setParent(node->getParent());
	if (node->getParent() == nullptr) {
		root = leftChild;
	} else if (node->isLeft()) {
		node->getParent()->setLeft(leftChild);
	} else {
		node->getParent()->setRight(leftChild);
	}

	leftChild->setRight(node);
	node->setParent(leftChild);
}

void RB::insert(int val, RBNode* node) {
	// Binary search tree insert
	if (val < node->getData()) {
		if (node->getLeft() == nullptr) {
			node->setLeft(new RBNode(val, node));
		} else {
			insert(val, node->getLeft());
		}
	} else {
		if (node->getRight() == nullptr) {
			node->setRight(new RBNode(val, node));
		} else {
			insert(val, node->getRight());
		}
	}

	// After insertion, balance the tree to maintain Red-Black properties
	balance(node);
}

void RB::insert(int val) {
	if (root == nullptr) {
		root = new RBNode(val);
		root->setColor(NodeColor::BLACK);  // Root is always black
	} else {
		insert(val, root);
	}
}

RBNode* RB::find(int val, RBNode* node) {
	RBNode* ans = nullptr;
	if (node == nullptr) return nullptr;

	if (node->getData() == val) {
		ans = node;
	} else {
		if (val < node->getData()) {
			ans = find(val, node->getLeft());
		} else {
			ans = find(val, node->getRight());
		}
	}
	return ans;
}

RBNode* RB::find(int val) {
	return find(val, root);
}

void RB::traverse(RBNode* node, int label) {
	if (node != nullptr) {
		for (int i = 0; i < label; i++) {
			std::cout << "*" << std::flush;
		}
		char T = node->isLeft() ? 'L' : 'R';
		std::cout << node->getData() << "  " << T << " Color: " << node->getColor() << std::endl;
		traverse(node->getLeft(), label + 1);
		traverse(node->getRight(), label + 1);
	}
}

void RB::traverse() {
	traverse(root, 1);
}

RB::~RB() {
	delete root;
}

}

