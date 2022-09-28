/*
Assignment 5
Created by: Bradley Knorr and Madison Dienhart
Date: 3/14/2021
This is the binarytreeinterface cpp
the functions in this file work together with the
binarytreeinterface.h file and main file to create
a threaded binary search tree to store integers
*/
#include "binarytreeinterface.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

/* Summary: Constructor for the node class
* Pre-condition: unintialized: int data, right, left
* hasRightChild, hasLeftChild
* Post condition:initialized: data, right, left
* hasRightChild, hasLeftChild
*/
Node::Node(int data)
{
	this->data = data;
	right = nullptr;
	left = nullptr;

	//right thread
	hasRightChild = false;
	//left thread
	hasLeftChild = false;
}

/* Summary: Constructor for an empty TBST
* Pre-condition: no tree
* Post condition: initlized tree
*/
BinaryTreeInterface::BinaryTreeInterface() {}

/* Summary: Constructor for an empty TBST
* Pre-condition: no tree
* Post condition: initlized tree
*/
BinaryTreeInterface::BinaryTreeInterface(int n)
{
	vector<int> vector;

	for (int i = 1; i <= n; i++) {
		vector.push_back(i);
	}

	add(vector);
}

/* Summary: destructor
* Pre-condition: n/a
* Post condition: all of the memory of the tree is cleared
*/
BinaryTreeInterface::~BinaryTreeInterface()
{
	clear(root);
}

/* Summary: BinaryTreeInterface copy constructor
* Pre-condition: A tree to copy to
* Post condition: created a copy of the BST
*/
BinaryTreeInterface::BinaryTreeInterface(BinaryTreeInterface& source)
{
	add(source.convertToVector());
}

/* Summary: converts tree to vector
* Pre-condition:
* Post condition: returns a vector of the pre-order traversal of the BST
*/
vector<int> BinaryTreeInterface::convertToVector() {
	vector<int> emptyVector;
	return convertToVector(emptyVector, root);
}

/* Summary: converts tree to vector
* Pre-condition: Takes in currNode, converts nodes to vectors
* Post condition: returns a vector of the pre-order traversal of the BST
*/
vector<int> BinaryTreeInterface::convertToVector(vector<int> vector,
	Node* currNode)
{
	// first recur on left child
	if (currNode->hasLeftChild)
		vector = convertToVector(vector, currNode->left);

	// then add the data of node to the vector
	vector.push_back(currNode->data);


	// now recur on right child
	if (currNode->hasRightChild)
		vector = convertToVector(vector, currNode->right);

	return vector;
}

/* Summary: checks to see if tree is empty
* Pre-condition: n/a
* Post condition: returns if tree is empty
*/
bool BinaryTreeInterface::isEmpty() const
{
	return (root == nullptr);
}

/* Summary: gets the height of the tree
* Pre-condition: n/a
* Post condition: returns getHeight passed through
* helper function
*/
int BinaryTreeInterface::getHeight() const
{
	if (root == nullptr)
		return 0;
	else {
		return (getHeight(root));
	}
}

/* Summary: getHeight helper
* Pre-condition: takes in currNode
* Post condition: returns the height
*/
int BinaryTreeInterface::getHeight(Node* currNode) const
{
	int leftHeight = 0;
	int rightHeight = 0;

	if (currNode->hasLeftChild)
		leftHeight = 1 + getHeight(currNode->left);

	if (currNode->hasRightChild)
		rightHeight = 1 + getHeight(currNode->right);

	return max(leftHeight, rightHeight);
}

/* Summary: adds through vector
* Pre-condition: receives vector of all nodes to add
* Post condition: returns add by midpoint
*/
bool BinaryTreeInterface::add(vector<int> vector) {
	bool isInOrder = true;
	int previousNumber = 0;

	// see if vector is in order
	for (int data : vector) {
		if (previousNumber < data) {
			previousNumber = data;
		}
		else {
			isInOrder = false;
			break;
		}
	}

	// if not in order, assume it is in pre-order and add all nodes
	// see if vector is in order
	if (!isInOrder) {
		bool addedAll = true;

		for (int data : vector) {
			if (!add(data))
				addedAll = false;
		}

		return addedAll;
	}

	// if it is in order, then find each midpoint and add
	return addByMidpoint(vector, 0, vector.size() - 1);
}

/* Summary: finds the midpoint of the first and last index passed in and
*	adds it to the tree
* Pre-condition: in-order vector of all nodes being added, first and last
*	 to find midpoint of, node that was just added
* Post condition: creates a balanced BST from an in-order vector
*/
bool BinaryTreeInterface::addByMidpoint(vector<int> vector, int firstIndex,
	int lastIndex)
{
	bool added = true;

	if (firstIndex > lastIndex)
		return true;

	int intGetMidPointIndex = floor((firstIndex + lastIndex) / 2);

	added = add(vector[intGetMidPointIndex]);

	Node* addedNode = getEntry(vector[intGetMidPointIndex]);

	if (root == nullptr)
		root = addedNode;

	if (!addByMidpoint(vector, firstIndex, intGetMidPointIndex - 1))
		added = false;

	if (!addByMidpoint(vector, intGetMidPointIndex + 1, lastIndex))
		added = false;

	return added;
}

/* Summary: Add a node with a specified value to the tree
* Pre-condition: an integer value
* Post condition: adds node to tree, returns true if successful
* add function
*/
bool BinaryTreeInterface::add(const int newData)
{
	if (root == nullptr)
	{
		root = new Node(newData);
		root->hasLeftChild = false;
		root->hasRightChild = false;

		return true;
	}

	return add(root, newData, nullptr, nullptr);
}

/* Summary: The add function that also helps to thread
* Pre-condition: node not nullptr, value being added, best candidate
*	for the left and right threads found as you went down the tree
* Post condition: node was added to the tree
*/
bool BinaryTreeInterface::add(Node* currNode, const int newData,
	Node* leftThread, Node* rightThread)
{
	if (currNode->data < newData) {// less than the newNode lowest
		if (leftThread == nullptr
			|| currNode->data > leftThread->data) // more than the next lowest
			leftThread = currNode;
	}

	else if (currNode->data > newData) {
		if (rightThread == nullptr
			|| currNode->data < rightThread->data)
			rightThread = currNode;
	}

	// should I go right?
	if (currNode->data < newData) {
		// Yes I should go right

		// Can I go right?
		if (currNode->hasRightChild) {
			return add(currNode->right, newData, leftThread, rightThread);
		}

		Node* newNode = new Node(newData);

		currNode->right = newNode;
		currNode->hasRightChild = true;

		addThreads(newNode, leftThread, rightThread);

		return true;
	}
	// I can't go right, should I go left?
	else if (currNode->data > newData) {
		if (currNode->hasLeftChild) {
			return add(currNode->left, newData, leftThread, rightThread);
		}

		Node* newNode = new Node(newData);

		currNode->left = newNode;
		currNode->hasLeftChild = true;

		addThreads(newNode, leftThread, rightThread);

		return true;
	}

	return false;
}

/* Summary: Adds threads to the node being added
* Pre-condition: the node you're adding, and the correct left and right
	threads
* Post condition: the added node will have the threads attached
*/
void BinaryTreeInterface::addThreads(Node* addedNode, Node* leftThread,
	Node* rightThread)
{
	addedNode->left = leftThread;
	addedNode->right = rightThread;
	addedNode->hasLeftChild = false;
	addedNode->hasRightChild = false;
}

/* Summary: removes the target value from the tree
* Pre-condition: target to be passed through secondary remove
* function
* Post condition: removes node after pass through remove function
*/
bool BinaryTreeInterface::remove(const int target)
{
	if (root == nullptr)
		return false;

	if (root->data == target) {
		if (!root->hasLeftChild && !root->hasRightChild) {
			delete root;
			root = nullptr;
			return true;
		}

		Node* saveRoot = root;
		prepareRemoval(root, root);
		delete saveRoot;

		return true;
	}

	if (target < root->data)
		return remove(root, root->left, target);

	return remove(root, root->right, target);
}

/* Summary: removes the target value from the tree
* Pre-condition: receives parentnode, currnode, and target
* Post condition: deletes the currnode
*/
bool BinaryTreeInterface::remove(Node* parentNode, Node* currNode,
	const int target)
{
	// if bst is empty, then the item is not found
	if (currNode == nullptr) {
		//the item is not found
		return false;
	}
	// if the target is equal to data in tree, item is found
	else if (target == currNode->data) {
		prepareRemoval(parentNode, currNode);
		delete currNode;
		return true;
	}
	// checks left / right continues to search through, contains
	else if (target < currNode->data) {
		return remove(currNode, currNode->left, target);
	}
	else {
		return remove(currNode, currNode->right, target);
	}
}

/* Summary: Sets up the rest of the tree to allow for safe removal
* Pre-condition: parent of node being removed, and node being removed
* Post condition: returns node in the correct new placement for removal
*/
void BinaryTreeInterface::prepareRemoval(Node* parentOfRemoveNode,
	Node* removeNode)
{
	Node* parentNodeOfReplacement;
	Node* replacementNode;

	bool isRoot = parentOfRemoveNode == removeNode;
	bool isLeftNode = parentOfRemoveNode->left == removeNode;
	bool isLeaf = ((!removeNode->hasLeftChild)
		&& (!removeNode->hasRightChild));

	// if the node being removed is a leaf node
	// does not need a node to replace it
	if (isLeaf) {
		if (isLeftNode) {
			parentOfRemoveNode->left = removeNode->left;
			parentOfRemoveNode->hasLeftChild = false;
			return;
		}

		parentOfRemoveNode->right = removeNode->right;
		parentOfRemoveNode->hasRightChild = false;

		return;
	}

	// if it does need a node to replace it:

	// if left node doesn't exist
	if (!removeNode->hasLeftChild)
	{
		if (isRoot)
			root = removeNode->right;
		else if (isLeftNode)
			parentOfRemoveNode->left = removeNode->right;
		else
			parentOfRemoveNode->right = removeNode->right;

		// if the node to the right of the node being removed has a left 
		//thread, change its thread to the parent node
		if (!removeNode->right->hasLeftChild)
			removeNode->right->left = parentOfRemoveNode;

		return;
	}

	// set replacementNode to left
	replacementNode = removeNode->left;

	// if the left node doesn't have a right node, the left node is the 
	//replacement
	if (!replacementNode->hasRightChild)
	{
		if (isRoot)
			root = removeNode->left;
		else if (isLeftNode)
			parentOfRemoveNode->left = removeNode->left;
		else
			parentOfRemoveNode->right = removeNode->left;

		replacementNode->right = removeNode->right;
		replacementNode->hasRightChild = true;

		return;
	}

	// if the left node  of the node being removed isn't the replacement
	//node, store the parent of the replacement
	parentNodeOfReplacement = replacementNode;

	// keep going right until you hit one from the end of the tree
	while (parentNodeOfReplacement->right->hasRightChild)
	{
		parentNodeOfReplacement = parentNodeOfReplacement->right;
	}

	// store the replacement node
	replacementNode = parentNodeOfReplacement->right;

	// if the replacement node has a left node,
	//  set the right of the parent node to the 
	//  left of the replacement node
	if (replacementNode->hasLeftChild)
		parentNodeOfReplacement->right = replacementNode->left;

	// otherwise, set the right to a thread, but keep the right node
	else
		parentNodeOfReplacement->hasRightChild = false;

	// set replacement node's edges to the edges of the node about to be
	//removed
	replacementNode->left = removeNode->left;
	replacementNode->right = removeNode->right;
	replacementNode->hasLeftChild = removeNode->hasLeftChild;
	replacementNode->hasRightChild = removeNode->hasRightChild;

	// if the removed node is the left or right of its parent,
	//  set the parent node's left/right to the replacement
	if (isRoot)
		root = replacementNode;
	else if (isLeftNode)
		parentOfRemoveNode->left = replacementNode;
	else
		parentOfRemoveNode->right = replacementNode;
}

/* Summary: Clears entire BST and its memory
* Pre-condition: node to remove itself all nodes below it
* Post condition: deleted tree starting at currNode
*/
void BinaryTreeInterface::clear(Node* currNode)
{
	if (currNode == nullptr)
	{
		return;
	}
	if (currNode->hasLeftChild)
	{
		clear(currNode->left);
	}
	if (currNode->hasRightChild)
	{
		clear(currNode->right);
	}

	delete currNode;
	//root = nullptr;
}

/* Summary: Returns the node with the targeted value
* Pre-condition:takes in target to find
* Post condition: returns new node and target to the getEntry helper function
*/
Node* BinaryTreeInterface::getEntry(const int target) const
{
	return getEntry(root, target);
}

/* Summary: getEntry helper function
* Pre-condition: currNode and target value
* Post condition: returns the value found, or returns if value not found
*/
Node* BinaryTreeInterface::getEntry(Node* currNode, const int target) const
{
	// if the target is equal to data in tree, item is found
	if (target == currNode->data) {
		//the item is found
		return currNode;
	}
	// checks left continues to search through, contains
	else if (target < currNode->data) {
		if (currNode->hasLeftChild)
			return getEntry(currNode->left, target);
		return nullptr;
	}
	// checks right continues to search through, contains
	else {
		if (currNode->hasRightChild)
			return getEntry(currNode->right, target);
		return nullptr;
	}
}

/* Summary: Contains function to see if the BST contains target value
* Pre-condition: target to check for
* Post condition: returns target passed through get entry to check for target
*/
bool BinaryTreeInterface::contains(const int target)
{
	return (getEntry(target)->data == target);
}

/* Summary: Prints the tree in order
* Pre-condition: n/a
* Post condition: prints the tree in order
*/
void BinaryTreeInterface::printInOrderTraversal()
{
	Node* currNode = root;

	if (currNode == nullptr)
		return;

	Node* currNode2 = currNode;

	while (currNode2->hasLeftChild)
		currNode2 = currNode2->left;

	while (true)
	{
		cout << currNode2->data << " ";

		if (currNode2->right == nullptr)
			break;

		currNode2 = inorderFindNextNode(currNode2);
	}

	cout << endl;
}

/* Summary: Finds next node when traversal
* Pre-condition: current node in the traversal
* Post condition: next node in traversal
*/
Node* BinaryTreeInterface::inorderFindNextNode(Node* currNode)
{
	//sends the next inorder node
	if (!currNode->hasRightChild)
		return currNode->right;

	currNode = currNode->right;

	while (currNode->hasLeftChild)
	{
		currNode = currNode->left;
	}

	return currNode;
}

/* Summary: Removes all even integers
* Pre-condition: n/a
* Post condition: all even nodes removed from tree
*/
bool BinaryTreeInterface::removeEvens()
{
	bool removedAllEvens = true;

	// get vector of all nodes
	vector<int> vector = convertToVector();

	// remove every odd value from vector
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] % 2 == 1)
			vector.erase(vector.begin() + i);
	}

	// remove all of the nodes left in the even vector
	for (int removeValue : vector)
	{
		if (!remove(removeValue))
			removedAllEvens = false;
	}

	return removedAllEvens;
}

/* Summary: returns the root node
* Pre-condition: n/a
* Post condition: returns the root node
*/
Node* BinaryTreeInterface::getRoot() {
	return root;
}