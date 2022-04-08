#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 3
#define MIN_DATA -987654321

typedef struct SkipNode {
  int data;
  int level;
  struct SkipNode* next[MAX_LEVEL];
} SkipNode;

void insertSkipNode(SkipNode** head, int data);
void showSkipNode(SkipNode* head);
void searchSkipNode(SkipNode* head, int data);

int main() {
  srand(time(NULL));

  SkipNode* skipList = (SkipNode*)malloc(sizeof(SkipNode));
  skipList->level = MAX_LEVEL;
  skipList->data = MIN_DATA;

  insertSkipNode(&skipList, 3);
  insertSkipNode(&skipList, 9);
  showSkipNode(skipList);

  insertSkipNode(&skipList, 1);
  insertSkipNode(&skipList, 4);
  showSkipNode(skipList);

  searchSkipNode(skipList, 4);

  return 0;
}

void showSkipNode(SkipNode* head) {
  SkipNode* tempNode = NULL;
  printf("---------------------------------------\n");

  for (int i = MAX_LEVEL; i > 0; i--) {
    tempNode = head->next[0];
    printf("Level %d:\t", i);

    while (tempNode != NULL) {
      if (tempNode->level >= i)
        printf("%d-----", tempNode->data);
      else
        printf("------");
      tempNode = tempNode->next[0];
    }
    printf("NULL\n");
  }

  printf("---------------------------------------\n");
}

void searchSkipNode(SkipNode* head, int data) {
  int pos = MAX_LEVEL - 1;
  SkipNode* tempNode = head->next[pos];

  while (tempNode == NULL || tempNode->data > data) {
    tempNode = tempNode->next[--pos];
  }

  printf("Search [%d] : ", data);
  while (tempNode->data != data) {
    if (tempNode->next[pos] == NULL || tempNode->next[pos]->data > data)
      pos--;
    else {
      printf("%d, ", tempNode->data);
      tempNode = tempNode->next[pos];
      if (tempNode->data == data) {
        printf("%d\n", tempNode->data);
        return;
      }
    }
  }
  printf(",,,there is no %d\n", data);
  printf("-------------------------------\n");
}

void insertSkipNode(SkipNode** head, int data) {
  int level = 1;
  SkipNode* tempNode[MAX_LEVEL];
  SkipNode* newNode;

  for (int i = 0; i < MAX_LEVEL; i++) {
    tempNode[i] = *head;
  }

  for (int i = MAX_LEVEL - 1; i >= 0; i--) {
    while (tempNode[i]->next[i] != NULL) {
      if (tempNode[i]->next[i]->data > data) break;
      tempNode[i] = tempNode[i]->next[i];
    }
  }

  while (rand() % 2) {
    level++;
    if (level >= MAX_LEVEL) break;
  }

  newNode = (SkipNode*)malloc(sizeof(SkipNode));
  newNode->level = level;
  newNode->data = data;

  for (int i = 0; i < MAX_LEVEL; i++) {
    newNode->next[i] = NULL;
  }

  for (int i = newNode->level - 1; i >= 0; i--) {
    newNode->next[i] = tempNode[i]->next[i];
    tempNode[i]->next[i] = newNode;
  }

  printf("Insert [%d] with level [%d]\n", data, level);
}