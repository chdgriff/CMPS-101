// Graph.c - Implements DFS version of Graph ADT
// Chris Griffis <chdgriff>
// pa5

#include "Graph.h"
#include <stdlib.h>

// private declarations and helper methods
typedef struct GraphObj {
  int order;
  int size;

  List* vertex;
  char* color;
  int* discover;
  int* finish;
  int* parent;
} GraphObj;

// Inserts an edge into correct location
void insertEdge(Graph G, int u, int v) {
  if(length(G->vertex[u]) == 0) { // when list is empty
    prepend(G->vertex[u], v);
    G->size++;
  }
  else { // when list has at least one element
    if (index(G->vertex[u]) == -1) moveFront(G->vertex[u]); // defines cursor if undefined

    while (index(G->vertex[u]) != -1) {
      if (v < get(G->vertex[u])) { // when new vertex is less then cursor
        if (index(G->vertex[u]) == 0) { // when at front
          prepend(G->vertex[u], v);
          G->size++;
          break;
        }
        else {
          movePrev(G->vertex[u]);
          if (v > get(G->vertex[u])) { // when greater then previous
            insertAfter(G->vertex[u], v);
            G->size++;
            break;
          }
        }
      }
      else if (v > get(G->vertex[u])) { // when new vertex is more then cursor
        if (index(G->vertex[u]) == length(G->vertex[u])-1) { // when at back
          append(G->vertex[u], v);
          G->size++;
          break;
        }
        else {
          moveNext(G->vertex[u]);
          if ( v < get(G->vertex[u])) { // when less than next
            insertBefore(G->vertex[u], v);
            G->size++;
            break;
          }
        }
      }
      else { // if duplicate
        break;
      }
    }
  }
}

// recursive method to visit all vertex children
void visit(Graph G, List S, int u, int *time) {
  (*time)++;
  G->discover[u] = *time;
  G->color[u] = 'G';

  moveFront(G->vertex[u]);
  while (index(G->vertex[u]) != -1) {
    if (G->color[get(G->vertex[u])] == 'W') {
      G->parent[get(G->vertex[u])] = u;
      visit(G, S, get(G->vertex[u]), time);
    }
    moveNext(G->vertex[u]);
  }

  G->color[u] = 'B';
  (*time)++;
  G->finish[u] = *time;
  insertAfter(S, u);
}

// constructor
Graph newGraph(int n) {
  Graph G;

  G = malloc(sizeof(GraphObj));

  G->order = n++;
  G->size = NIL;
  // Allocates memory for each array
  G->vertex = malloc(n*sizeof(List));
  G->color = malloc(n*sizeof(int));
  G->discover = malloc(n*sizeof(int));
  G->finish = malloc(n*sizeof(int));
  G->parent = malloc(n*sizeof(int));

  // Sets default value and initializes each list
  for (int i = 1; i <= getOrder(G); i++) {
    G->vertex[i] = newList();
    G->color[i] = 'W';
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
    G->parent[i] = NIL;
  }
  return G;
}

// deconstructor
void freeGraph(Graph* pG) {
  if (pG == NULL) {
    printf("Graph error: Calling freeGraph() on NULL Graph pointer value\n");
    exit(1);
  }
  else if (*pG == NULL) {
    printf("Graph error: Calling freeGraph() on NULL Graph reference\n");
    exit(1);
  }

  for(int i = 1; i <= getOrder(*pG); i++) freeList(&((*pG)->vertex[i]));

  free((*pG)->vertex);
  free((*pG)->color);
  free((*pG)->discover);
  free((*pG)->finish);
  free((*pG)->parent);

  free(*pG);
  pG = NULL;
}

// Getter methods
int getOrder(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling getOrder() on NULL Graph reference\n");
    exit(1);
  }
  return G->order;
}

int getSize(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling getSize() on NULL Graph reference\n");
    exit(1);
  }
  return G->size;
}

int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("Graph error: Calling getParent() on NULL Graph reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling getParent() on out of bounds value u: %d\n", u);
    exit(1);
  }
  return G->parent[u];
}

int getDiscover(Graph G, int u) {
  if (G == NULL) {
    printf("Graph error: Calling getDiscover() on NULL Graph reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling getDiscover() on out of bounds value u: %d\n", u);
    exit(1);
  }
  return G->discover[u];
}

int getFinish(Graph G, int u) {
  if (G == NULL) {
    printf("Graph error: Calling getFinish() on NULL Graph reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling getFinish() on out of bounds value u: %d\n", u);
    exit(1);
  }
  return G->finish[u];
}

// Adds arcs or edges using helper method
void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    printf("Graph error: Calling addArc() on NULL Graph reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling addArc() on out of bounds value u: %d\n", u);
    exit(1);
  }
  else if (v < 1 || v > getOrder(G)) {
    printf("Graph error: Calling addArc() on out of bounds value v: %d\n", v);
    exit(1);
  }

  insertEdge(G, u, v);
}

void addEdge(Graph G, int u, int v) {
  if (G == NULL) {
    printf("Graph error: Calling addEdge() on NULL Graph reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling addEdge() on out of bounds value u: %d\n", u);
    exit(1);
  }
  else if (v < 1 || v > getOrder(G)) {
    printf("Graph error: Calling addEdge() on out of bounds value v: %d\n", v);
    exit(1);
  }

  insertEdge(G, u, v);
  insertEdge(G, v, u);
  G->size--; // fixes double edge size count
}

// Finds DFS using input stack and outputing to that stack
void DFS(Graph G, List S) {
  if (G == NULL) {
    printf("Graph error: Calling DFS() on NULL Graph reference\n");
    exit(1);
  }
  else if (S == NULL) {
    printf("Graph error: Calling DFS() on NULL List reference\n");
    exit(1);
  }
  else if (length(S) != getOrder(G)) {
    printf("Graph error: Calling DFS() when List S isn't of length %d\n", getOrder(G));
    exit(1);
  }
  int time;

  for (int i = 1; i <= getOrder(G); i++) {
    G->color[i] = 'W';
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
    G->parent[i] = NIL;
  }
  time = 0;

  moveBack(S);

  while(index(S) != -1) {
    if (G->color[front(S)] == 'W') visit(G, S, front(S), &time);

    deleteFront(S);
  }
}

// transposes to a new graph
Graph transpose(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling transpose() on NULL Graph reference\n");
    exit(1);
  }

  Graph nG;

  nG = newGraph(getOrder(G));

  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(G->vertex[i]);
    while (index(G->vertex[i]) != -1) {
      addArc(nG, get(G->vertex[i]), i);

      moveNext(G->vertex[i]);
    }
  }
  return nG;
}

// copies graph
Graph copyGraph(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling transpose() on NULL Graph reference\n");
    exit(1);
  }

  Graph nG;

  nG = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(G->vertex[i]);
    while (index(G->vertex[i]) != -1) {
      addArc(nG, i, get(G->vertex[i]));

      moveNext(G->vertex[i]);
    }
  }
  return nG;
}

void printGraph(FILE* out, Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling printGraph() on NULL Graph reference\n");
    exit(1);
  }

  for (int i = 1; i <= getOrder(G); i++) {
   // if (i > 1) fprintf(out, "\n"); // prints to next line when not line 1

    fprintf(out, "%d:", i); // prints vertex

    if (length(G->vertex[i]) > 0) {// prints adjacency list if not empty
      fprintf(out, " ");
      printList(out, G->vertex[i]);
    }
    fprintf(out, "\n");
  }
}
