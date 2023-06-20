#include <stdio.h>
#include <stdlib.h>

#define Max(x, y) (((x) > (y)) ? (x) : (y))

typedef struct Avlnode {
  int data;
  struct Avlnode* left;
  struct Avlnode* right;
  int height;
} Avlnode;

int height(Avlnode* node) {
  if (node == NULL)
    return -1;
  else
    return node->height;
}

Avlnode* rotateLL(Avlnode* parent) {
  Avlnode* child = parent->left;

  parent->left = child->right;
  child->right = parent;

  parent->height = Max(height(parent->left), height(parent->right)) + 1;
  child->height = Max(height(child->left), parent->height) + 1;

  return child;
}

Avlnode* rotateRR(Avlnode* parent) {
  Avlnode* child = parent->right;

  parent->right = child->left;
  child->left = parent;

  parent->height = Max(height(parent->left), height(parent->right)) + 1;
  child->height = Max(height(child->right), parent->height) + 1;

  return child;
}

Avlnode* rotateLR(Avlnode* parent) {
  Avlnode* child = parent->left;
  parent->left = rotateRR(child);
  return rotateLL(parent);
}

Avlnode* rotateRL(Avlnode* parent) {
  Avlnode* child = parent->right;
  parent->right = rotateLL(child);
  return rotateRR(parent);
}

Avlnode* avlAdd(Avlnode* root, int data) {
  if (root == NULL) {
    root = (Avlnode*)malloc(sizeof(Avlnode));
    if (root == NULL) {
      exit(1);
    }

    root->data = data;
    root->height = 0;
    root->left = root->right = NULL;
  }
  else if (data < root->data) {
    root->left = avlAdd(root->left, data);

    if (height(root->left) - height(root->right) == 2) {
      if (data < root->left->data)
        return rotateLL(root);
      else
        return rotateLR(root);
    }
  }
  else if (data > root->data) {
    root->right = avlAdd(root->right, data);

    if (height(root->right) - height(root->right) == 2) {
      if (data > root->right->data)
        return rotateRR(root);
      else
        return rotateRL(root);
    }
  }
  else {
    printf("중복 키 삽입 오류!\n");
    exit(1);
  }

  root->height = Max(height(root->left), height(root->right)) + 1;
  return root;
}

Avlnode* avlSearch(Avlnode* node, int key) {
  if (node == NULL)
    return NULL;
  if (key == node->data)
    return node;
  else if (key < node->data)
    return avlSearch(node->left, key);
  else
    return avlSearch(node->right, key);
}

void inorderTraveling(Avlnode* root) {
  if (root != NULL) {
    inorderTraveling(root->left);
    printf("[%d] ", root->data);
    inorderTraveling(root->right);
  }
}

int main() {
  Avlnode* root = NULL;
  root = avlAdd(root, 7);
  root = avlAdd(root, 8);
  root = avlAdd(root, 9);
  root = avlAdd(root, 2);
  root = avlAdd(root, 1);
  root = avlAdd(root, 5);
  root = avlAdd(root, 3);
  root = avlAdd(root, 6);
  root = avlAdd(root, 4);

  printf("\n검색: %d\n", avlSearch(root, 4)->data);
  printf("\n");
  inorderTraveling(root);
  return 0;
}