#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 3
#define MIN_DATA -987654321

typedef struct skiplist {
  int data;
  int level;
  struct skiplist* next[MAX_LEVEL];
} skiplist;

void showList(skiplist* head) {
  printf("-------------------------------------\n");
  skiplist* tempnode;

  for (int i = MAX_LEVEL; i > 0; i--) {
    printf("Level %d:\t", i);
    tempnode = head->next[0];

    while (tempnode) {
      if (tempnode->level >= i)
        printf("%d----", tempnode->data);
      else
        printf("-----");

      tempnode = tempnode->next[0];
    }
    printf("NULL\n");
  }

  printf("-------------------------------------\n");
}

void insertList(skiplist* head, int data) {
  skiplist* prevnode[MAX_LEVEL];
  skiplist* newnode;

  int level = 1;

  for (int i = 0; i < MAX_LEVEL; i++) {
    prevnode[i] = head;
  }

  for (int i = MAX_LEVEL - 1; i >= 0; i--) {
    while (prevnode[i]->next[i]) {
      if (prevnode[i]->next[i]->data > data) break;

      prevnode[i] = prevnode[i]->next[i];
    }
  }

  newnode = (skiplist*)malloc(sizeof(skiplist));
  newnode->data = data;

  while (rand() & 1) {
    level++;
    if (level >= MAX_LEVEL) break;
  }

  newnode->level = level;

  for (int i = 0; i < MAX_LEVEL; i++) {
    newnode->next[i] = prevnode[i]->next[i];
    prevnode[i]->next[i] = newnode;
  }

  printf("Insert [%d] with level [%d]\n", data, level);
}

int main() {
  srand(time(NULL));

  skiplist* s = (skiplist*)malloc(sizeof(skiplist));

  s->level = MAX_LEVEL;
  s->data = MIN_DATA;

  insertList(s, 3);
  insertList(s, 9);
  showList(s);

  insertList(s, 1);
  insertList(s, 4);
  showList(s);

  // searchSkipNode(s, 4);
  return 0;
}