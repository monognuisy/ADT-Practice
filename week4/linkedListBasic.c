#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE -1

typedef struct Node {
  int data;
  struct Node* nextNode;
} Node;

typedef struct LinkedList {
  int curCount;
  Node headNode;
} LinkedList;

int addNode(LinkedList* pList, int pos, int data);
int removeNode(LinkedList* pList, int pos);
void showNode(LinkedList* pList);
int isEmpty(LinkedList* pList);
int findPos(LinkedList* pList, int data);
void makeEmpty(LinkedList* pList);

int main() {
  // int pos;
  LinkedList* ll = (LinkedList*)malloc(sizeof(LinkedList));
  ll->curCount = 0;
  ll->headNode.nextNode = NULL;

  addNode(ll, 0, 100);
  addNode(ll, 0, 20);
  addNode(ll, 0, 30);
  addNode(ll, 0, 50);
  addNode(ll, 0, 80);

  showNode(ll);

  removeNode(ll, 1);

  showNode(ll);

  printf("%d\n", findPos(ll, 50));

  makeEmpty(ll);

  showNode(ll);
  return 0;
}

void showNode(LinkedList* pList) {
  Node* pNode = NULL;

  if (pList == NULL) {
    printf("error\n");
    return;
  }

  printf("현재 node 개수: %d\n", pList->curCount);
  pNode = pList->headNode.nextNode;

  printf("[ ");
  while (pNode != NULL) {
    printf("%d ", pNode->data);
    pNode = pNode->nextNode;
  }
  printf("]\n");
}

int isEmpty(LinkedList* pList) {
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
    printf("position error\n");
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
    return FALSE;
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