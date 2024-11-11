#ifndef RB_HPP_
#define RB_HPP_

#include "trees/rbNode.hpp"

namespace trees {

enum RotationType {
	case_1 = 10, // Left-Left case
	case_2 = 20, // Right-Right case
	case_3 = 30, // Left-Right case
	case_4 = 40  // Right-Left case
	// You can add more cases if necessary
};

class RB {
private:
	RBNode* root;

	// Private methods for balancing and rotations
	void balance(RBNode* node);  // Balancing the tree
	void rotateLeft(RBNode* node);  // Left rotation
	void rotateRight(RBNode* node);  // Right rotation
	RotationType getRotationType(RBNode* node);  // Determine rotation type

public:
	RB();
	void insert(int val, RBNode* node);  // Insert a value
	void insert(int val);  // Insert a value with no node reference (starting at root)
	RBNode* find(int val, RBNode* node);  // Find a value starting from a node
	RBNode* find(int val);  // Find a value starting from root
	void traverse(RBNode* node, int level);  // Traverse and print the tree structure
	void traverse();  // Traverse from root
	virtual ~RB();
};

}  // namespace trees

#endif  // RB_HPP_
