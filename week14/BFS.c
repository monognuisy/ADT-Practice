#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Queue {
  int queue[MAX_SIZE + 1];
  int rear;
  int front;
} Queue;

typedef struct Graph {
  int adjMatrix[MAX_VERTICES][MAX_VERTICES];
  int n;
} Graph;

void init(Graph* g) {
  g->n = 0;
  for (int i = 0; i < MAX_VERTICES; i++) {
    for (int j = 0; j < MAX_VERTICES; j++) {
      g->adjMatrix[i][j] = 0;
    }
  }
}

void initQueue(Queue* q) { q->front = q->rear = 0; }

void insertVertex(Graph* g, int v) {
  if (g->n == MAX_VERTICES) {
    printf("vertex 개수가 너무 많습니다. node 삽입 불가.\n");
    return;
  }
  g->n++;
}

void insertEdge(Graph* g, int u, int v) {
  if (u >= g->n || v >= g->n) {
    printf("정점 번호가 잘못됨.\n");
    return;
  }

  g->adjMatrix[u][v] = 1;
  g->adjMatrix[v][u] = 1;
}

int isFull(Queue* q) {
  if ((q->rear + 1) % MAX_SIZE == q->front)
    return TRUE;
  else
    return FALSE;
}

int isEmpty(Queue* q) {
  if (q->front == q->rear)
    return TRUE;
  else
    return FALSE;
}

void enqueue(Queue* q, int data) {
  if (isFull(q))
    printf("큐가 가득 참.\n");
  else {
    q->queue[q->rear] = data;
    q->rear = (q->rear + 1) % MAX_SIZE;
  }
}

int dequeue(Queue* q) {
  int tmp = -1;
  if (isEmpty(q))
    printf("큐가 비어있음.\n");
  else {
    tmp = q->queue[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
  }

  return tmp;
}

void bfs(Graph* g, int v) {
  int w, search_v;
  Queue q;
  initQueue(&q);
  visited[v] = TRUE;
  enqueue(&q, v);

  while (!isEmpty(&q)) {
    search_v = dequeue(&q);
    printf("%d -> ", search_v);

    for (w = 0; w < MAX_VERTICES; w++) {
      if (g->adjMatrix[search_v][w] == 1 && visited[w] == FALSE) {
        visited[w] = TRUE;
        enqueue(&q, w);
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

  bfs(&g, 0);

  return 0;
}