// This is the SkipList header file, 
// it holds the SNode class, and the SkipList class
// that work together in the skiplist cpp file
// both files work together to create
// a Skip List data structure to store integers 
// at multiple levels
#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>

using namespace std;

class SkipList;

class SNode {
	friend class SkipList;
	friend ostream& operator<<(ostream& Out, const SkipList& SkipL);

public:
	//snode class constructor
	explicit SNode(int value);

	//data variable
	int value;

	//links to the next SNode
	SNode* forward;

	//links to the previous SNode
	SNode* backward;
	
	//links to the upward SNode
	SNode* up;

	//links to the downward SNode
	SNode* down;
};

class SkipList {
	//prints out / displays
	friend ostream& operator<<(ostream& Out, const SkipList& SkipL);

public:
	//construstor for the SkipList class
	explicit SkipList(int maxLevel, int probability); 

	//destructor
	virtual ~SkipList();

	//adds a value
	bool add(int value);

	//adds values
	bool add(const vector<int>& values);

	//removes values
	bool remove(int value);

	//checks if value is found in skiplist
	bool contains(int value) const;

private:
	//probability variable (random value between 0 to 100%)
	int probability;

	//max number of levels
	int maxLevel;

	//head of linked levels
	SNode** FrontGuards;

	//tail of linked levels
	SNode** RearGuards;

	//returns random, for a chance of higher level
	bool alsoHigher() const;

	//places before given NextNode
	void addBefore(SNode* NewNode, SNode* NextNode); 

	//given a value, returns a pointer, returns nullptr if node does not exist
	SNode* findNode(int value) const;
};

#endif // ASS4_SKIPLIST_H
