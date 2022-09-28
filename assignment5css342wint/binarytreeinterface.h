/*Assignment 5
Created by: Bradley Knorr and Madison Dienhart
Date: 3/14/2021
This is the header file, binarytreeinterface.h,
the functions in this file work together with the
binarytreeinterface.cpp file and main file to create
a threaded binary search tree to store integers
*/
#ifndef BINARY_TREE_INTERFACE_
#define BINARY_TREE_INTERFACE_
#include <iostream>
#include <vector>
using namespace std;

//Node Class
class Node {

public:
    //data variable
    int data;

    //right and left nodes
    Node* right;
    Node* left;

    //right thread
    bool hasRightChild;

    //left thread
    bool hasLeftChild;

    friend class BinaryTreeInterface;

    //Node class constructor
    Node(int data);
};

//Tree Class
class BinaryTreeInterface
{

private:

    //root node
    Node* root = nullptr;

public:

    //constructor
    BinaryTreeInterface();

    BinaryTreeInterface(int n);

    //copy constructor
    BinaryTreeInterface(BinaryTreeInterface& source);

    //destructor
    ~BinaryTreeInterface();

    //creates vector
    vector<int> convertToVector();

    //creates vector - helper
    vector<int> convertToVector(vector<int> vector, Node* currNode);

    //adds vector by midpoint
    bool addByMidpoint(vector<int> vector, int firstIndex, int lastIndex);

    //inserts integers
    bool add(const int newData);

    //adds to vector
    bool add(vector<int> vector);

    //adds data at the right level
    bool add(Node* currNode, const int newData, Node* nextLowest, Node* nextHighest);

    //adds threading to the tree
    void addThreads(Node* addedNode, Node* leftThread, Node* rightThread);

    //checks if tree is empty
    bool isEmpty() const;

    //checks the height of the tree
    int getHeight() const;

    //checks the height of the tree - helper
    int getHeight(Node* currNode) const;

    //removes  target
    bool remove(const int target);

    //removes functions helper
    bool remove(Node* parentNode, Node* currNode, const int target);

    //prepares removal
    void prepareRemoval(Node* parentNode, Node* currNode);

    //clears all data
    void clear(Node* currNode);

    //searches for a target
    Node* getEntry(const int target) const;

    // searches for a target - helper
    Node* getEntry(Node* currNode, const int target) const;

    // checks to see if the tree contains target data
    bool contains(const int target);

    // prints inorder traversal of tree
    void printInOrderTraversal();

    // finds next node when traversal
    Node* inorderFindNextNode(Node* currNode);

    // finds evens for removal
    bool removeEvens();

    // gets root
    Node* getRoot();

};
#endif