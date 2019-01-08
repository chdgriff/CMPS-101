// Graph.c - implementation of Graph ADT
// Chris Griffis <chdgriff>
// pa4

#include "Graph.h"

// private helper
typedef struct GraphObj {
  int order; // number of vertices
  int size; // number of edges
  int source; // last vertex used as source

  List *vertex; // adjacency list
  char *color; // color array
  int *parent; // parent array
  int *distance; // distance from source

} GraphObj;

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

// constructor and deconstructor
Graph newGraph(int n) {
  Graph G;

  G = malloc(sizeof(GraphObj));
  G->order = n++; // fixes off by 1 error by incrementing n post assignment
  G->size = 0;
  G->source = NIL;

  G->vertex = malloc(n*sizeof(List));
  G->color = malloc(n*sizeof(char));
  G->parent = calloc(n, sizeof(int)); // sets all parent values to NIL aka 0
  G->distance = malloc(n*sizeof(int));

  for (int i = 1; i < n;  i++) {
    G->vertex[i] = newList(); // initializes all lists
    G->color[i] = 'w'; // sets all colors to white
    G->distance[i] = INF; // sets all distance to INF
    G->parent[i] = NIL; // sets all parent to NIL
  }

  return G;
}

void freeGraph(Graph* pG) {
  for (int i = 1; i < getOrder(*pG)+1; i++) freeList(&(*pG)->vertex[i]); // frees each list
  free((*pG)->vertex);
  free((*pG)->color);
  free((*pG)->parent);
  free((*pG)->distance);
  free(*pG);
  pG = NULL;
}

// access methods
int getOrder(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling getOrder() on NULL reference\n");
    exit(1);
  }
  return G->order;
}

int getSize(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling getSize() on NULL reference\n");
    exit(1);
  }
  return G->size;
}

int getSource(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling getSource() on NULL reference\n");
    exit(1);
  }
  return G->source;
}

int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("Graph error: Calling getParent() on NULL reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling getParent() on non valid vertex u\n");
    exit(1);
  }
  return G->parent[u];
}

int getDist(Graph G, int u) {
  if (G == NULL) {
    printf("Graph error: Calling getDist() on NULL reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling getDist() on non valid vertex u");
    exit(1);
  }
  return G->distance[u];
}

void getPath(List L, Graph G, int u) {
  if (G == NULL) {
    printf("Graph error: Calling getPath() on NULL reference\n");
    exit(1);
  }
  else if (u < 1 || u > getOrder(G)) {
    printf("Graph error: Calling getPath() on non valid vertex u\n");
    exit(1);
  }
  else if (getSource(G) == NIL) {
    printf("Graph error: Calling getSource() when BFS() not called\n");
    exit(1);
  }

  if (L == NULL) {
    printf("Graph error: Calling getPath() on NULL reference list\n");
    exit(1);
  }
  int p;

  p = G->parent[u];
  if (u == getSource(G)) { // when u is source
    append(L, u);
  }
  else if (p == NIL) { // when there is no parent
    prepend(L, p);
  }
  else { // other cases
    prepend(L, u);
    while (p != NIL) { // loops up to each parent until source
      prepend(L, p);
      p = G->parent[p];
    }
  }
}

// Manipulation methods
void makeNull(Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling makeNULL() on NULL reference\n");
    exit(1);
  }

  G->size = 0;
  G->source = NIL;

  for (int i = 1; i < getOrder(G)+1; i++) { // clears and resets each array
    clear(G->vertex[i]);
    G->color[i] = 'w';
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
}

void addEdge(Graph G, int u, int v) {
  if (G == NULL) {
    printf("Graph error: Calling addEdge() on NULL reference\n");
    exit(1);
  }

  insertEdge(G, u, v);
  insertEdge(G, v, u);
  G->size--; // fixes double edge size count
}
void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    printf("Graph error: Calling addArc() on NULL reference\n");
    exit(1);
  }

  insertEdge(G, u, v);
}
void BFS(Graph G, int s) {
  if (G == NULL) {
    printf("Graph error: Calling BFS() on NULL reference\n");
    exit(1);
  }
  List queue;
  int x, y;

  for(int i = 1; i < getOrder(G)+1; i++) { // resets color distance and parent for each vertex
    G->color[i] = 'w';
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }

  queue = newList();

  // sets source attributes
  G->source = s;
  G->color[s] = 'g';
  G->distance[s] = NIL;
  append(queue, s);

  while (length(queue) != 0) {
    // dequeue
    x = front(queue);
    deleteFront(queue);
    //printf("%d ", x); prints queue

    moveFront(G->vertex[x]);
    while (index(G->vertex[x]) != -1) { // loops through each edge
      y = get(G->vertex[x]);
      if (G->color[y] == 'w') { // if not visited
        G->color[y] = 'g';
        G->distance[y] = G->distance[x] + 1;
        G->parent[y] = x;
        append(queue, y);
      }
      moveNext(G->vertex[x]); // moves to next vertex
    }
    G->color[x] = 'b';
  }
  //printf("\n"); // formating for printing queue
  freeList(&queue);
}
void printGraph(FILE* out, Graph G) {
  if (G == NULL) {
    printf("Graph error: Calling printGraph() on NULL reference\n");
    exit(1);
  }

  for (int i = 1; i < getOrder(G)+1; i++) {
    if (i != 1) fprintf(out, "\n");
    fprintf(out, "%d:", i); // prints vertex label
    if (length(G->vertex[i]) != 0) { // prints list of vertices
      fprintf(out, " ");
      printList(out, G->vertex[i]);
    }
  }
}
