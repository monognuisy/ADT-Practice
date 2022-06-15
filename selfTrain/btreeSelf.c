#include <stdio.h>
#include <stdlib.h>

#define M_WAY 3
#define TRUE 1;
#define FALSE 0;

typedef struct BTNode {
  int n;  // key의 개수
  int isLeaf;
  int isRoot;
  int keys[M_WAY];

  struct BTNode* childs[M_WAY + 1];
} BTNode;

BTNode* initBTNode();
BTNode* BTInsert(BTNode* root, int key);
BTNode* splitChild(BTNode* root);
void inorderTraversal(BTNode* root);

int main() {
  BTNode* root;
  int n, t;

  root = initBTNode();
  root->isRoot = 1;

  printf("넣을 데이터의 개수: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    printf("데이터를 입력하세요: ");
    scanf("%d", &t);
    root = BTInsert(root, t);
  }

  printf("트리 출력. \n");
  inorderTraversal(root);

  return 0;
}

BTNode* initBTNode() {
  BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
  newNode->n = 0;
  newNode->isLeaf = TRUE;
  newNode->isRoot = FALSE;

  for (int i = 0; i < M_WAY + 1; i++) {
    newNode->childs[i] = NULL;
  }

  return newNode;
}

BTNode* BTInsert(BTNode* root, int key) {
  // 만약 root가 leaf node라면
  if (root->isLeaf) {
    int pos;  // key가 들어갈 위치

    for (pos = 0; pos < root->n; pos++) {
      if (root->keys[pos] > key)
        break;
    }

    // 정렬(pos보다 뒤에 있는 녀석들을 한 칸씩 뒤로 shift) 후 key 삽입.
    for (int i = root->n; i > pos; i--) {
      root->keys[i] = root->keys[i - 1];
    }
    root->keys[pos] = key;
    root->n++;

    // 만일 keys가 다 찼고, root가 root 노드이면, 여기서 split.
    if (root->n == M_WAY && root->isRoot) {
      return splitChild(root);
    }

    // keys가 다 찼어도 그냥 leaf이면 상위 함수에서 split.
    return root;
  }

  // 만일 leaf가 아니라면 -> 계속 들어가 leaf까지 탐색!
  else {
    int pos;  // key가 들어갈 위치

    for (pos = 0; pos < root->n; pos++) {
      if (root->keys[pos] > key)
        break;
    }

    // leaf 까지 탐색!
    root->childs[pos] = BTInsert(root->childs[pos], key);

    // 그렇게 해서 찾은 child가 꽉 찼다면, 그제서야 split. 상위함수가 이 의미임.
    if ((root->childs[pos])->n == M_WAY) {
      // child[pos]를 split하여 그 가장 윗대가리 놈을 split에 저장함.
      BTNode* split = splitChild(root->childs[pos]);

      // 그 윗대가리 놈을 root에 넣어주기 위하여 일단 뒤로 한 칸씩 shift.
      for (int i = root->n; i > pos; i--) {
        root->keys[i] = root->keys[i - 1];
        root->childs[i + 1] = root->childs[i];
      }
      root->keys[pos] = split->keys[0];  // 윗대가리의 key값.
      root->n++;
      root->childs[pos] = split->childs[0];
      root->childs[pos + 1] = split->childs[1];
    }

    // 그리하여 윗대가리까지 추가했을 때, 만일 root가 꽉 찼으면 마지막으로
    // split.
    if (root->n == M_WAY && root->isRoot)
      return splitChild(root);

    return root;
  }
}

BTNode* splitChild(BTNode* root) {
  /*
         newParent
        /         \
      root    newSibling
  */

  BTNode* newParent;   // 윗대가리
  BTNode* newSibling;  // root 친구

  newParent = initBTNode();
  newParent->isLeaf = FALSE;  // 당연히 윗대가리는 leaf가 아니겠지.
  newParent->isRoot = root->isRoot;  // isRoot는 inherit.

  root->isRoot = FALSE;  // 이젠 더이상 root는 root가 아니다.

  newSibling = initBTNode();
  newSibling->isLeaf = root->isLeaf;  // root 친구(같은 level)니까...

  // root의 중간 지점을 정하고
  // 오른쪽 값들은 newSibling으로 이동.
  int mid = (M_WAY - 1) / 2;
  for (int i = mid + 1; i < M_WAY; i++) {
    newSibling->childs[i - (mid + 1)] = root->childs[i];
    newSibling->keys[i - (mid + 1)] = root->keys[i];
    newSibling->n++;

    root->childs[i] = NULL;
    root->keys[i] = 0;
    root->n--;
  }
  // child 포인터는 하나 더 많으므로, 끝난 후 한번 더 실행.
  newSibling->childs[M_WAY - (mid + 1)] = root->childs[M_WAY];
  root->childs[M_WAY] = NULL;

  // root의 가운데 있었던 key를 newParent로 이동.
  newParent->keys[0] = root->keys[mid];
  newParent->n++;

  root->keys[mid] = 0;
  root->n--;

  // 마지막으로, newParent의 자식들을 연결.
  newParent->childs[0] = root;
  newParent->childs[1] = newSibling;

  return newParent;
}

void inorderTraversal(BTNode* root) {
  printf("\n");

  int i;
  for (i = 0; i < root->n; i++) {
    if (!(root->isLeaf)) {
      inorderTraversal(root->childs[i]);
      printf("    ");
    }

    printf("%d", root->keys[i]);
  }

  if (!(root->isLeaf)) {
    inorderTraversal(root->childs[i]);
  }

  printf("\n");
}
