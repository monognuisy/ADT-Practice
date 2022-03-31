#include <stdio.h>

const int MAX = 10000;

long long f(int n, long long* arr) {
  arr[0] = 0;
  arr[1] = 1;

  for (int i = 2; i <= n; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }

  return arr[n];
}

int main() {
  long long arr[MAX];
  int N;
  scanf("%d", &N);

  printf("%lld\n", f(N, arr));

  return 0;
}