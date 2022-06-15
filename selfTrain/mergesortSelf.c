#include <stdio.h>
#include <stdlib.h>

int list[7] = {7, 6, 5, 4, 3, 2, 1};

void merge(int list[], int left, int mid, int right) {
  // i: left ~ mid 까지 움직이는 녀석.
  // j: mid + 1 ~ right 까지 움직이는 녀석.
  // k: tempList의 index.
  int i, j, k;
  i = k = left;
  j = mid + 1;

  int* tempList = (int*)malloc(sizeof(int) * 7);

  // i, j 각각 자기네 범위에서 움직이면서 tempList에 저장.
  while (i <= mid && j <= right) {
    tempList[k++] = (list[i] <= list[j]) ? list[i++] : list[j++];
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

void mergeSort(int list[], int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    mergeSort(list, left, mid);
    mergeSort(list, mid + 1, right);
    merge(list, left, mid, right);
  }
}

int main() {
  mergeSort(list, 0, 6);

  for (int i = 0; i < 7; i++) {
    printf("%d\t", list[i]);
  }

  printf("\n");

  return 0;
}