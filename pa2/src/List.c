// List.c - Doubly Linked list implementation
// Chris Griffis <chdgriff>
// pa2

#include "List.h"
#include <stdlib.h>
#include <assert.h>

// private helper methods

typedef struct NodeObj {
  int data;
  struct NodeObj* next;
  struct NodeObj* previous;
} NodeObj;

typedef struct NodeObj* Node; // creates Node object reference called Node

Node newNode(int d) { // Node constructor
  Node N = malloc(sizeof(NodeObj));
  assert(N != NULL);

  N->data = d;
  N->next = NULL;
  N->previous = NULL;

  return N;
}

void freeNodes (Node N) { // frees all Nodes from given N on
  if (N == NULL) return;
  freeNodes(N->next);
  free(N);
}

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;

  int length;
  int cursorIndex;
}ListObj;

// Constructors and Deconstructors

List newList() {
  List L = malloc(sizeof(ListObj));
  assert(L != NULL);

  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->length = 0;
  L->cursorIndex = -1;

  return L;
}

// Frees list
void freeList(List* pL) {
  if (pL != NULL && *pL != NULL) {
    freeNodes((*pL)->front);

    free(*pL);
    *pL = NULL;
  }
}

// Access methods

// Returns length of List L
int length(List L) {
  if (L == NULL) {
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return L->length;
}

// Returns index of cursor for List L
int index(List L) {
  if (L == NULL) {
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }
  return L->cursorIndex;
}

// Returns data of front element in List L
int front(List L) {
  if (L == NULL) {
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if (L->length == 0) {
    printf("List  Error: calling front() on empty List\n");
    exit(1);
  }
  return L->front->data;
}

// Returns data of back element in List L
int back(List L) {
  if (L == NULL) {
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }
  if (L->length == 0) {
    printf("List  Error: calling back() on empty List\n");
    exit(1);
  }
  return L->back->data;
}

// Returns data of cursor
int get(List L) {
  if (L == NULL) {
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }
  if (L->cursorIndex == -1) {
    printf("List Error: calling get() when cursor is undefined\n");
    exit(1);
  }
  return L->cursor->data;
}

// Returns 1 if List A and B have the same data
int equals(List A, List B) {
  if (A == NULL || B == NULL) {
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }
  if (A->length != B->length) return 0;
  Node An = A->front;
  Node Bn = B->front;
  while (An != NULL) {
    if (An->data != Bn->data) return 0;
    An = An->next;
    Bn = Bn->next;
  }
  return 1;
}

// Manipulation methods

// Clears List L
void clear(List L) {
  if (L == NULL) {
    printf("List Error: calling clear() on NULL List reference\n");
    exit(1);
  }
  if (L->length > 0) {
    freeNodes(L->front);
  }
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->cursorIndex = -1;
}

// Moves cursor to front of List L
void moveFront(List L) {
  if (L == NULL) {
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(1);
  }
  if (L->length > 0) {
    L->cursor = L->front;
    L->cursorIndex = 0;
  }
}

// Moves cursor to back of List L
void moveBack(List L) {
  if (L == NULL) {
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  }
    if (L->length > 0) {
      L->cursor = L->back;
      L->cursorIndex = L->length-1;
    }
}

// Moves cursor to previous element in L
void movePrev(List L) {
  if (L == NULL) {
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  }
  if (L->cursorIndex != -1) {
    L->cursor = L->cursor->previous;
    L->cursorIndex--;
  }
}

// Moves cursor to next element in L
void moveNext(List L) {
  if (L == NULL) {
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  }
  if (L->cursorIndex != -1) {
    L->cursor = L->cursor->next;
    L->cursorIndex++;

    if (L->cursor == NULL) L->cursorIndex = -1; // If cursorIndex goes off list
  }
}

// Inserts new Node in the beginning of List L
void prepend(List L, int data) {
  if (L == NULL) {
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }

  Node N = newNode(data);
  if (L->length == 0) { // If empty list
    L->front = L->back = N;
  }
  else { // Other cases
    L->front->previous = N;
    N->next = L->front;
    L->front = N;
  }
  L->length++;

  if (L->cursorIndex > -1) L->cursorIndex++; // Updates cursor index if necessary
}

// Inserts new Node at the end of List L
void append(List L, int data) {
  if (L == NULL) {
    printf("List Error: calling append() on NULL List reference\n");
    exit(1);
  }

  Node N = newNode(data);
  if (L->length == 0) { // If empty list
    L->front = L->back = N;
  }
  else { // Other cases
    L->back->next = N;
    N->previous = L->back;
    L->back = N;
  }
  L->length++;
}

// Inserts new Node before cursor element in List L
void insertBefore(List L, int data) {
  if (L == NULL) {
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  }
  if (L->length == 0) {
    printf("List Error: calling insertBefore() on empty List\n");
    exit(1);
  }
  if (L->cursorIndex == -1) {
    printf("List Error: calling insertBefore() on undefined cursor\n");
    exit(1);
  }
  if (L->cursor == L->front) prepend(L, data);
  else {
    Node N = newNode(data);
    N->next = L->cursor;
    N->previous = L->cursor->previous;
    L->cursor->previous->next = N;
    L->cursor->previous = N;
    L->length++;
    L->cursorIndex++;
  }
}

// Inserts new Node after cursor
void insertAfter(List L, int data) {
  if (L == NULL) {
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  }
  if (L->length == 0) {
    printf("List Error: calling insertAfter() on empty List\n");
    exit(1);
  }
  if (L->cursorIndex == -1) {
    printf("List Error: calling insertAfter() on undefined cursor\n");
    exit(1);
  }
  if (L->cursor == L->back) append(L, data);
  else {
    Node N = newNode(data);
    N->next = L->cursor->next;
    N->previous = L->cursor;
    L->cursor->next->previous = N;
    L->cursor->next = N;
    L->length++;
  }
}

// Deletes front element of List L
void deleteFront(List L) {
  if (L == NULL) {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
  if (L->length == 0) {
    printf("List Error: calling insertAfter() on empty List\n");
    exit(1);
  }

  if (L->length == 1) {
    clear(L);
  }
  else {
    L->front = L->front->next;
    free(L->front->previous);
    L->front->previous = NULL;

    L->length--;
    L->cursorIndex--;
    if (L->cursorIndex == -1) L->cursor = NULL;
  }
}

// Deletes back element of List L
void deleteBack(List L) {
  if (L == NULL) {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
  if (L->length == 0) {
    printf("List Error: calling insertAfter() on empty List\n");
    exit(1);
  }

  if (L->length == 1) {
    clear(L);
  }
  else {
    L->back = L->back->previous;
    free(L->back->next);
    L->back->next = NULL;

    L->length--;
    if (L->cursorIndex == L->length) {
      L->cursor = NULL;
      L->cursorIndex = -1;
    }
  }
}

// deletes cursor element
void delete(List L) {
  if (L == NULL) {
    printf("List Error: calling delete() on NULL List reference\n");
    exit(1);
  }
  if (L->length == 0) {
    printf("List Error: calling delete() on empty List\n");
    exit(1);
  }
  if (L->cursorIndex == -1) {
    printf("List Error: calling delete() on undefined cursor\n");
    exit(1);
  }

  if (L->length == 1) clear(L); // if cursor is only element
  else if (L->cursor == L->front) deleteFront(L); // if cursor is at front
  else if (L->cursor == L->back) deleteBack(L); // if cursor is at back
  else { // other cases
    L->cursor->previous->next = L->cursor->next;
    L->cursor->next->previous = L->cursor->previous;
    L->cursorIndex = -1;
    free(L->cursor);
    L->cursor = NULL;
    L->length--;
  }
}

// Other Methods

// prints List to file pointer given
void printList(FILE* out, List L) {
  if (L == NULL) {
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  }
  Node N = L->front;
  if (N!= NULL) {
    fprintf(out, "%d", N->data);
    N = N->next;
  }
  while (N != NULL) {
    fprintf(out, " %d", N->data);
    N = N->next;
  }
}

// Returns a copy of List L
List copyList(List L) {
  List L2 = newList();
  Node N = L->front;
  while (N != NULL) {
    append(L2, N->data);
    N = N->next;
  }
  return L2;
}

// Concates List A and B and returns it
List concatList(List A, List B) {
  List L = newList();

  Node N = A->front;
  while (N != NULL) {
    append(L, N->data);
    N = N->next;
  }

  N = B->front;
  while (N != NULL) {
    append(L, N->data);
    N = N->next;
  }

  return L;
}
