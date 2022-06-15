#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
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

typedef struct Queue {
  node_t queue[MAX_SIZE + 1];
  int rear;
  int front;
} Queue;

void init(Graph* g) {
  g->n = 0;
  for (int i = 0; i < MAX_VERTICES; i++) {
    for (int j = 0; j < MAX_VERTICES; j++) {
      g->adjMatrix[i][j] = FALSE;
    }
  }
}

void initQueue(Queue* q) { q->front = q->rear = 0; }

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

bool_t isFull(Queue* q) { return ((q->rear + 1) % MAX_SIZE == q->front); }

bool_t isEmpty(Queue* q) { return (q->rear == q->front); }

void enqueue(Queue* q, node_t data) {
  if (isFull(q))
    return;

  q->queue[q->rear] = data;
  q->rear = (q->rear + 1) % MAX_SIZE;
}

node_t dequeue(Queue* q) {
  node_t tmp;

  if (isEmpty(q))
    return -1;

  tmp = q->queue[q->front];
  q->front = (q->front + 1) % MAX_SIZE;

  return tmp;
}

void BFS(Graph* g, node_t start) {
  Queue q;
  initQueue(&q);
  visited[start] = TRUE;
  enqueue(&q, start);

  while (!isEmpty(&q)) {
    node_t curr = dequeue(&q);
    printf("%d -> ", curr);

    for (node_t next = 0; next < MAX_VERTICES; next++) {
      if (g->adjMatrix[curr][next] && !visited[next]) {
        visited[next] = TRUE;
        enqueue(&q, next);
      }
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

  BFS(&g, 0);

  return 0;
}