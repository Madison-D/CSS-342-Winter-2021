
#include <iostream>
#include <climits>
#include "skiplist.h"
#include <time.h>
#include <vector>

#include <string>
#include <cassert>
#include <cstdlib>

using namespace std;

ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int Index = SkipL.maxLevel - 1; Index >= 0; Index--) {
	Out << "Level: " + to_string(Index) + " -- ";
	 SNode* Curr = SkipL.frontGuards[Index];
	while(Curr != nullptr) {
	  Out<< to_string(Curr->value) + ", ";
	  Curr = Curr->forward;
	}
	Out << "\n";
  }
  return Out;
}


SNode::SNode(int value) : value{ value }, up{ nullptr }, down{ nullptr },
forward{ nullptr }, backward{ nullptr } {}

// Constructor for the SkipList class.
// Initializes the depth to be the desire value.
// Creates Depth number of FrontGuards and RearGuards.

/*SkipList::SkipList(int maxLevel = 1, int probability = 0) { //SkipList::SkipList(int Depth, double prob=50)                                                   
	//SkipList::maxLevel = maxLevel;
	//SkipList::probability = probability;

	//this->maxLevel = maxLevel;
	// Create the front and rear guards to be the desired depth
	this->frontGuards = new SNode * [maxLevel];
	this->rearGuards = new SNode * [maxLevel];
	auto NewFront = new SNode(INT_MIN);
	auto NewBack = new SNode(INT_MAX);

	NewFront->forward = NewBack;
	NewBack->backward = NewFront;

	this->frontGuards[0] = NewFront;
	this->rearGuards[0] = NewBack;
	for (int Index = 1; Index < maxLevel; Index++) {
		NewFront = new SNode(INT_MIN);
		NewBack = new SNode(INT_MAX);

		NewFront->forward = NewBack;
		NewBack->backward = NewFront;
		this->frontGuards[Index] = NewFront;
		this->rearGuards[Index] = NewBack;

		NewFront->down = this->frontGuards[Index - 1];
		this->frontGuards[Index - 1]->up = NewFront;

		NewBack->down = this->rearGuards[Index - 1];
		this->rearGuards[Index - 1]->up = NewBack;
	}
}*/

SkipList::SkipList(int maxLevel, int probability) : maxLevel{ maxLevel }, probability{ probability }
{
	this -> maxLevel = maxLevel;
	probability = probability;

	frontGuards = new SNode * [maxLevel];
	rearGuards = new SNode * [maxLevel];

	frontGuards[0] = new SNode(INT_MIN);
	rearGuards[0] = new SNode(INT_MAX);
	frontGuards[0]->forward = rearGuards[0];
	rearGuards[0]->backward = frontGuards[0];

	for (int i{ 1 }; i < maxLevel; i++) {
		// Create nodes
		frontGuards[i] = new SNode(INT_MIN);
		rearGuards[i] = new SNode(INT_MAX);

		// Set nodes down level
		frontGuards[i]->down = frontGuards[i - 1];
		rearGuards[i]->down = rearGuards[i - 1];

		// Set last nodes up level
		frontGuards[i - 1]->up = frontGuards[i];
		rearGuards[i - 1]->up = rearGuards[i];

		// Set nodes next and prev
		frontGuards[i]->forward = rearGuards[i];
		rearGuards[i]->backward = frontGuards[i];
	}
	srand(static_cast<unsigned int>(time(0)));
}

// Destructor
SkipList::~SkipList() {
	SNode* curr = frontGuards[0]->forward;
	SNode* nextNode;
	while (curr != rearGuards[0]) {
		nextNode = curr->forward;
		this->remove(curr->value);
		curr = nextNode;
	}
	for (int i{ 0 }; i < maxLevel; i++) {
		delete frontGuards[i];
		delete rearGuards[i];
	}
	delete[] frontGuards;
	delete[] rearGuards;
}

// return true if successfully added, no duplicates
bool SkipList::add(int value) {
	int level{ 0 };
	SNode* newNode = new SNode(value);

	if (!findSpotAndAdd(newNode, level)) {
		return false;
	}

	SNode* lowerNode = newNode;
	while (alsoHigher() && level < maxLevel) {
		SNode* newHigherNode = new SNode(value);
		newHigherNode->down = lowerNode;
		lowerNode->up = newHigherNode;
		findSpotAndAdd(newHigherNode, level);
	}
	return true;
}

// return true if successfully removed
bool SkipList::remove(int value) {
	if (!this->contains(value)) {
		return false;
	}
	int level{ maxLevel - 1 };
	SNode* curr;
	while (level >= 0) {
		curr = frontGuards[level];
		while (curr != nullptr) {
			if (curr->value == value) {
				SNode* forward = curr->forward;
				SNode* backward = curr->backward;
				forward->backward = backward;
				backward->forward = forward;
				delete curr;
				curr = forward;
			}
			curr = curr->forward;
		}
		level--;
	}
	return true;
}

// return true if found in
bool SkipList::contains(int value) const {
	SNode* curr = frontGuards[maxLevel - 1]->forward;
	for (int i{ maxLevel - 1 }; i >= 0; i--) {
		bool checkLevel = true;
		while (checkLevel) {
			if (curr == nullptr || curr == rearGuards[0]) {
				return false;
			}
			if (curr->value == value) {
				return true;
			}
			if (curr->value > value) {
				curr = curr->backward;
				curr = curr->down;
				checkLevel = false;
			}
			else {
				curr = curr->forward;
			}

		}
	}
	return false;
}

// 50% it returns true or false
bool SkipList::alsoHigher() const {
	return rand() % 2 == 1;
}

// Adds a new node before the current node
void SkipList::addBefore(SNode* newNode, SNode* nextNode) {
	newNode->backward = nextNode->backward;
	newNode->forward = nextNode;
	nextNode->backward->forward = newNode;
	nextNode->backward = newNode;
}

// Will add a node to given level and increase level by one.
// Returns false if is already in list.

bool SkipList::findSpotAndAdd(SNode* newNode, int& level) {
	SNode* curr = frontGuards[level];

	while (curr->value < newNode->value) {
		curr = curr->forward;
		if (curr->value == newNode->value) {
			return false;
		}
	}
	addBefore(newNode, curr);
	level++;
	return true;
}

bool SkipList::add(const vector<int>& values) {

	for (const int& value : values)
	{
		add(value);
	}
	//???? for loop for values to add if not a duplicate, return true, return false for dupe

	return true;
}
