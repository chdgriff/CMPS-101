// FindPath.c - reads and reads an adjacency list using List and Graph ADTs to find various paths
// Chris Griffis <chdgriff>
// pa4

#include "Graph.h"
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("FindPath error: Usage %s input_file output_file\n", argv[0]);
    exit(1);
  }

  FILE *in, *out;
  int order, u, v; //inputs from input file
  char line[MAX_LEN]; // Holds each line of input file
  char *token; // holds number
  List source, destination, path; // holds values needed to calculate each path

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
  order = atoi(line); // stores first line ast int

  Graph G = newGraph(order);

  while (fgets(line, MAX_LEN, in) != NULL) { // loops through each line
    token = strtok(line, " "); // reads first number
    u = atoi(token);
    token = strtok(NULL, " \n"); // reads second number
    v = atoi(token);

    if (u == 0) break; // stops when 0 0 is reached
    addEdge(G, u, v);
  }

  source = newList(); // holds all sources to calculate BFS on
  destination = newList(); // holds all destinations which path is to be found

  while (fgets(line, MAX_LEN, in) != NULL) { // loops through rest of file
    token = strtok(line, " ");
    u = atoi(token);
    token = strtok(NULL, " \n");
    v = atoi(token);

    if (u == 0) break; // stops when 0 0 is reached
    append(source, u);
    append(destination, v);
  }

  printGraph(out, G);
  fprintf(out, "\n");

  path = newList();

  moveFront(source);
  moveFront(destination);

  while (index(source) != -1) { // Loops through each value in list source
    BFS(G, get(source));
    getPath(path, G, get(destination));

    fprintf(out, "\nThe distance from %d to %d is ", getSource(G), get(destination));
    if (getDist(G, get(destination)) == -1) { // when no distance and path
      fprintf(out, "infinity\n");
      fprintf(out, "No %d-%d path exists", get(source), get(destination));
    }
    else {
      fprintf(out, "%d\n", getDist(G, get(destination)));
      fprintf(out, "A shortest %d-%d path is: ", get(source), get(destination));
      printList(out, path);
    }
    fprintf(out, "\n");

    clear(path);
    moveNext(source);
    moveNext(destination);
  }

  // frees all allocated memory
  freeList(&source);
  freeList(&destination);
  freeList(&path);
  freeGraph(&G);
  fclose(in);
  fclose(out);

  return 0;
}
