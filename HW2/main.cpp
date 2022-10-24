#include "ThreadedBST.h"
#include "ThreadedBST.cpp"
#include <iostream>

using namespace std;

void test1() { // size 1
    int n = 10;
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
    int n = 5;
    ThreadedBST origTree(n); // creating a tree
    ThreadedBST newTree = origTree; // copying original tree
    // remove all evens from newTree
    int totalNodes = newTree.getNumberOfNodes(newTree.getEntry(1));
    //output
    cout << totalNodes << endl;
}

int main() {
    test2();
    return 0;
}