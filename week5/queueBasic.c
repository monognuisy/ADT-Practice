#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define CAPACITY 5

typedef struct circularQueue {
  int data[CAPACITY];
  int front;
  int rear;
} circularQueue;

circularQueue* createCQueue();
void enqueue(circularQueue* cQueue, int data);
int isFull(circularQueue* cQueue);
void showQueue(circularQueue* cQueue);
int isEmpty(circularQueue* cQueue);
void dequeue(circularQueue* cQueue);

void printFR(circularQueue* cQueue);
void succByCap(int* num);

int main() {
  circularQueue* cQueue = createCQueue();

  printFR(cQueue);
  enqueue(cQueue, 10);
  enqueue(cQueue, 20);
  enqueue(cQueue, 30);
  showQueue(cQueue);
  printFR(cQueue);

  dequeue(cQueue);
  dequeue(cQueue);
  showQueue(cQueue);
  printFR(cQueue);

  enqueue(cQueue, 40);
  printFR(cQueue);
  enqueue(cQueue, 50);
  printFR(cQueue);
  enqueue(cQueue, 60);
  printFR(cQueue);
  enqueue(cQueue, 70);
  printFR(cQueue);
  showQueue(cQueue);

  return 0;
}

void printFR(circularQueue* cQueue) {
  printf("front: %d,  rear: %d\n", cQueue->front, cQueue->rear);
}

void succByCap(int* num) { *num = ((*num) + 1) % CAPACITY; }

circularQueue* createCQueue() {
  circularQueue* newQueue = (circularQueue*)malloc(sizeof(circularQueue));
  newQueue->front = 0;
  newQueue->rear = 0;

  return newQueue;
}

void showQueue(circularQueue* cQueue) {
  int i = 0;

  if (isEmpty(cQueue)) {
    printf("Empty Queue\n");
    return;
  }

  printf("==========Show Queue==========\n");

  for (i = cQueue->front + 1; i != cQueue->rear; succByCap(&i)) {
    printf("[%d]\n", cQueue->data[i]);
  }
  printf("[%d]\n", cQueue->data[i]);

  printf("==============================\n");
}

void enqueue(circularQueue* cQueue, int data) {
  if (isFull(cQueue)) {
    printf("Full Queue\n");
    return;
  }

  succByCap(&(cQueue->rear));
  cQueue->data[cQueue->rear] = data;
}

void dequeue(circularQueue* cQueue) {
  if (isEmpty(cQueue)) {
    printf("Empty Queue\n");
    return;
  }

  succByCap(&(cQueue->front));
}

int isFull(circularQueue* cQueue) {
  if ((cQueue->rear + 1) % CAPACITY == cQueue->front)
    return TRUE;
  else
    return FALSE;
}

int isEmpty(circularQueue* cQueue) {
  if (cQueue->front == cQueue->rear)
    return TRUE;
  else
    return FALSE;
}