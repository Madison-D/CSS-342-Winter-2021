/*
Assignment 5
Created by: Bradley Knorr and Madison Dienhart
Date: 3/14/2021
This is the main cpp
This file contains the 'main' function.
the functions in this file work together with the
binarytreeinterface.h file and cpp file to create
a threaded binary search tree to store integers
*/

#include <iostream>
#include "binarytreeinterface.h"

using namespace std;

void test1() {
    BinaryTreeInterface t1;

    // Creation of the Threaded 
    // Binary search tree
    cout << "isEmpty: " << (t1.isEmpty() == true ? "True" : "False") << endl;
    t1.add(10);
    cout << "isEmpty: " << (t1.isEmpty() == true ? "True" : "False") << endl;
    t1.printInOrderTraversal();
    t1.add(5);
    t1.printInOrderTraversal();
    t1.add(15);
    t1.printInOrderTraversal();
    t1.add(7);
    t1.printInOrderTraversal();
    t1.add(6);
    t1.printInOrderTraversal();
    t1.add(9);
    t1.printInOrderTraversal();
    t1.add(8);
    t1.printInOrderTraversal();
    t1.add(3);
    t1.printInOrderTraversal();
    t1.add(1);
    t1.printInOrderTraversal();
    t1.add(2);
    t1.printInOrderTraversal();
    t1.add(4);
    t1.printInOrderTraversal();
    t1.add(17);
    t1.printInOrderTraversal();
    t1.add(16);
    t1.printInOrderTraversal();
    t1.add(19);
    t1.printInOrderTraversal();
    t1.add(18);
    t1.printInOrderTraversal();
    t1.add(13);
    t1.printInOrderTraversal();
    t1.add(11);
    t1.printInOrderTraversal();
    t1.add(12);
    t1.printInOrderTraversal();
    t1.add(14);
    t1.printInOrderTraversal();
    int height = t1.getHeight();
    cout << "Height: " << height << endl;

    // remove leaf node
    t1.remove(18);
    t1.printInOrderTraversal();
    // remove node with no left node, but has a right node
    t1.remove(11);
    t1.printInOrderTraversal();
    // remove root
    t1.remove(10);
    t1.printInOrderTraversal();
    // remove non-root with deep subtree
    t1.remove(5);
    t1.printInOrderTraversal();

    Node* entry = t1.getEntry(2);
    cout << "Entry: " << entry->data << endl;
    cout << "Contains 2? " << (t1.contains(2) == true ? "True" : "False") << endl;
}


void test2() {

  BinaryTreeInterface t2(19);
    t2.printInOrderTraversal();

    BinaryTreeInterface t1 = t2;
    t1.removeEvens();
    t1.printInOrderTraversal();
}

void test3(){
    BinaryTreeInterface t3;
    t3.add(5);
    t3.add(7);
    t3.add(6);
    t3.remove(5);
}

int main()
{
    test1();
    test2();
    test3();
}
