// GraphTest.c - tests Graph.c ADT
// Chris Griffis <chdgriff>
// pa4
#include "Graph.h"

int main() {
  Graph graph0;
  List l0;

  graph0 = newGraph(8);

  addEdge(graph0, 1, 4);
  addEdge(graph0, 1, 5);

  addEdge(graph0, 2, 3);
  addEdge(graph0, 2, 7);

  addEdge(graph0, 3, 5);
  addEdge(graph0, 3, 6);

  addEdge(graph0, 4, 6);
  addEdge(graph0, 4, 8);

  addEdge(graph0, 5, 7);

  addEdge(graph0, 7, 8);


  printGraph(stdout, graph0);
  printf("\n");

  BFS(graph0, 1);

  printf("Order: %d\n", getOrder(graph0));
  printf("Size: %d\n", getSize(graph0));
  printf("Source: %d\n", getSource(graph0));

  printf("\n");

  l0 = newList();
  for (int i = 1; i < getOrder(graph0)+1; i++) {
    printf("Distance to source: %d\n", getDist(graph0, i));
    getPath(l0, graph0, i);
    printf("Path to %d: ", i);
    printList(stdout, l0);
    printf("\n");
    clear(l0);
  }

  freeList(&l0);
  freeGraph(&graph0);

  // implements test from script
  Graph A = newGraph(100);
  List L = newList();
  List C = newList();

   addArc(A, 64, 4);
  addArc(A, 64, 3);
  addArc(A, 42, 2);
  addArc(A, 2, 64);
  addArc(A, 4, 2);
  addArc(A, 3, 42);
  BFS(A, 3);
  getPath(L, A, 64);
  append(C, 3);
  append(C, 42);
  append(C, 2);
  append(C, 64);
  if (!equals(L, C)) printf("1\n");
  moveFront(L);
  BFS(A, 2);
  getPath(L, A, 2);
  append(C, 2);
  if (!equals(L, C)) printf("2\n");
  printGraph(stdout, A);
  printf("\n");
  printList(stdout, L);
  printf("\t");
  printList(stdout, C);
  printf("\n");
  getPath(L, A, 99);
  if (equals(L, C)) printf("3\n");
  clear(L);
  clear(C);
  append(C, NIL);
  BFS(A, 99);
  getPath(L, A, 2);
  if (!equals(C, L)) printf("4\n");

  freeList(&L);
  freeList(&C);
  freeGraph(&A);

  return 0;
}

