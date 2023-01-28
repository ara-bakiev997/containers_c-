#include <iostream>
typedef int Data;

typedef struct Node {
  Data data;
  struct Node* left;
  struct Node* right;
} Node;

void tree_print(Node* tree) {
  if (tree == NULL) return;
  tree_print(tree->left);
  printf("%d ", tree->data);
  tree_print(tree->right);
}
void print(Node* tree) {
  tree_print(tree);
  printf("\n");
}

Node* tree_add(Node* tree, Data d) {
  if (tree == NULL) {
    Node* t = new Node;
    t->data = d;
    t->left = t->right = NULL;
    return t;
  }
  if (d < tree->data) {
    tree->left = tree_add(tree->left, d);
  }
  if (d > tree->data) {
    tree->right = tree_add(tree->right, d);
  }
  return tree;
}

int main() {
  Node* tree = NULL;
  tree = tree_add(tree, 7);
  print(tree);

  tree = tree_add(tree, 7);
  print(tree);

  tree = tree_add(tree, 3);
  print(tree);



  return 0;
}