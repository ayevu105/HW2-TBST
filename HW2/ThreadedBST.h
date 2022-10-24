/* @file ThreadedBST.h
 * @brief The following code gives the declarations of the following functions that
 * were listed in the TBST assignment. 
 * @author Anthony Vu
 * @date 10/23/2022
 */

#ifndef THREADEDBST_H
#define THREADEDBST_H

#include <iostream>
#include <stack>

using namespace std;

class Node {

  friend class ThreadedBST;

public:

  int value;

  Node* left;

  Node* right;

  bool leftThread;

  bool rightThread;

  explicit Node(int value);
};

class ThreadedBST {

  friend ostream &operator<<(ostream& out, const ThreadedBST& bst);

public:

  ThreadedBST& operator=(const ThreadedBST& bst);

  ThreadedBST(int n);

  ThreadedBST(const ThreadedBST& other);

  ~ThreadedBST();

  Node* copyTree(Node* node);

  Node* balanceTree(int min, int max);

  int getHeight() const;
  
  int getHeightHelper(Node* node) const;

  Node* getEntry(int n) const;

  Node* getEntryHelper(int n, Node* ptr) const;

  int getNumberOfNodes(int numberOfNodes);

  void clear(Node* node);

  bool remove(const int &target);

  bool removeHelper(Node* curr, Node* prev);

private:

  Node* root = nullptr;

  int n;

  int numberOfNodes;

  bool isEmpty() const; 

  void addRightThread();

  void addLeftThread();

  void preOrderTraversal(Node* node) const;

  void inOrderTraversal(Node* node) const;

  void postOrderTraversal(Node* node) const;
};

#endif