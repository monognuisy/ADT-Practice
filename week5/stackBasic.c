#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct StackNode {
  int data;
  struct StackNode* next;
} StackNode;

void pushLStack(StackNode** top, int data);
StackNode* popLStack(StackNode** top);
void showLStack(StackNode* top);
StackNode* topLStack(StackNode* top);
void deleteLStack(StackNode** top);
int isEmpty(StackNode* top);

int main() {
  StackNode* top = NULL;

  pushLStack(&top, 10);
  pushLStack(&top, 20);
  pushLStack(&top, 30);
  showLStack(top);

  popLStack(&top);
  showLStack(top);

  printf("%d\n", topLStack(top)->data);

  deleteLStack(&top);
  showLStack(top);

  return 0;
}

int isEmpty(StackNode* top) {
  if (top == NULL)
    return TRUE;
  else
    return FALSE;
}

void showLStack(StackNode* top) {
  if (isEmpty(top)) {
    printf("Empty Stack\n");
    return;
  }

  StackNode* node = top;

  printf("==========Show Stack==========\n");

  while (node != NULL) {
    printf("[%d]\n", node->data);
    node = node->next;
  }

  printf("==============================\n");
}

void pushLStack(StackNode** top, int data) {
  StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
  newNode->data = data;
  newNode->next = NULL;

  if (isEmpty(*top)) {
    *top = newNode;
  } else {
    newNode->next = (*top);
    *top = newNode;
  }
}

StackNode* popLStack(StackNode** top) {
  if (isEmpty(*top)) {
    printf("Empty Stack\n");
    return NULL;
  }

  StackNode* topNode = (*top);
  *top = topNode->next;

  free(topNode);

  return topNode;
}

StackNode* topLStack(StackNode* top) {
  if (isEmpty(top)) {
    printf("Empty Stack\n");
    return NULL;
  }

  return top;
}

void deleteLStack(StackNode** top) {
  StackNode* moveNode = *top;
  StackNode* delNode = NULL;

  while (moveNode != NULL) {
    delNode = moveNode;
    moveNode = moveNode->next;
    free(delNode);
  }

  *top = NULL;
}