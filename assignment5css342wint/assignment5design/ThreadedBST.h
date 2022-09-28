#ifndef THREADEDBST_H
#define THREADEDBST_H

#include "TreeNode.h"
#include "InOrder.h"

class ThreadedBST {

  friend ostream &operator<<(ostream &out, const ThreadedBST &tree);

public: 
  ThreadedBST();
  ThreadedBST(int numNodes);
  ~ThreadedBST();
  bool add(int newValue);
  bool remove(int valueToRemove);
  
private:
  InOrder findNode(int value);
  string inOrder(TreeNode* startNode);
  string preOrder(TreeNode* startNode);
  string postOrder(TreeNode* startNode);
};

#endif // THREADEDBST_H
