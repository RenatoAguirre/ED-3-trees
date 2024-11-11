/*
 * abb.cpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 */

#include "trees/abb.hpp"
#include <iostream>

namespace trees {

ABB::ABB():root(nullptr) {
	// TODO Auto-generated constructor stub
}

void ABB::insert_rec(int val, ABBNode* node){
	if (val < node->getData()){
		//LEFT
		if (node->getLeft() == nullptr){
			node->setLeft(new ABBNode(val));
			//std::cout<<val << " inserted on left" << std::endl;
		}
		else{
			insert_rec(val, node->getLeft());
		}
	}
	else{
		//RIGHT
		if (node->getRight() == nullptr){
			node->setRight(new ABBNode(val));
			//std::cout<<val << " inserted on right" << std::endl;
		}
		else{
			insert_rec(val, node->getRight());
		}
	}
}

void ABB::insert(int val) {
    if (root == nullptr) {
        root = new ABBNode(val);
    } else {
        ABBNode* current = root;
        ABBNode* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (val < current->getData()) {
                current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }

        if (val < parent->getData()) {
            parent->setLeft(new ABBNode(val));
        } else {
            parent->setRight(new ABBNode(val));
        }
    }

    // Mensaje de depuración
    static int count = 0;
    if (++count % 10000 == 0) {
        std::cout << "Inserted " << count << " elements." << std::endl;
    }
}


ABBNode* ABB::find_rec(int val, ABBNode* node){
    if (node == nullptr) {
        return nullptr;  
    }

    if (node->getData() == val){
        return node;
    }
    else if (val < node->getData()){
        return find_rec(val, node->getLeft());
    }
    else{
        return find_rec(val, node->getRight());
    }
}

ABBNode* ABB::find(int val) {
    ABBNode* current = root;

    while (current != nullptr) {
        if (current->getData() == val) {
            return current;  // Value found, return the node
        } else if (val < current->getData()) {
            current = current->getLeft();  // Move to the left child
        } else {
            current = current->getRight();  // Move to the right child
        }
    }
    
    return nullptr;  // Value not found in the tree
}

void ABB::traverse_rec(ABBNode* node, int level){
	if (node != nullptr){
		std::cout << std::string(level*2, '-');
		std::cout << node->getData() << " | s = " << node->getSize() << std::endl;
		traverse_rec(node->getLeft(), level + 1);
		traverse_rec(node->getRight(), level + 1);
	}
}

void ABB::traverse(){
	traverse_rec(root, 1);
}

/*extras*/
void ABB::showASC_rec(ABBNode* node){
	if (node != nullptr){
		showASC_rec(node->getLeft());
		std::cout << node->getData() << " " << std::flush;
		showASC_rec(node->getRight());
	}
}
void ABB::showASC(){
	showASC_rec(root);
	std::cout << std::endl;
}

void ABB::updateSize_rec(ABBNode* node){
	if (node != nullptr){
		updateSize_rec(node->getLeft());
		updateSize_rec(node->getRight());
		int lSize = 0;
		int rSize = 0;
		if (node->getLeft() != nullptr){
			lSize = node->getLeft()->getSize();
		}
		if (node->getRight() != nullptr){
			rSize = node->getRight()->getSize();
		}
		node->setSize(lSize + rSize + 1);
	}
}

void ABB::updateSize(){
	updateSize_rec(root);
}


ABBNode* ABB::k_element_rec(int k, ABBNode* node){
	ABBNode* ans = nullptr;
	if (node != nullptr){
		int lSize = 0;
		int posNode = 0;
		if (node->getLeft() != nullptr){
			lSize = node->getLeft()->getSize();
		}
		posNode = lSize + 1;

		if (k == posNode){
			ans = node;
		}
		else if  (k > posNode ){
			ans = k_element_rec( k - posNode, node->getRight());
		}
		else{
			ans = k_element_rec( k, node->getLeft());
		}
	}
	return ans;

}

ABBNode* ABB::k_element(int k){
	return k_element_rec(k, root);
}

ABB::~ABB() {
	delete root;
}

} /* namespace trees */
