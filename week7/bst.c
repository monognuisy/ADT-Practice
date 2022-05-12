#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* leftChild;
  struct node* rightChild;
} node;

void insertTreeNode(node** root, int value);
void printTreePre(node* root);
void printTreePost(node* root);
void printTreeIn(node* root);

int main() {
  node* root = NULL;

  insertTreeNode(&root, 4);
  insertTreeNode(&root, 2);
  insertTreeNode(&root, 6);
  insertTreeNode(&root, 1);
  insertTreeNode(&root, 3);
  insertTreeNode(&root, 5);
  insertTreeNode(&root, 7);

  printf("Show Pre\n");
  printTreePre(root);
  printf("\nShow Post\n");
  printTreePost(root);
  printf("\nShow In\n");
  printTreeIn(root);

  return 0;
}

void insertTreeNode(node** root, int value) {
  if ((*root) == NULL) {
    (*root) = (node*)malloc(sizeof(node));
    (*root)->data = value;
    (*root)->leftChild = NULL;
    (*root)->rightChild = NULL;
  } else if (value > (*root)->data) {
    insertTreeNode(&((*root)->rightChild), value);
  } else {
    insertTreeNode(&((*root)->leftChild), value);
  }
}

void printTreePre(node* root) {
  if (!root) {
    return;
  }

  printf("%3d", root->data);
  printTreePre(root->leftChild);
  printTreePre(root->rightChild);
}
void printTreePost(node* root) {
  if (!root) {
    return;
  }

  printTreePost(root->leftChild);
  printTreePost(root->rightChild);
  printf("%3d", root->data);
}
void printTreeIn(node* root) {
  if (!root) {
    return;
  }

  printTreeIn(root->leftChild);
  printf("%3d", root->data);
  printTreeIn(root->rightChild);
}