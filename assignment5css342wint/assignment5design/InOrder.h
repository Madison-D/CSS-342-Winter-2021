#ifndef INORDER_H
#define INORDER_H

class InOrder {
  
public:
  InOrder(TreeNode* position);
  const int& operator*() const;
  int& operator*();
  bool operator==(const InOrder& p) const;
  InOrder operator++(int);
  InOrder& operator++();
  InOrder& operator--();
  
private:
  TreeNode* pos;
};

#endif // INORDER_H
