#include <stdio.h>
#include <stdlib.h>

int list[7] = {7, 6, 5, 4, 3, 2, 1};

void swap(int* pa, int* pb) {
  int temp = *pa;
  *pa = *pb;
  *pb = temp;
}

int partition(int list[], int left, int right) {
  // 일부러 하나씩 엇나가게 잡음. do-while 위해서.
  int low = left;
  int high = right + 1;
  int pivot = list[left];

  do {
    // low 인덱스의 값이 pivot 이상이 되면 break. (low를 점점 늘려가며)
    do {
      low++;
    } while (low <= right && list[low] < pivot);
    // high 인덱스의 값이 pivot 이상이 되면 break. (high를 점점 줄여가며)
    do {
      high--;
    } while (high >= left && list[high] > pivot);

    if (low < high) {
      swap(&list[low], &list[high]);
    }
  } while (low < high);  // 끝나면 high와 low가 역전돼있음. (high + 1 == low)

  // list[left] 와 list[high]를 바꿔준다.
  swap(&list[left], &list[high]);

  // pivot이 들어갈 위치를 반환.
  return high;
}

void quickSort(int list[], int left, int right) {
  if (left < right) {
    int pivotLocation = partition(list, left, right);
    quickSort(list, left, pivotLocation - 1);
    quickSort(list, pivotLocation + 1, right);
  }
}

int main() {
  quickSort(list, 0, 6);

  for (int i = 0; i < 7; i++) {
    printf("%d\t", list[i]);
  }

  printf("\n");

  return 0;
}