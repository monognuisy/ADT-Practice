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

void insertHeap(Heap* h, int data) {
  if (h->lastIndex == MAX_NODE - 1)
    return;

  // data는 맨 마지막에 넣어줄 것! 일단은 빈공간 만들기.
  h->lastIndex++;
  int index = h->lastIndex;

  // index가 1이 아니고, data가 부모의 값보다 클 때동안 반복해라.
  while ((index != 1) && (data > h->nodes[index / 2])) {
    // 자식에다가 부모의 값을 넣어준다.
    h->nodes[index] = h->nodes[index / 2];
    index /= 2;
  }
  h->nodes[index] = data;
}

int deleteHeap(Heap* h) {
  if (h->lastIndex == 0)
    return -1;

  int topNode = h->nodes[1];
  if (h->lastIndex == 1) {
    h->nodes[1] = 0;
    h->lastIndex--;
    return topNode;
  }

  // 미리 마지막 노드를 저장.
  int lastData = h->nodes[h->lastIndex];

  // printf("last: %d\n", lastData);

  int parentIndex = 1;
  int childIndex = 2;

  // 맨 위(빈공간)부터 슬슬 아래로 내려오면서 부모를 자식으로 바꿔주기.
  while (childIndex <= h->lastIndex) {
    // sibling 중 더 큰 녀석이 childIndex가 됨.
    childIndex = (h->nodes[childIndex] > h->nodes[childIndex + 1])
                     ? childIndex
                     : childIndex + 1;

    // 만약, 마지막 값이 이 child의 값보다 이상이면 그만해도 됨.
    if (lastData >= h->nodes[childIndex])
      break;

    // 부모 자식 change.
    h->nodes[parentIndex] = h->nodes[childIndex];
    parentIndex = childIndex;
    childIndex *= 2;
  }

  // 마지막으로, 부모 자리에 마지막 값 넣어주기.
  h->nodes[parentIndex] = lastData;

  h->nodes[h->lastIndex] = 0;
  h->lastIndex--;

  return topNode;
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

  printf("top: %d\n", deleteHeap(&h));

  printHeap(&h);

  printf("top: %d\n", deleteHeap(&h));

  printHeap(&h);

  return 0;
}