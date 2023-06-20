#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Node {
  int data;
  struct Node* nextNode;
} Node;

typedef struct LinkedList {
  int curCount;
  Node headNode;
} LinkedList;

typedef struct StackNode {
  int data;
  struct StackNode* next;
} StackNode;

void pushLStack(StackNode** top, int data);
StackNode* popLStack(StackNode** top);
void showLStack(StackNode* top);
StackNode* topLStack(StackNode* top);
void deleteLStack(StackNode** top);
int isStackEmpty(StackNode* top);

int addNode(LinkedList* pList, int pos, int data);
int removeNode(LinkedList* pList, int pos);
void showNode(LinkedList* pList);
int isListEmpty(LinkedList* pList);
int findPos(LinkedList* pList, int data);
void makeEmpty(LinkedList* pList);

void reverseList(LinkedList* pList, StackNode** top);

int main() {
  // int pos;
  LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
  linkedList->curCount = 0;
  linkedList->headNode.nextNode = NULL;

  StackNode* top = NULL;

  addNode(linkedList, 0, 10);
  addNode(linkedList, 5, 100);
  addNode(linkedList, 1, 20);
  addNode(linkedList, 2, 30);
  addNode(linkedList, 1, 50);
  addNode(linkedList, 1, 70);
  addNode(linkedList, 1, 40);

  showNode(linkedList);

  reverseList(linkedList, &top);

  showNode(linkedList);

  makeEmpty(linkedList);
  showNode(linkedList);

  free(linkedList);

  return 0;
}

void showNode(LinkedList* pList) {
  if (pList == NULL) {
    printf("error\n");
    return;
  }

  printf("현재 node 개수: %d\n", pList->curCount);

  if (pList->curCount != 0) {
    Node* pNode = pList->headNode.nextNode;

    printf("[ ");
    while (pNode != NULL) {
      printf("%d ", pNode->data);
      pNode = pNode->nextNode;
    }
    printf("]\n");
  }
}

int isStackEmpty(StackNode* top) {
  if (top == NULL)
    return TRUE;
  else
    return FALSE;
}

void showLStack(StackNode* top) {
  if (isStackEmpty(top)) {
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

  if (isStackEmpty(*top)) {
    *top = newNode;
  } else {
    newNode->next = (*top);
    *top = newNode;
  }
}

StackNode* popLStack(StackNode** top) {
  if (isStackEmpty(*top)) {
    printf("Empty Stack\n");
    return NULL;
  }

  StackNode* topNode = (*top);
  *top = topNode->next;

  free(topNode);

  return topNode;
}

StackNode* topLStack(StackNode* top) {
  if (isStackEmpty(top)) {
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

int isListEmpty(LinkedList* pList) {
  if (pList == NULL) {
    printf("error\n");
    return FALSE;
  }

  if (pList->headNode.nextNode == NULL) {
    return TRUE;
  } else {
    return FALSE;
  }
}

int addNode(LinkedList* pList, int pos, int data) {
  if (pList == NULL) {
    printf("error\n");
    return FALSE;
  }
  if (pos < 0 || pos > pList->curCount) {
    printf("addNode() error2: 추가 범위 초과\n");
    return FALSE;
  }

  Node* newNode = (Node*)malloc(sizeof(Node));

  newNode->data = data;
  newNode->nextNode = NULL;

  Node* tempNode = &(pList->headNode);
  for (int i = 0; i < pos; i++) {
    tempNode = tempNode->nextNode;
  }

  newNode->nextNode = tempNode->nextNode;
  tempNode->nextNode = newNode;
  pList->curCount++;

  return TRUE;
}

int removeNode(LinkedList* pList, int pos) {
  if (pList == NULL) {
    printf("error\n");
    return FALSE;
  }
  if (pos < 0 || pos > pList->curCount) {
    printf("position error\n");
    return FALSE;
  }

  Node* prevNode = &(pList->headNode);

  for (int i = 0; i < pos; i++) {
    prevNode = prevNode->nextNode;
  }

  Node* nowNode = prevNode->nextNode;
  prevNode->nextNode = nowNode->nextNode;

  free(nowNode);
  nowNode = NULL;

  pList->curCount--;

  return TRUE;
}

int findPos(LinkedList* pList, int data) {
  if (pList == NULL) {
    printf("error\n");
    return FALSE;
  }

  Node* tempNode = pList->headNode.nextNode;
  int pos = 0;
  while (tempNode != NULL) {
    if (tempNode->data == data) {
      return pos;
    }
    tempNode = tempNode->nextNode;
    pos++;
  }

  return FALSE;
}

void makeEmpty(LinkedList* pList) {
  if (pList == NULL) {
    printf("error\n");
    return;
  }

  Node* delNode = &(pList->headNode);
  Node* moveNode = delNode->nextNode;

  while (moveNode != NULL) {
    delNode = moveNode;
    moveNode = moveNode->nextNode;

    free(delNode);
    delNode = NULL;
  }
  pList->headNode.nextNode = NULL;

  pList->curCount = 0;
}

void reverseList(LinkedList* pList, StackNode** top) {
  if (pList == NULL) {
    printf("error\n");
    return;
  }

  Node* pNode = NULL;

  printf("Reverse Linked List!\n");

  pNode = pList->headNode.nextNode;

  while (pNode != NULL) {
    pushLStack(top, pNode->data);
    pNode = pNode->nextNode;
  }

  makeEmpty(pList);

  pNode = &(pList->headNode);

  while (!isStackEmpty(*top)) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = topLStack(*top)->data;
    newNode->nextNode = NULL;
    pNode->nextNode = newNode;

    popLStack(top);
    pNode = pNode->nextNode;
    pList->curCount++;
  }
}