// GraphTest.c - 
// Chris Griffis <chdgriff>
// pa5

#include "Graph.h"

int main() {
  Graph G, G1, G2;
  List S;

  G = newGraph(5);
  // Adds arcs
  addArc(G, 1, 2);
  addArc(G, 1, 3);
  addArc(G, 2, 3);
  addArc(G, 2, 5);
  addArc(G, 3, 1);
  addArc(G, 3, 4);
  addArc(G, 4, 4);
  addArc(G, 4, 5);

  // Prints Graph
  printf("getOrder(): %d\n", getOrder(G));
  printf("getSize(): %d\n", getSize(G));
  printGraph(stdout, G);

  // Increments S
  S = newList();
  for (int i = 1; i <= getOrder(G); i++) {
    append(S, i);
  }
  printf("\nS: ");
  printList(stdout, S);
  printf("\n");

  // Finds DFS and prints stack
  DFS(G, S);
  printf("\nDFS stack: ");
  printList(stdout, S);

  // Prints all discovery and finish times
  printf("\nDiscovery and finish times:\n");
  for (int i = 1; i <= getOrder(G); i++) {
    if (i > 1) printf("\n");
    printf("%d: P: %d, ", i, getParent(G, i));
    printf("D: %d, ", getDiscover(G, i));
    printf("F: %d", getFinish(G, i));
  }

  G1 = copyGraph(G);
  printf("\n\nGraph copy:\n");
  printf("getOrder(): %d\n", getOrder(G1));
  printf("getSize(): %d\n", getSize(G1));
  printGraph(stdout, G1);


  // Prints transpose
  G2 = transpose(G);
  printf("\n\nTranspose:\n");
  printf("getOrder(): %d\n", getOrder(G2));
  printf("getSize(): %d\n", getSize(G2));
  printGraph(stdout, G2);

  freeList(&S);
  freeGraph(&G1);
  freeGraph(&G2);
  freeGraph(&G);

  return 0;
}

