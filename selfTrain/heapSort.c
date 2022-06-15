#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 50
#define INF 987654321

typedef int bool_t;

int list[7] = {1, 5, 7, 4, 3, 2, 6};

typedef struct Heap {
  int nodes[MAX_NODE];
  int lastIndex;
} Heap;

bool_t max(int a, int b) { return (a > b); }
bool_t min(int a, int b) { return (a < b); }

void initHeap(Heap* h, bool_t (*cmp)(int, int)) {
  for (int i = 0; i < MAX_NODE; i++) {
    h->nodes[i] = (cmp(INF, -INF) ? -INF : INF);
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

void insertHeap(Heap* h, int data, bool_t (*cmp)(int, int)) {
  if (h->lastIndex == MAX_NODE - 1)
    return;

  // data는 맨 마지막에 넣어줄 것! 일단은 빈공간 만들기.
  h->lastIndex++;
  int index = h->lastIndex;

  // index가 1이 아니고, data가 부모의 값보다 클 때동안 반복해라.
  while ((index != 1) && cmp(data, h->nodes[index / 2])) {
    // 자식에다가 부모의 값을 넣어준다.
    h->nodes[index] = h->nodes[index / 2];
    index /= 2;
  }
  h->nodes[index] = data;
}

int deleteHeap(Heap* h, bool_t (*cmp)(int, int)) {
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

  int parentIndex = 1;
  int childIndex = 2;

  // 맨 위(빈공간)부터 슬슬 아래로 내려오면서 부모를 자식으로 바꿔주기.
  while (childIndex <= h->lastIndex) {
    // sibling 중 더 큰 녀석이 childIndex가 됨.
    childIndex = cmp(h->nodes[childIndex], h->nodes[childIndex + 1])
                     ? childIndex
                     : childIndex + 1;

    // 만약, 마지막 값이 이 child의 값보다 이상이면 그만해도 됨.
    if (!cmp(h->nodes[childIndex], lastData))
      break;

    // 부모 자식 change.
    h->nodes[parentIndex] = h->nodes[childIndex];
    parentIndex = childIndex;
    childIndex *= 2;
  }

  // 마지막으로, 부모 자리에 마지막 값 넣어주기.
  h->nodes[parentIndex] = lastData;

  h->nodes[h->lastIndex] = (cmp(INF, -INF) ? -INF : INF);
  h->lastIndex--;

  return topNode;
}

void heapSort(int list[], int len, bool_t (*cmp)(int, int)) {
  Heap h;
  initHeap(&h, cmp);

  for (int i = 0; i < len; i++) {
    insertHeap(&h, list[i], cmp);
  }

  for (int i = 0; i < len; i++) {
    list[i] = deleteHeap(&h, cmp);
  }
}

void printList(int list[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%d\t", list[i]);
  }

  printf("\n");
}

int main() {
  heapSort(list, 7, max);
  printList(list, 7);

  heapSort(list, 7, min);
  printList(list, 7);

  return 0;
}