// This is the SkipList cpp file, 
// the functions in this file work together with the
// skiplist.h file and main file to create
// a Skip List data structure to store integers 
// at multiple levels
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

//prints out / displays by level
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  for (int Index = SkipL.maxLevel - 1; Index >= 0; Index--) {
	Out << to_string(Index) + ": ";
	 SNode* Curr = SkipL.FrontGuards[Index]->forward;
	while(Curr != SkipL.RearGuards[Index]) {
	  Out<< to_string(Curr->value);
	  Curr = Curr->forward;
      if (Curr != SkipL.RearGuards[Index]){
        cout <<  "-->";
      }
	}
	Out << "\n";
  }
  return Out;
}

//SNode constructor that sets forward/backward/up/down to nullptr
SNode::SNode(int value) {  
    this->value = value;
    this->forward = nullptr;
    this->backward = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Constructor for the SkipList class.
// Initializes the maxLevel
// Creates maxLevel number of FrontGuards and RearGuards.
SkipList::SkipList(int maxLevel = 1, int probability = 0) {                                                
   SkipList::maxLevel = maxLevel;
   SkipList::probability = probability;
    this->FrontGuards = new SNode * [maxLevel];
    this->RearGuards = new SNode * [maxLevel];
    auto NewFront = new SNode(INT_MIN);
    auto NewBack = new SNode(INT_MAX);

    NewFront->forward = NewBack;
    NewBack->backward = NewFront;

    this->FrontGuards[0] = NewFront;
    this->RearGuards[0] = NewBack;

    for (int Index = 1; Index < maxLevel; Index++) {
        NewFront = new SNode(INT_MIN);
        NewBack = new SNode(INT_MAX);

        NewFront->forward = NewBack;
        NewBack->backward = NewFront;
        this->FrontGuards[Index] = NewFront;
        this->RearGuards[Index] = NewBack;

        NewFront->down = this->FrontGuards[Index - 1];
        this->FrontGuards[Index - 1]->up = NewFront;

        NewBack->down = this->RearGuards[Index - 1];
        this->RearGuards[Index - 1]->up = NewBack;
    }
}

 // returns a random int, that determines
 //probability of being at a higher level
bool SkipList::alsoHigher() const {
    int random = rand() % 100;
    return random < probability;
}

// Description: takes in added values
// cannot be duplicates
// Pre: values
// Post: added values
bool SkipList::add(const vector<int>& values) {

    bool addedValues = true;

    for(const int &value : values){
        if(!add(value))
        addedValues = false;
    }
return addedValues;
}

// Description:
// Pre: value
// Post: return true if value not a duplicate
// and value was added successfully 
bool SkipList::add(int value) {
    SNode* Curr = FrontGuards[0]->forward;

    while (Curr != RearGuards[0] && Curr->value <= value) {
     
            if (Curr->value == value) {
                return false;
            }
        Curr = Curr->forward;
    }
    auto NewNode = new SNode(value);
    addBefore(NewNode, Curr);
    int CurrDepth = 1;
    Curr = NewNode;
    while (alsoHigher() && (CurrDepth < this->maxLevel)) {
    auto NewUpperNode = new SNode(value);
    Curr->up = NewUpperNode;
    NewUpperNode->down = Curr;
    Curr = FrontGuards[CurrDepth]->forward;

        while (Curr != RearGuards[CurrDepth] && Curr->value <= value) {
        
          Curr = Curr->forward;
        }

    addBefore(NewUpperNode, Curr);
    Curr = NewUpperNode;
    CurrDepth++;

    }
    return true; 
}

// destructor removes/deletes
SkipList::~SkipList() {
    SNode* curr = FrontGuards[0]->forward;
    SNode* nextNode;
    while (curr != RearGuards[0]) {
        nextNode = curr->forward;
        this->remove(curr->value);
        curr = nextNode;
    }
    for (int i{ 0 }; i < maxLevel; i++) {
        delete FrontGuards[i];
        delete RearGuards[i];
    }
    delete[] FrontGuards;
    delete[] RearGuards;
}

// Description:
// Pre: value
// Post: returns true if successfully removed value
// false otherwise
bool SkipList::remove(int value) {
    SNode* curr = findNode(value);

    if (curr != nullptr) {
        while (curr->down != nullptr) {
            SNode* forward = curr->forward;
            SNode* backward = curr->backward;
            forward->backward = backward;
            backward->forward = forward;
            curr = curr->down;
            delete curr->up;
        }
        
        SNode* forward = curr->forward;
        SNode* backward = curr->backward;
        forward->backward = backward;
        backward->forward = forward;
        delete curr;
        return true;
    }
    return false;
}

//Given a SNode, place it before the given NextNode
//provided in the Github starter file
void SkipList::addBefore(SNode* NewNode, SNode* NextNode) {
    // Link next to node in front
    NewNode->forward = NextNode;
    // Link prev to node behind
    NewNode->backward = NextNode->backward;
    // Link node in back to new node
    NextNode->backward->forward = NewNode;
    // Link node in front to new node
    NextNode->backward = NewNode;
}

// Description: searches for the existance
// of a value
// Pre: value
// Post: returns if contains value or not
bool SkipList::contains(int value) const {
    return (findNode(value) != nullptr);
}

// Description: Given a data value returns a pointer to that
// node in the list at the highest level.
// Returns nullptr if the desired node does not exist in the SkipList
// Pre: value
// Post: returns nullptr or returns curr if curr = value
SNode* SkipList::findNode(int value) const {
    int level = maxLevel - 1;
  
    SNode* Curr = FrontGuards[maxLevel - 1]->forward;

     while(level >= 0) { 
        while (Curr->value < value) {
            Curr = Curr->forward;
        }

        if (Curr->value == value) {
            return Curr;
        }
    
        Curr = Curr->backward;
        Curr = Curr->down;
        level--;
    }
    return nullptr;
}