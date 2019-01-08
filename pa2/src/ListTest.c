// ListTest.c - Test linked list
// Chris Griffis <chdgriff>
// pa2

#include "List.h"

int main() {
  List L = newList();

  append(L, 0);
  append(L, 1);
  append(L, 2);
  append(L, 3);

  printList(stdout, L);

  freeList(&L);

  return 0;
}
