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

  for (int i = 0; i <= h->lastIndex; i++) {
    printf("%d\t", h->nodes[i]);
    if (i == lineLength - 1) {
      printf("\n");
      lineLength *= 2;
    }
  }

  printf("\n\n");
}

void deleteHeap(Heap* h) {
  int temp, parentIndex, childIndex;

  if (h->lastIndex == 0) {
    printf("Heap is Empty!!\n");
    return;
  }

  if (h->lastIndex == 1) {
    h->nodes[h->lastIndex] = 0;
    h->lastIndex = 0;
    return;
  }

  temp = h->nodes[h->lastIndex];

  parentIndex = 1;
  childIndex = 2;

  while (childIndex <= h->lastIndex) {
    childIndex = (h->nodes[childIndex] > h->nodes[childIndex + 1])
                     ? childIndex
                     : (childIndex + 1);

    if (temp >= h->nodes[childIndex]) break;

    h->nodes[parentIndex] = h->nodes[childIndex];
    parentIndex = childIndex;
    childIndex *= 2;
  }

  h->nodes[parentIndex] = temp;
}

void insertHeap(Heap* h, int data) {
  int index;

  if (h->lastIndex == MAX_NODE - 1) {
    printf("Heap is FULL!!\n");
    return;
  }

  h->lastIndex++;
  index = h->lastIndex;

  while ((index != 1) && (data > h->nodes[index / 2])) {
    h->nodes[index] = h->nodes[index / 2];
    index /= 2;
  }
  h->nodes[index] = data;
}

int main() {
  Heap h;
  initHeap(&h);
}