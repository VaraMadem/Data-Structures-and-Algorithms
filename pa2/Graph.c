/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#2
* Graph.c
* Graph ADT
*********************************************************************************/  

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"


//structs
typedef struct GraphObj *Graph;


typedef struct GraphObj {
  int source;
  int size;
  int order;
  int *parent;
  int *distance;
  List *neighbors;
  int *color;
} GraphObj;




// Constructors-Destructors ---------------------------------------------------


// Graph newGraph(int n);
Graph newGraph(int n) {

  Graph G = malloc(sizeof(GraphObj));
  
  G->source = NIL;
  G->size = 0;
  G->order = n;
  G->parent = (int *)malloc(sizeof(int) * (G->order + 1));
  G->distance = (int *)malloc(sizeof(int) * (G->order + 1));
  G->neighbors = (List *)malloc(sizeof(List) * (G->order + 1));
  G->color = (int *)malloc(sizeof(int) * (G->order + 1));

  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->distance[i] = INF;
    G->neighbors[i] = newList();
    G->color[i] = 0;
  }
  return G;
}




// void freeGraph(Graph* pG);
void freeGraph(Graph *pG) {
  if ((pG != NULL) && (*pG != NULL)) {
    
    for (int i = 1; i < ((*pG)->order + 1); i++) {
      freeList(&((*pG)->neighbors[i]));
    }
    free((*pG)->parent);
    (*pG)->parent = NULL;
    free((*pG)->distance);
    (*pG)->distance = NULL;
    free((*pG)->neighbors);
    (*pG)->neighbors = NULL;
    free((*pG)->color);
    (*pG)->color = NULL;
    free((*pG));
    (*pG) = NULL;
    pG = NULL;
  }
}




// Access functions -----------------------------------------------------------


// int getOrder(Graph G);
int getOrder(Graph G) {
  if (G == NULL) {
    exit(EXIT_FAILURE);
  }
  return G->order;
}



// int getSize(Graph G);
int getSize(Graph G) {
  if (G == NULL) {
    exit(EXIT_FAILURE);
  }
  return G->size;
}



//int getSource(Graph G);
int getSource(Graph G) {
  if (G == NULL) {
    exit(EXIT_FAILURE);
  }
  return G->source;
}



// int getParent(Graph G, int u);
int getParent(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: getParent(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u > (G->order + 1)) || (u < 1)) {
    printf("Error in Graph ADT: getParent()");
    exit(EXIT_FAILURE);
  }
  
  return G->parent[u];
}



//int getDist(Graph G, int u);
int getDist(Graph G, int u) {
  if (G == NULL) {
    printf("Error in Graph ADT: getDist(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u > (G->order + 1)) || (u < 1)) {
    printf("Error in Graph ADT: getDist()");
    exit(EXIT_FAILURE);
  }

  return G->distance[u];
}




// void getPath(List L, Graph G, int u);
void getPath(List L, Graph G, int u) {
  if (G == NULL) {
    printf("Error in Graph ADT: getPath(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if (u > G->order || u < 1) {
    printf("Error in Graph ADT: getPath(), vertex out of bounds");
    exit(EXIT_FAILURE);
  }

  if (getSource(G) == u) {
    append(L, u);
  } 
  else if (G->parent[u] == NIL) {
    append(L, NIL);
  } 
  else {
    getPath(L, G, G->parent[u]);
    append(L, u);
  }
}




// Manipulation procedures ----------------------------------------------------

// void makeNull(Graph G);
void makeNull(Graph G) {
  if (G == NULL) {
    printf("Error in Graph ADT: makeNull(), graph is NULL.");
    exit(EXIT_FAILURE);
  }
  G->size = 0;
  G->source = NIL;

  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->distance[i] = INF;
    clear(G->neighbors[i]);
    G->color[i] = 0;
  }
}




// void addEdge(Graph G, int u, int v);
void addEdge(Graph G, int u, int v) {
  if (G == NULL) {
    printf("Error in Graph ADT: addEdge(), G is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u < 1) || (v < 1) || (u > (getOrder(G) + 1)) || (v >= (getOrder(G) + 1))) { 
    printf("u: %d, v: %d\n", u, v);
    printf("Error in Graph ADT: addEdge()");
    exit(EXIT_FAILURE);
  }

  addArc(G, u, v);
  addArc(G, v, u);
  G->size--; 
}





// void addArc(Graph G, int u, int v);
void addArc(Graph G, int u, int v) {

  if (G == NULL) {
    printf("Error in Graph ADT: addArc(), G is NULL.");
    exit(EXIT_FAILURE);
  }

  if ((u < 1) || (v < 1) || (u > (getOrder(G) + 1)) ||
      (v > (getOrder(G) + 1))) {
    printf("Error in Graph ADT: addArc()");
    exit(EXIT_FAILURE);
  }

  // insertion
  if (length(G->neighbors[u]) == 0) {
    append(G->neighbors[u], v);
    G->size++;
  } 
  else {
    moveBack(G->neighbors[u]);
    while (index(G->neighbors[u]) != -1) {

      if (v < get(G->neighbors[u])) {
        movePrev(G->neighbors[u]); 
      } 
      else {
        break;
      }
    }
    
    if (index(G->neighbors[u]) == -1) {
      prepend(G->neighbors[u], v);
      G->size++;
    } 
    else {
      insertAfter(G->neighbors[u], v);
      G->size++;
    }
  }
}





// void BFS(Graph G, int s);
void BFS(Graph G, int s) {
  if (G == NULL) {
    printf("Error in Graph ADT: BFS(), G is NULL");
    exit(EXIT_FAILURE);
  }
  if (s > (G->order + 1) || s < 1) {
    printf("Error in Graph ADT: BFS(), s is out of bounds");
    exit(EXIT_FAILURE);
  }

  // reset BFS just in case
  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->distance[i] = INF;
    G->color[i] = 0;
  }


  G->source = s;
  G->color[s] = 1;
  G->distance[s] = 0;
  G->parent[s] = NIL;
  List Q = newList();
  append(Q, s);
  int top = 0;


  while (length(Q) != 0) { 
    top = front(Q);
    List adj = G->neighbors[top];
    moveFront(adj);

    for (int i = 0; i < length(adj); i++) {
      if (G->color[get(adj)] == 0) { 
        G->color[get(adj)] = 1;      
        G->distance[get(adj)] = G->distance[top] + 1;
        G->parent[get(adj)] = top;
        append(Q, get(adj));
      }

      moveNext(adj);
    }

    G->color[top] = 2; 
    deleteFront(Q);    
  }
  freeList(&Q);
}





// Other operations -----------------------------------------------------------


// void printGraph(FILE* out, Graph G);
void printGraph(FILE *out, Graph G) {

  if (G == NULL) {
    printf("Error in Graph ADT: printList(), G appears to be NULL");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < (G->order + 1); i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->neighbors[i]);
    fprintf(out, "\n");
  }
}


