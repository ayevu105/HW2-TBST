/* @file TreadedBST.cpp
 * @brief The following code gives the implementations of the following functions that
 * were listed in the TBST assignment. 
 * @author Anthony Vu
 * @date 10/23/2022
 */

#include <iostream>
#include <stack>
#include "ThreadedBST.h"

using namespace std;

//output overloading
ostream &operator<<(ostream& out, const ThreadedBST& bst) {
  bst.preOrderTraversal(bst.root);
  return out << "\n";
}

//assignment overloading for copying
ThreadedBST& ThreadedBST::operator=(const ThreadedBST& bst) {
  if (this != &bst) {
    clear(root);
    copyTree(bst.root);
  }
  return *this;
}

//constructs a new tree node with a given int
Node::Node(int value) : value{value} {
  left = nullptr;
  right = nullptr;
  leftThread = false;
  rightThread = false;
}

//constructs a new tree with a given int
ThreadedBST::ThreadedBST(int n) {
  this->n = n;
  root = balanceTree(1, n);
  addRightThread();
  addLeftThread();
}

//constructs a new tree from another tree by copying its contents 
ThreadedBST::ThreadedBST(const ThreadedBST& other) {
  this->root = copyTree(other.root);
  this->n = other.n;
  addRightThread();
  addLeftThread();
}

//
ThreadedBST::~ThreadedBST() {
  clear(root);
}

/* copyTree copies a tree
 * @param node is the root node that copying begins at
 */
Node* ThreadedBST::copyTree(Node* node) {
  if (node != nullptr) {
    Node *newNode = new Node(node->value);
    if (!node->leftThread) {
      newNode->left = copyTree(node->left);
    }
    if (!node->rightThread) {
      newNode->right = copyTree(node->right);
    }
    return newNode;
  }
  return nullptr;
}

/* balanceTree creates a balanced tree 
 * @param start is the start range of ints where the balance tree starts from
 * @param end is the end range of ints that the balance tree ends at 
 */
Node* ThreadedBST::balanceTree(int start, int end) {
  if (end < start) {
    return nullptr;
  } else {
    int midpoint = (start + end) / 2;
    Node *root = new Node(midpoint);
    root->left = balanceTree(start, midpoint - 1);
    root->right = balanceTree(midpoint + 1, end);
    return root;
  }
}

/* getHeight returns the height of a TBST
 */
int ThreadedBST::getHeight() const {
  if (root == nullptr) {
    return 0;
  }
  else {
    return (getHeightHelper(root));
  }
}

/* getHeightHelper is the helper function the returns the height of a TBST
 * @param root is the starting node that traversing begins at
 */
int ThreadedBST::getHeightHelper(Node* root) const {
  int left_height;
  int right_height;

  if (root->leftThread) {
    left_height = 1 + getHeightHelper(root->left);
  }

  if(root->rightThread) {
    right_height = 1 + getHeightHelper(root->right);
  }
  return max(left_height, right_height);
}

/* getEntry returns a node if found in the TBST
 * @param target is the target int that is being searched for
 */
Node* ThreadedBST::getEntry(int target) const {
	return getEntryHelper(target, root);
}


/* getEntryHelper is the helper function that searches for a node with a specified value
 * @param n is the target int that is being searched for
 * @param node is the current node that we are traversing with
 */
Node* ThreadedBST::getEntryHelper(int n, Node* node) const {
	if (node != nullptr) {
		if (node->value == n) {
			return node;
		} else {
			if (n < node->value) {
				return getEntryHelper(n, node->left);
			} else {
				return getEntryHelper(n, node->right);
			}
		}
	} else {
		return nullptr;
	}
}

/* addRightThread adds the right threads to the TBST
 */
void ThreadedBST::addRightThread() {
  stack<Node*> stack;
  Node* curr = root;
  Node* prev = root;
  if (root != nullptr) {
    stack.push(curr);
  }
  while (!stack.empty()) {
    while (curr != nullptr) {
      prev = curr;
      stack.push(curr);
      curr = curr->left;
    }
    while (curr == nullptr || (curr->right == nullptr && !stack.empty())) {
      curr = stack.top();
      stack.pop();
    }
    if (!stack.empty() && curr->value > prev->value) {
      prev->right = curr;
      prev->rightThread = true;
    }
    curr = curr->right;
  }
}

/* addLeftThread adds the left threads to the TBST
 */
void ThreadedBST::addLeftThread() {
  stack<Node* > stack;
  Node* curr = root;
  Node* prev = root;
  if (root != nullptr) {
    stack.push(curr);
  }
  while (!stack.empty()) {
    while (curr != nullptr) {
      prev = curr;
      stack.push(curr);
      if (!curr->rightThread) {
        curr = curr->right;
      } else {
        curr = nullptr;
      }
    }
    while (curr == nullptr || (curr->left == nullptr && prev->value <= curr->value && !stack.empty())) {
      curr = stack.top();
      stack.pop();
    }
    if (curr->value < prev->value) {
      prev->left = curr;
      prev->leftThread = true;
    }
    if (prev->left == curr) {
      prev = curr;
    }
    curr = curr->left;
  }
}

/* getNumberOfNodes returns the number of nodes in the TBST
 * @param numberOfNodes is the number of nodes in the TBST
 */
int ThreadedBST::getNumberOfNodes(int numberOfNodes) { 
  return numberOfNodes;
}

/* isEmpty returns true or false depning on whether the TBST is empty or not
 */
bool ThreadedBST::isEmpty() const {
  if (this->root == nullptr) {
    return true;
  } else {
    return false;
  }
}

/* clear recursively goes through the TBST and clears each node
 * @param node is the starting node that clearing starts at
 */
void ThreadedBST::clear(Node* node) {
  if (node != nullptr) {
    if (!node->leftThread) {
      clear(node->left);
    }
    if (!node->rightThread) {
      clear(node->right);
    }
    delete node;
  }
}

/* preOrderTraversal gives a preorder traversal of the TBST
 * @param node is the starting node for preorder traversal
 */
void ThreadedBST::preOrderTraversal(Node* node) const {
  if (node == nullptr){
    return;
  }

  cout << node->value;
  cout << " ";
  if(!node->leftThread) {
    preOrderTraversal(node->left);
  }
  if(!node->rightThread) {
    preOrderTraversal(node->right);
  }
}

/* inOrderTraversal gives an inorder traversal of the TBST
 * @param node is the starting node for inorder traversal
 */
void ThreadedBST::inOrderTraversal(Node* node) const {
  if (node == nullptr){
    return;
  }

  if (!node->leftThread) {
    inOrderTraversal(node->left);
  }
  cout << node->value;
  cout << " ";
  if(!node->rightThread) {
    inOrderTraversal(node->right);
  }
}

/* postOrderTraversal gives a postorder traversal of the TBST
 * @param node is the starting node for the postorder traversal
 */
void ThreadedBST::postOrderTraversal(Node* node) const {
  if (node == nullptr){
    return;
  }

  if(!node->leftThread) {
    postOrderTraversal(node->left);
  }
  if(!node->rightThread) {
   postOrderTraversal(node->right);
  }
  cout << node->value;
  cout << " ";
}

/* remove removes a specific node from the TBST
 * @param target is the node that we are looking to remove
 */
bool ThreadedBST::remove(const int& target) {
  Node *curr = root;
  Node *prev = nullptr;
  while (curr != nullptr && ((!curr->leftThread && curr->left != nullptr) ||
        (!curr->rightThread && curr->right != nullptr)) &&
         curr->value != target) { 
    if (target < curr->value) {
      prev = curr;
      curr = curr->left;
    } else {
      prev = curr;
      curr = curr->right;
    }
  }

  if (curr == nullptr || curr->value != target) {
    return false;
  } else {
    bool result = removeHelper(curr, prev);
    return result;
  }
}

/* removeHelper is the helper function for removing a node from the TBST
 * @param curr is the pointer for the node to be removed
 * @param prev is the pointer of the nodes parent to be removed
 */
bool ThreadedBST::removeHelper(Node* curr, Node* prev) {
  if ((curr->leftThread || curr->left == nullptr) && (curr->rightThread || 
       curr->right == nullptr)) { 
    if (curr == prev->left) {
      prev->left = curr->left;
      if (prev->left != nullptr) {
        prev->leftThread = true;
      }
    } else {
      prev->right = curr->right;
      if (prev->right != nullptr) {
        prev->rightThread = true;
      }
    }
    delete curr;
    return true;
  } else if (!curr->leftThread && !curr->rightThread && curr->left != nullptr && curr->right != nullptr) { 
    Node *next = curr->right;
    Node *nextPrev = curr;
    while (!next->leftThread) { 
      nextPrev = next;
      next = next->left;
    }
    curr->value = next->value;
    return removeHelper(next, nextPrev);
  } else { 
    Node *next = nullptr;
    if (curr->leftThread || curr->right != nullptr) {
      next = curr->right;
    } else if (curr->rightThread || curr->left != nullptr) {
      next = curr->left;
    }
    if (prev == nullptr) { 
      root = next;
    } else if (curr == prev->left) {
      prev->left = next;
    } else {
      prev->right = next;
    }
    prev = curr->left; 
    if (!curr->leftThread) {
      while (prev != nullptr && !prev->rightThread) {
        prev = prev->right;
      }
    }
    next = curr->right;
    if (!curr->rightThread) {
      while (next != nullptr && !next->leftThread) {
        next = next->left;
      }
    }
    if (!curr->leftThread && prev != nullptr) {
      prev->right = next;
    } else if (!curr->rightThread && next != nullptr) {
      next->left = prev;
    }
    delete curr;
    return true;
  }
}

