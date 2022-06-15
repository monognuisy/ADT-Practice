#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int bool_t;

int list[7] = {1, 5, 7, 4, 3, 2, 6};

bool_t descending(int a, int b) { return (a > b); }
bool_t ascending(int a, int b) { return (a < b); }

void swap(int* pa, int* pb) {
  int temp = *pa;
  *pa = *pb;
  *pb = temp;
}

int partition(int list[], int left, int right, bool_t (*cmp)(int, int)) {
  // 일부러 하나씩 엇나가게 잡음. do-while 위해서.
  int low = left;
  int high = right + 1;
  int pivot = list[left];

  do {
    // low 인덱스의 값이 pivot 이상이 되면 break. (low를 점점 늘려가며)
    do {
      low++;
    } while (low <= right && cmp(list[low], pivot));
    // high 인덱스의 값이 pivot 이상이 되면 break. (high를 점점 줄여가며)
    do {
      high--;
    } while (high >= left && cmp(pivot, list[high]));

    if (low < high) {
      swap(&list[low], &list[high]);
    }
  } while (low < high);  // 끝나면 high와 low가 역전돼있음. (high + 1 == low)

  // list[left] 와 list[high]를 바꿔준다.
  swap(&list[left], &list[high]);

  // pivot이 들어갈 위치를 반환.
  return high;
}

void quickSort(int list[], int left, int right, bool_t (*cmp)(int, int)) {
  if (left < right) {
    int pivotLocation = partition(list, left, right, cmp);
    quickSort(list, left, pivotLocation - 1, cmp);
    quickSort(list, pivotLocation + 1, right, cmp);
  }
}

void merge(int list[], int left, int mid, int right, bool_t (*cmp)(int, int)) {
  // i: left ~ mid 까지 움직이는 녀석.
  // j: mid + 1 ~ right 까지 움직이는 녀석.
  // k: tempList의 index.
  int i, j, k;
  i = k = left;
  j = mid + 1;

  int* tempList = (int*)malloc(sizeof(int) * 7);

  // i, j 각각 자기네 범위에서 움직이면서 tempList에 저장.
  while (i <= mid && j <= right) {
    tempList[k++] = cmp(list[i], list[j]) ? list[i++] : list[j++];
  }
  // 나머지 것들도 저장!
  while (i <= mid) {
    tempList[k++] = list[i++];
  }
  while (j <= right) {
    tempList[k++] = list[j++];
  }

  for (int l = left; l <= right; l++) {
    list[l] = tempList[l];
  }
}

void mergeSort(int list[], int left, int right, bool_t (*cmp)(int, int)) {
  if (left < right) {
    int mid = (left + right) / 2;
    mergeSort(list, left, mid, cmp);
    mergeSort(list, mid + 1, right, cmp);
    merge(list, left, mid, right, cmp);
  }
}

void printList(int list[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%d\t", list[i]);
  }

  printf("\n");
}

int main() {
  quickSort(list, 0, 6, ascending);
  printList(list, 7);

  quickSort(list, 0, 6, descending);
  printList(list, 7);

  mergeSort(list, 0, 6, ascending);
  printList(list, 7);

  mergeSort(list, 0, 6, descending);
  printList(list, 7);

  return 0;
}