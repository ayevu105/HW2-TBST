#include <cassert>
#include <iostream>
#include <stack>

#include "ThreadedBST.h"

using namespace std;

ostream &operator<<(ostream &out, const ThreadedBST &bst) {
  Node *prev = bst.root;
  Node *curr = bst.root;
  while (curr != nullptr) {
    while (curr->left != nullptr && !curr->leftThread) {
      curr = curr->left;
      prev = curr;
    }
    while (
        curr != nullptr &&
        (curr->rightThread || curr->left == nullptr ||
         curr->left->data <= prev->data)) {
      prev = curr;
      curr = curr->right;
      out << prev->data << " ";
    }
  }
  return out;
}

Node::Node(int data) : data{data} {
  this->left = nullptr;
  this->right = nullptr;
  this->leftThread = false;
  this->rightThread = false;
}

ThreadedBST::ThreadedBST(int n) {
  assert(n > 0);
  this->n = n;
  root = balancedTree(1, n);
  addRightThreads();
  addLeftThreads();
}

ThreadedBST::ThreadedBST(const ThreadedBST& other) {
  this->root = copyTree(other.root);
  this->n = other.n;
  addRightThreads();
  addLeftThreads();
}

ThreadedBST::~ThreadedBST() {
  clear(root);
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

Node *ThreadedBST::balancedTree(int min, int max) {
  if (min > max) {
    return nullptr;
  } else {
    int midpoint = (min + max) / 2;
    Node *node = new Node(midpoint);
    node->left = balancedTree(min, midpoint - 1);
    node->right = balancedTree(midpoint + 1, max);
    return node;
  }
}

void ThreadedBST::addRightThreads() {
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

vector<int> ThreadedBST::preorderTraversal() const {
	if (currentNode->right!= nullptr) {

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


