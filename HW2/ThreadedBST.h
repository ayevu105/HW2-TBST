// Kristen Maggs and Amanda Todakonzie
// This is Tree.h. It can dynamically create and destroy a balanced
// threaded binary search tree of ints, print the tree, copy the tree into
// another tree, remove all evens as well as individual nodes, and clear it.

#ifndef THREADEDBST_H
#define THREADEDBST_H

#include <iostream>
#include <stack>

using namespace std;

class ThreadedBST;

class Node {

  friend class ThreadedBST;

  friend ostream &operator<<(ostream &out, const ThreadedBST &bst);

private:

  explicit Node(int data);

  int data;

  Node* left = nullptr;

  Node* right = nullptr;

  bool leftThread = false;

  bool rightThread = false;
};

class ThreadedBST {

  friend ostream &operator<<(ostream &out, const ThreadedBST &bst);

public:

  explicit ThreadedBST(int n);

  virtual ~ThreadedBST();

  ThreadedBST(const ThreadedBST& other);

  bool remove(const int &target);

  void clear(Node* node);

  Node* getEntry(int n) const;

  int getHeight() const;

  int getNumberOfNodes() const;

private:

  Node* root;

  int n;

  int height{0};

  int numberOfNodes;

  void preOrderTraversal(Node* node) const;

  void inOrderTraversal(Node* node) const;

  void postOrderTraversal(Node* node) const;

  Node* balancedTree(int min, int max);

  void addRightThreads();

  void addLeftThreads();

  Node* copyTree(Node* node);

  bool removeHelper(Node* curr, Node* prev);

  Node* getEntryHelper(int n, Node* ptr) const;

  bool isEmpty() const;

};

#endif