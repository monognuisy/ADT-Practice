#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 7
#define INF 1000

typedef int node_t;
typedef int bool_t;

int graph[MAX][MAX] = {
    {0, 28, INF, INF, INF, 10, INF}, {28, 0, 16, INF, INF, INF, 14},
    {INF, 16, 0, 12, INF, INF, INF}, {INF, INF, 12, 0, 22, INF, 18},
    {INF, INF, INF, 22, 0, 25, 24},  {10, INF, INF, INF, 25, 0, INF},
    {INF, 14, INF, 18, 24, INF, 0}};

// vertex set. 즉, selected == True면 vertex set에 있는 것임.
bool_t selected[MAX];
int dist[MAX];

// 연결되있으면서 vertex set에 없는 녀석들 중 가장 최소인 길이를 가지는 애 반환.
// 연결이 안되어있다면 dist는 INF 일 것임.
// n은 총 vertex 개수
node_t getMinVertex(int n) {
  node_t v;

  // vertex set에 없는 애 중 하나 고르기(임시로. 후에 대소 비교하는데 쓸 예정.)
  for (node_t i = 0; i < n; i++) {
    // 만일 vertex set에 없다면
    if (!selected[i]) {
      v = i;
      break;
    }
  }

  for (node_t i = 0; i < n; i++) {
    // 만일 vertex set에 없다면, 가장 작은 거리를 가지는 i를 v로 세팅해라.
    if (!selected[i] && (dist[i] < dist[v])) {
      v = i;
    }
  }

  return v;
}

void prim(node_t start, int n) {
  // 먼저 거리를 다 INF로 초기화.
  for (int i = 0; i < n; i++) {
    dist[i] = INF;
  }

  dist[start] = 0;

  // 최대 n번만 돌리면 되니까, n번 반복.
  for (int i = 0; i < n; i++) {
    node_t curr = getMinVertex(n);
    selected[curr] = TRUE;

    printf("%d -> ", curr);

    // curr과 연결된 녀석의 거리를 update.
    for (node_t next = 0; next < n; next++) {
      // 이 조건이 없으면, 이전에 연결되어있어도 나중에 연결이 안되면 INF로
      // 초기화되어서 문제가 생긴다.
      if (graph[curr][next] != INF) {
        dist[next] = graph[curr][next];
      }
    }
  }
}

int main() {
  prim(0, MAX);

  return 0;
}
