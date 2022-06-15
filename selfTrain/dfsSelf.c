#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

typedef int node_t;
typedef int bool_t;

bool_t visited[MAX_VERTICES];

typedef struct Graph {
  bool_t adjMatrix[MAX_VERTICES][MAX_VERTICES];
  int n;
} Graph;

void init(Graph* g) {
  g->n = 0;
  for (int i = 0; i < MAX_VERTICES; i++) {
    for (int j = 0; j < MAX_VERTICES; j++) {
      g->adjMatrix[i][j] = FALSE;
    }
  }
}

void insertVertex(Graph* g, node_t v) {
  if (g->n == MAX_VERTICES) {
    printf("too many!\n");
    return;
  }

  g->n++;
}

void insertEdge(Graph* g, node_t v1, node_t v2) {
  g->adjMatrix[v1][v2] = g->adjMatrix[v2][v1] = TRUE;
}

void DFS(Graph* g, node_t start) {
  visited[start] = TRUE;
  printf("%d -> ", start);

  for (node_t next = 0; next < MAX_VERTICES; next++) {
    if (g->adjMatrix[start][next] && !visited[next]) {
      DFS(g, next);
    }
  }
}

int main() {
  Graph g;

  init(&g);

  for (int i = 0; i < MAX_VERTICES; i++) {
    visited[i] = FALSE;
  }
  for (int i = 0; i < 7; i++) insertVertex(&g, i);

  insertEdge(&g, 0, 4);
  insertEdge(&g, 0, 6);
  insertEdge(&g, 1, 3);
  insertEdge(&g, 3, 5);
  insertEdge(&g, 4, 1);
  insertEdge(&g, 4, 2);
  insertEdge(&g, 6, 2);

  DFS(&g, 0);

  return 0;
}