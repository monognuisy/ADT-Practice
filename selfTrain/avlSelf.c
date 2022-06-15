#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y)) ? (x) : (y)

typedef struct AvlNode {
  int data;
  struct AvlNode* left;
  struct AvlNode* right;
  int height;
} AvlNode;

int height(AvlNode* node) {
  if (node == NULL) {
    return -1;
  }
  else {
    return node->height;
  }
}

AvlNode* rotateLL(AvlNode* parent) {
  AvlNode* child = parent->left;

  parent->left = child->right;
  child->right = parent;

  parent->height = MAX(height(parent->left), height(parent->right)) + 1;
  child->height = MAX(height(child->left), height(child->right)) + 1;

  return child;
}

AvlNode* rotateRR(AvlNode* parent) {
  AvlNode* child = parent->right;

  parent->right = child->left;
  child->left = parent;

  parent->height = MAX(height(parent->left), height(parent->right)) + 1;
  child->height = MAX(height(child->left), height(child->right)) + 1;

  return child;
}

AvlNode* rotateLR(AvlNode* parent) {
  parent->left = rotateRR(parent->left);
  return rotateLL(parent);
}

AvlNode* rotateRL(AvlNode* parent) {
  parent->right = rotateLL(parent->right);
  return rotateRR(parent);
}

AvlNode* avlAdd(AvlNode* root, int data) {
  if (root == NULL) {
    root = (AvlNode*)malloc(sizeof(AvlNode));

    root->data = data;
    root->height = 0;
    root->left = root->right = NULL;
  }
  else if (data < root->data) {
    root->left = avlAdd(root->left, data);

    if (height(root->left) - height(root->right) == 2) {
      if (data < root->left->data) {
        return rotateLL(root);
      }
      else {
        return rotateLR(root);
      }
    }
  }
  else if (data > root->data) {
    root->right = avlAdd(root->right, data);

    if (height(root->right) - height(root->left) == 2) {
      if (data > root->right->data) {
        return rotateRR(root);
      }
      else {
        return rotateRL(root);
      }
    }
  }
  else {
    printf("error\n");
    exit(1);
  }

  root->height = MAX(height(root->left), height(root->right)) + 1;
  return root;
}

AvlNode* avlSearch(AvlNode* node, int key) {
  if (node == NULL)
    return NULL;
  if (key == node->data)
    return node;
  else if (key < node->data)
    return avlSearch(node->left, key);
  else
    return avlSearch(node->right, key);
}

void inorder(AvlNode* root) {
  if (root == NULL)
    return;

  inorder(root->left);
  printf("[%d] ", root->data);
  inorder(root->right);
}

int main() {
  AvlNode* root = NULL;
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
  inorder(root);
  return 0;
}