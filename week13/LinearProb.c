#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 10
#define TABLE_SIZE 13
#define empty(e) (strlen(e.key) == 0)
#define equal(e1, e2) (!strcmp(e1.key, e2.key))

typedef struct Element {
  char key[KEY_SIZE];
} Element;

Element hashTable[TABLE_SIZE];

void initTable(Element ht[]) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    ht[i].key[0] = 0;
  }
}

int transform(char* key) {
  int number = 0;
  int size = strlen(key);

  for (int i = 0; i < size; i++) {
    number = number + key[i];
  }

  return number;
}

int hashFunction(char* key) { return (transform(key) % TABLE_SIZE); }

void addHashTable(Element item, Element ht[]) {
  int hashValue = hashFunction(item.key);
  int i = hashValue;

  while (!empty(ht[i])) {
    if (equal(ht[i], item)) {
      printf("중복 삽입 에러\n");
      return;
    }
    else {
      i = (i + 1) % TABLE_SIZE;
      if (i == hashValue) {  // 모든 bucket 조사함
        return;
      }
    }
  }
  ht[i] = item;
}

void hashSearch(Element item, Element ht[]) {
  int hashValue = hashFunction(item.key);
  int i = hashValue;

  while (!empty(ht[i])) {
    if (equal(ht[i], item)) {
      printf("탐색 성공: 존재합니다.\n");
      return;
    }
    else {
      i = (i + 1) % TABLE_SIZE;
      if (i == hashValue) {  // 모든 bucket 조사함
        break;
      }
    }
  }

  printf("테이블에 찾는 값이 없습니다.\n");
}

void printHashTable(Element ht[]) {
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    printf("[%d]\t%s\n", i, ht[i].key);
  }
}

int main() {
  Element temp;
  int op;

  while (1) {
    printf("연산 입력(0: 추가, 1: 탐색, 2: 종료) = ");
    scanf("%d", &op);

    if (op == 2)
      break;

    printf("키 입력: ");
    scanf("%s", temp.key);
    if (op == 0)
      addHashTable(temp, hashTable);
    else if (op == 1)
      hashSearch(temp, hashTable);
    printHashTable(hashTable);
  }

  return 0;
}