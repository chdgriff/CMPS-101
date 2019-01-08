// FindComponents.c - Finds the strongly connected components through DFS
// Chris Griffis <chdgriff>
// pa5

#include "Graph.h"
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Incorrect usage: %s <infile> <outfile>\n", argv[0]);
    exit(1);
  }

  FILE *in, *out;
  int order, u, v; //inputs from input file
  char line[MAX_LEN]; // Holds each line of input file
  char *token; // holds number
  Graph G, Gt;
  List S; // holds values needed to calculate each path
  List* Str;
  int count; // count of strongly connected components

  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if (in == NULL) {
    printf("FindPath error: Cannot open %s for input\n", argv[1]);
    exit(1);
  }
  if (out == NULL) {
    printf("FindPath error: Cannot open %s for output\n", argv[2]);
    exit(1);
  }

  fgets(line, MAX_LEN, in); // gets first line
  order = atoi(line); // stores first line as int

  G = newGraph(order);

  while (fgets(line, MAX_LEN, in) != NULL) { // loops through each line
    token = strtok(line, " "); // reads first number
    u = atoi(token);
    token = strtok(NULL, " \n"); // reads second number
    v = atoi(token);

    if (u == 0) break; // stops when 0 0 is reached
    addArc(G, u, v);
  }

  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);

  // initializes list S in number order
  S = newList();
  for (int i = 1; i <= getOrder(G); i++) append(S, i);

  // Finds stack of strongly connected components
  DFS(G, S);
  Gt = transpose(G);
  DFS(Gt, S);

  // Counts strongly connected components
  count = 0;
  moveFront(S);
  while (index(S) != -1) {
    if (getParent(Gt, get(S)) == NIL) count++;

    moveNext(S);
  }

  // allocates and initializes strongly connected components holder
  Str = malloc(count*sizeof(List)); // allocated memory to hold components
  for (int i = 0; i < count; i++) Str[i] = newList(); // initializes each list

  count = 0;
  moveBack(S); // Starts from end of stack
  while (index(S) != -1) {
    prepend(Str[count], get(S)); // prepends each connected component

    if (getParent(Gt, get(S)) == NIL) count++; // increases count when at root
    movePrev(S);
  }

  // Prints S.C.C.
  fprintf(out, "\nG contains %d strongly connected components:\n", count);
  for (int i = 0; i < count; i++) {
    fprintf(out, "Component %d: ", i+1);
    printList(out, Str[i]);
    fprintf(out, "\n");
  }

  // frees and closes files
  for (int i = 0; i < count; i++) freeList(&(Str[i]));
  free(Str);
  freeList(&S);
  freeGraph(&Gt);
  freeGraph(&G);
  fclose(in);
  fclose(out);
  return 0;
}


