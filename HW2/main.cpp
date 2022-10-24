#include "ThreadedBST.h"
#include "ThreadedBST.cpp"
#include <iostream>

using namespace std;

void test1() { // size 1
    int n = 4;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    // remove all evens from newTree
    for (int i = 2; i < n + 1; i += 2) {
        newTree.remove(i);
    }
    //output
    cout << "Original Tree: " << origTree << endl;
    cout << "New Tree: " << newTree << endl;
}

void test2() { // size 1
    int n = 4;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    // remove all evens from newTre
    
    Node* node = origTree.getEntry(2);
    cout << node->data << endl;
}

void test3() { // size 1
    int n = 4;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    int count = newTree.getNumberOfNodes(n);
    cout << count << endl;
}

void test4() { // size 1
    int n = 10;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    int height = newTree.getHeight();
    cout << height << endl;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}