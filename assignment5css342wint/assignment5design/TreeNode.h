#ifndef TREENODE_H
#define TREENODE_H

class TreeNode {
  
public:
  explicit TreeNode(int data);
  int data;
  TreeNode* leftChild;
  TreeNode* rightChild;
  bool hasThread;
};

#endif // TREENODE_H
