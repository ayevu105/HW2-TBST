

#include "threadedBST.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// output overload
ostream& operator<<(ostream& out, const ThreadedBST& bst) {


}

// assignment overload for copying
ThreadedBST& ThreadedBST::operator=(const ThreadedBST& bst) {

}

// constructor
// n equals the total number of nodes in the tree
ThreadedBST::ThreadedBST(int n) : totalNodes{ n } {
	// vector for adding inputs
	vector<int> nums;
	for (int i = 1; i <= n; i++) {
		nums.push_back(i);
	}
	// assign headptr and start recursive call to build tree, then thread it
	headPtr = buildSubTree(nums, 0, nums.size() - 1);
	threadTree(headPtr);
}

// helper function to thread a tree
void ThreadedBST::threadTree(Node* headPtr) {
	// find left most child of tree 
	Node* currentNode = headPtr;
	while (currentNode->leftPtr != nullptr) {
		currentNode = currentNode->leftPtr;
	}
	if (currentNode->rightPtr != nullptr) {
		currentNode = currentNode->rightPtr;
	}
	// traverse tree and create threads when necessary
	while (currentNode->value < totalNodes) {
		if (currentNode->rightPtr == nullptr) { // thread needed
			// create thread and follow it
			currentNode->rightPtr = getEntry(currentNode->value + 1);
			currentNode->isThread = true;
			currentNode = currentNode->rightPtr;

			// new currentNode will always have a right child, follow again
			currentNode = currentNode->rightPtr;
		}
		else if (currentNode->leftPtr != nullptr) {
			// explore left child/subtree
			currentNode = currentNode->leftPtr;
		}
		else {
			// explore right child/subtree
			currentNode = currentNode->rightPtr;
		}
	}
}

/* Helper function that allocates a
new node */
Node* newNode(int value)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return (node);
}

// helper function to build subtrees recursively
// returns a Node* to make recursion possible
Node* ThreadedBST::buildSubTree(const vector<int>& nums,
	int lowerIndex, int upperIndex) {
	Node *root = nullptr;
	// Base case for recursion
	if (lowerIndex < upperIndex)
	{
		root = newNode(nums[i]);
		
		// insert left child
		root->left = insertLevelOrder(nums,
				2 * lowerIndex + 1, upperIndex);

		// insert right child
		root->right = insertLevelOrder(nums,
				2 * lowerIndex + 2, upperIndex);
	}
	return root;

}

// copy constructor
ThreadedBST::ThreadedBST(const ThreadedBST& tbst) {
	
}

// destructor
ThreadedBST::~ThreadedBST() {
	clear(root);
}

// clear helper function to recursively delete TBST
void ThreadedBST::clear(Node* node) {
	if (node != nullptr) {
		clear(node->left);
		clear(node->right);
		delete node;
		return;
	} else {
		return;
	}

}

// searches Tree for a node with specified value
// returns Node if found, nullptr if not found
Node* ThreadedBST::getEntry(int n) const {
	return getEntryHelper(n, root);
}

Node* ThreadedBST::getEntryHelper(int n, node* ptr) const {
	if (ptr != nullptr) {
		if (ptr->value == n) {
			return ptr;
		} else {
			if (n < ptr->value) {
				return getEntryHelper(n, ptr->left);
			} else {
				return getEntryHelper(n, ptr->right);
			}
		}
	} else {
		return nullptr;
	}

}


// returns true if empty, false if not
bool ThreadedBST::isEmpty() const {
	return (root == nullptr);
}

// iterator to do inorder traversal of the tree
vector<int> ThreadedBST::preorderTraversal() const {
	if (currentNode->right!= nullptr) {

	}

}

//removes a node
bool ThreadedBST::remove(int value) {
	

}

