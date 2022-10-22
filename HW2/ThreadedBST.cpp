#include <iostream>
#include <stack>

#include "ThreadedBST.h"

using namespace std;

ostream &operator<<(ostream &out, const ThreadedBST &bst) {
bst.preOrderTraversal(bst.root);
return out << "\n";
}

void ThreadedBST::preOrderTraversal(Node* node) const {
  if(node == nullptr){
    return;
  }
  cout << node->data;
  cout << " ";
    if(!node->leftThread) {
      preOrderTraversal(node->left);
    }
    if(!node->rightThread) {
      preOrderTraversal(node->right);
    }
  }

void ThreadedBST::inOrderTraversal(Node* node) const {
  if(node == nullptr){
    return;
  }

  if(!node->leftThread) {
    inOrderTraversal(node->left);
  }
  cout << node->data;
  cout << " ";
  if(!node->rightThread) {
    inOrderTraversal(node->right);
  }
}

void ThreadedBST::postOrderTraversal(Node* node) const {
if(node == nullptr){
  return;
}
  if(!node->leftThread) {
    postOrderTraversal(node->left);
  }
  if(!node->rightThread) {
   postOrderTraversal(node->right);
  }
  cout << node->data;
  cout << " ";
}

//Constructor
Node::Node(int data) : data{data} {
  left = nullptr;
  right = nullptr;
  leftThread = false;
  rightThread = false;
}

//Constructor w parameter
ThreadedBST::ThreadedBST(int n) {
  this->n = n;
  root = balancedTree(1, n);
  addRightThreads();
  addLeftThreads();
}

//copy constructor
ThreadedBST::ThreadedBST(const ThreadedBST& other) {
  this->root = copyTree(other.root);
  this->n = other.n;
  addRightThreads();
  addLeftThreads();
}

Node *ThreadedBST::copyTree(Node *node) {
  if (node != nullptr) {
    Node *newNode = new Node(node->data);
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

Node *ThreadedBST::balancedTree(int start, int end) {
  if (end < start) {
    return nullptr;
  } else {
    int midpoint = (start + end) / 2;
    Node *root = new Node(midpoint);
    root->left = balancedTree(start, midpoint - 1);
    root->right = balancedTree(midpoint + 1, end);
    return root;
  }
}

ThreadedBST::~ThreadedBST() {
  clear(root);
}

int ThreadedBST::getHeight() const {
  return this->height;
}

bool ThreadedBST::isEmpty() const {
  if (this->root == nullptr) {
    return true;
  } else {
    return false;
  }
}

int ThreadedBST::getNumberOfNodes() const { 
  return this->numberOfNodes;
}

Node* ThreadedBST::getEntry(int n) const {
	return getEntryHelper(n, root);
}

Node* ThreadedBST::getEntryHelper(int n, Node* ptr) const {
	if (ptr != nullptr) {
		if (ptr->data == n) {
			return ptr;
		} else {
			if (n < ptr->data) {
				return getEntryHelper(n, ptr->left);
			} else {
				return getEntryHelper(n, ptr->right);
			}
		}
	} else {
		return nullptr;
	}
}

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

void ThreadedBST::addRightThreads() {
  stack<Node*> nodeStack;
  Node* curr = root;
  Node* prev = root;
  if (root != nullptr) {
    nodeStack.push(curr);
  }
  while (!nodeStack.empty()) {
    while (curr != nullptr) {
      prev = curr;
      nodeStack.push(curr);
      curr = curr->left;
    }
    while (curr == nullptr || (curr->right == nullptr && !nodeStack.empty())) {
      curr = nodeStack.top();
      nodeStack.pop();
    }
    if (!nodeStack.empty() && curr->data > prev->data) {
      prev->right = curr;
      prev->rightThread = true;
    }
    curr = curr->right;
  }
}

void ThreadedBST::addLeftThreads() {
  stack<Node *> nodeStack;
  Node *curr = root;
  Node *prev = root;
  if (root != nullptr) {
    nodeStack.push(curr);
  }
  while (!nodeStack.empty()) {
    while (curr != nullptr) {
      prev = curr;
      nodeStack.push(curr);
      if (!curr->rightThread) {
        curr = curr->right;
      } else {
        curr = nullptr;
      }
    }
    while (curr == nullptr ||
           (curr->left == nullptr && prev->data <= curr->data &&
            !nodeStack.empty())) {
      curr = nodeStack.top();
      nodeStack.pop();
    }
    if (curr->data < prev->data) {
      prev->left = curr;
      prev->leftThread = true;
    }
    if (prev->left == curr) {
      prev = curr;
    }
    curr = curr->left;
  }
}

bool ThreadedBST::remove(const int &target) {
  Node *curr = root;
  Node *prev = nullptr;
  while (curr != nullptr &&
         ((!curr->leftThread && curr->left != nullptr) ||
          (!curr->rightThread && curr->right != nullptr)) &&
         curr->data != target) { 
    if (target < curr->data) {
      prev = curr;
      curr = curr->left;
    } else {
      prev = curr;
      curr = curr->right;
    }
  }
  if (curr == nullptr || curr->data != target) {
    return false;
  } else {
    bool result = removeHelper(curr, prev);
    return result;
  }
}

bool ThreadedBST::removeHelper(Node *curr, Node *prev) {
  if ((curr->leftThread || curr->left == nullptr) &&
      (curr->rightThread || curr->right == nullptr)) { 
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
  } else if (!curr->leftThread && !curr->rightThread && curr->left != nullptr &&
             curr->right != nullptr) { 
    Node *next = curr->right;
    Node *nextPrev = curr;
    while (!next->leftThread) { 
      nextPrev = next;
      next = next->left;
    }
    curr->data = next->data;
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


