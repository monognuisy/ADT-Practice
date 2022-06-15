#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 50

typedef struct Heap {
  int nodes[MAX_NODE];
  int lastIndex;
} Heap;

void initHeap(Heap* h) {
  for (int i = 0; i < MAX_NODE; i++) {
    h->nodes[i] = 0;
  }
  h->lastIndex = 0;
}

void printHeap(Heap* h) {
  int lineLength = 2;

  for (int i = 1; i <= h->lastIndex; i++) {
    printf("%d\t", h->nodes[i]);
    if (i == lineLength - 1) {
      printf("\n");
      lineLength *= 2;
    }
  }

  printf("\n\n");
}

void deleteHeap(Heap* h) {
  int lastData = h->nodes[h->lastIndex];

  int parentIndex = 1;
  int childIndex = 2;

  while (childIndex <= h->lastIndex) {
    childIndex = (h->nodes[childIndex] > h->nodes[childIndex ^ 1])
                     ? childIndex
                     : childIndex ^ 1;

    if (lastData >= h->nodes[childIndex])
      break;

    h->nodes[parentIndex] = h->nodes[childIndex];
    parentIndex = childIndex;
    childIndex <<= 1;
  }

  h->nodes[parentIndex] = lastData;

  h->lastIndex--;
}

void insertHeap(Heap* h, int data) {
  if (h->lastIndex == MAX_NODE - 1) {
    printf("Heap is FULL!!\n");
    return;
  }

  h->lastIndex++;

  int index = h->lastIndex;

  while ((index != 1) && (data > h->nodes[index / 2])) {
    h->nodes[index] = h->nodes[index / 2];

    index /= 2;
  }

  h->nodes[index] = data;
}

int main() {
  Heap h;
  initHeap(&h);

  insertHeap(&h, 10);
  insertHeap(&h, 9);
  insertHeap(&h, 2);
  insertHeap(&h, 5);
  insertHeap(&h, 3);
  insertHeap(&h, 8);
  insertHeap(&h, 7);

  printHeap(&h);

  deleteHeap(&h);

  printHeap(&h);

  return 0;
}