

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include <vector>
using namespace std;

class SkipList;

class SNode {
		friend class SkipList;
		friend ostream& operator<<(ostream& out, const SkipList& skip);

public:
	// SNode stores int as data
	explicit SNode(int value);

	// data for SNode
	int value{ 0 };

	// link to next SNode
	SNode* forward;

	// link to prev SNode
	SNode* backward;

	// link to up one level
	SNode* up;

	// link to down one level
	SNode* down;

	// how many forward/backward pointers it has
	//int height() const;

	// increase the number of forward/backward pointers it has
	//void increaseHeight();
};

class SkipList {
	friend ostream& operator<<(ostream& out, const SkipList& skip);

public:
	
	explicit SkipList(int maxLevel = 1, int probability = 0);

	// destructor
	virtual ~SkipList();

	// copy not allowed
	SkipList(const SkipList& other) = delete;

	// move not allowed
	SkipList(SkipList&& other) = delete;

	// assignment not allowed
	SkipList& operator=(const SkipList& other) = delete;

	// move assignment not allowed
	SkipList& operator=(SkipList&& other) = delete;

	// return true if successfully added, no duplicates
	bool add(int value);

	// return true if successfully added, no duplicates
	bool add(const vector<int>& values);

	// return true if successfully removed
	bool remove(int value);

	// return true if found in
	bool contains(int value) const;

private:
	int maxLevel;
	int probability;

	// head of linked levels
	//SNode* head;

	// tail of linked levels
	//SNode* tail;

	// array of Depth SNode* objects as FrontGuards linking levels
	SNode** frontGuards;

	// array of Depth SNode* objects as RearGuards linking levels
	SNode** rearGuards;

	//bool shouldInsertAtHigher() const;
	// 50% it returns true or false
	bool alsoHigher() const;

	// Adds a new node before the current node
	void addBefore(SNode* newNode, SNode* nextNode);

	// Will add a node to given level and increase level by one.
	// Returns false if is already in list.
	bool findSpotAndAdd(SNode* newNode, int& level);

	//FROM GITHUB, NOT IN USE
	/*// return true p% of time,
  // for p = 50, each node has a 50% chance of being at higher level
  bool shouldInsertAtHigher() const;

  // connect 2 nodes in a line
  static void connect2AtLevel(SNode *a, SNode *b, int level);

  // connect 3 nodes in a line
  static void connect3AtLevel(SNode *a, SNode *b, SNode *c, int level);

  SNode *containsSNode(int data) const;

  vector<SNode *> getBeforeNodes(int data) const;*/
};


#endif //ASS4_SKIPLIST_H