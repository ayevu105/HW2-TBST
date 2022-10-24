/* @file main.cpp
 * @brief The following code fufills the requirments of the TBST project
 * where the main driver uses multiple int values which represent the number of nodes
 * that will be in the tree. The program then will print out a list of nodes using a preorder
 * traversal.
 * @author Anthony Vu
 * @date 10/23/2022
 */

#include "ThreadedBST.h"
#include <iostream>

void test1() { 
    cout << "Testing = operator: " << endl;
    int n = 4;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    cout << "Original Tree: " << origTree;
    cout << "Copied Tree: " << newTree;
}

void test2() { // size 1
    cout << "Testing getEntry() implementation:" << endl;
    int n = 10;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    Node* node = newTree.getEntry(2);
    cout << "Copied Tree: " << newTree;
    cout << node->value << " exists in the TBST" << endl;
}

void test3() { // size 1
    cout << "Testing getNumberOfNodes() implementation:" << endl;
    int n = 17;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    int count = newTree.getNumberOfNodes(n);
    cout << "Copied Tree: " << newTree;
    cout << "There are " << count << " nodes in this TBST" << endl;
}

void test4() { // size 1
    cout << "Testing getHeight() implementation:" << endl;
    int n = 100;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    int height = newTree.getHeight();
    cout << newTree;
    cout << "Height of TBST is: " << height << endl;
}

void test5() { // size 1
    cout << "Testing remove() implementation:" << endl;
    int n = 11;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    for (int i = 2; i < n + 1; i += 2) {
        newTree.remove(i);
    }
    cout << "Original Tree: " << origTree;
    cout << "Copied Tree with even numbers removed: " << newTree;
}

int main() {
    test1();
    cout << endl;
    test2();
    cout << endl;
    test3();
    cout << endl;
    test4();
    cout << endl;
    test5();
    return 0;
}