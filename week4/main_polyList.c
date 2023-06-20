#define _CRT_SECURE_NO_WARNINGS

#define BUFFSIZE 1024
#define MAX_EXP 100

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct polyTerm {
  int order;
  int coeff;
  struct polyTerm* nextNode;
} polyTerm;

typedef struct poly {
  int size;
  polyTerm* headNode;
} poly;

// Poly computation function.
void clearPoly(poly* A);
void printPoly_impl(poly A, char* buffer);
void printPoly(poly A);
void addTerm(poly* A, int exp, int coeff);

void initPoly(poly* A);

void clearPoly(poly* A) {
  if (A == NULL) {
    printf("error\n");
    return;
  }

  polyTerm* delPoly = A->headNode;
  polyTerm* movePoly = delPoly->nextNode;

  free(delPoly);  // headNode free하기 위함

  while (movePoly != NULL) {
    delPoly = movePoly;
    movePoly = movePoly->nextNode;

    free(delPoly);
    delPoly = NULL;
  }

  A->size = 0;
}

void printPoly_impl(poly A, char* buffer) {
  polyTerm* tempNode = A.headNode->nextNode;
  int isFirst = 1;

  if (A.size == 0) {
    sprintf(buffer, "0");
    return;
  }

  while (tempNode != NULL) {
    char tempBuffer[BUFFSIZE] = "";
    if (tempNode->coeff == 0) {
      tempNode = tempNode->nextNode;
      continue;
    }
    if (isFirst || tempNode->coeff < 0) {
      sprintf(tempBuffer, "%dx^%d", tempNode->coeff, tempNode->order);
      isFirst = 0;
    } else {
      sprintf(tempBuffer, "+%dx^%d", tempNode->coeff, tempNode->order);
    }
    strcat(buffer, tempBuffer);
    tempNode = tempNode->nextNode;
  }
}

void printPoly(poly A) {
  char buffer[BUFFSIZE] = "";
  printPoly_impl(A, buffer);
  printf(buffer);
}

void addTerm(poly* A, int exp, int coeff) {
  if (A == NULL) {
    printf("error\n");
    return;
  }

  polyTerm* addPoly = A->headNode->nextNode;

  while (addPoly != NULL) {
    if (addPoly->order == exp) {
      break;
    }
    addPoly = addPoly->nextNode;
  }

  if (addPoly) {
    addPoly->coeff += coeff;
  } else {
    polyTerm* tempNode = A->headNode;

    while (tempNode->nextNode != NULL) {
      if (tempNode->nextNode->order < exp) {
        break;
      }
      tempNode = tempNode->nextNode;
    }

    polyTerm* newNode = (polyTerm*)malloc(sizeof(polyTerm));

    newNode->coeff = coeff;
    newNode->order = exp;

    newNode->nextNode = tempNode->nextNode;
    tempNode->nextNode = newNode;
    A->size++;
  }
}

poly multiPoly(poly A, poly B) {
  poly res;
  initPoly(&res);

  polyTerm* ATempNode = A.headNode->nextNode;
  while (ATempNode != NULL) {
    polyTerm* BTempNode = B.headNode->nextNode;
    while (BTempNode != NULL) {
      addTerm(&res, ATempNode->order + BTempNode->order,
              ATempNode->coeff * BTempNode->coeff);
      BTempNode = BTempNode->nextNode;
    }
    ATempNode = ATempNode->nextNode;
  }

  return res;
}

void initPoly(poly* A) {
  A->size = 0;
  A->headNode = (polyTerm*)malloc(sizeof(polyTerm));
  A->headNode->nextNode = NULL;
}

int main() {
  poly A, B;
  initPoly(&A);
  initPoly(&B);

  addTerm(&A, 3, 1);
  addTerm(&A, 1, 2);
  addTerm(&A, 0, -1);
  printf("poly A: ");
  printPoly(A);
  printf("\n");

  addTerm(&B, 2, 2);
  addTerm(&B, 1, -1);
  addTerm(&B, 0, 1);
  printf("poly B: ");
  printPoly(B);
  printf("\n");

  poly mult = multiPoly(A, B);
  printf("A*B: ");
  printPoly(mult);
  printf("\n");

  clearPoly(&mult);
  clearPoly(&A);
  clearPoly(&B);

  return 0;
}