/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#3
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


// structs
typedef struct GraphObj *Graph;


typedef struct GraphObj {
  int size;
  int *parent;
  int *discover;
  int *finish;
  int order;
  List *neighbors;
  int *color;
  int time;
} GraphObj;




// Constructors-Destructors ---------------------------------------------------


// Graph newGraph(int n);
Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj));
 
  G->size = 0;
  G->time = 0;
  G->order = n;
  G->parent = (int *)malloc(sizeof(int) * (G->order + 1));
  G->finish = (int *)malloc(sizeof(int) * (G->order + 1));
  G->discover = (int *)malloc(sizeof(int) * (G->order + 1));
  G->neighbors = (List *)malloc(sizeof(List) * (G->order + 1));
  G->color = (int *)malloc(sizeof(int) * (G->order + 1));

  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->neighbors[i] = newList();
    G->color[i] = 0;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
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
    free((*pG)->neighbors);
    (*pG)->neighbors = NULL;
    free((*pG)->color);
    (*pG)->color = NULL;
    free((*pG)->discover);
    (*pG)->discover = NULL;
    free((*pG)->finish);
    (*pG)->finish = NULL;
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



// int getParent(Graph G, int u);
int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("Error in Graph ADT: getParent(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u > (G->order + 1)) || (u < 1)) {
    printf("Error in Graph ADT: getParent()");
    exit(EXIT_FAILURE);
  }
  
  return G->parent[u];
}



/* Pre: 1<=u<=n=getOrder(G) */
//int getDiscover(Graph G, int u); 
int getDiscover(Graph G, int u) {
  if (G == NULL) {
    printf("Error in Graph ADT, getDiscover(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((1 <= u) && (u <= (getOrder(G) + 1))) {
    return G->discover[u];
  } 
  else {
    exit(EXIT_FAILURE);
  }
}



/* Pre: 1<=u<=n=getOrder(G) */
//int getFinish(Graph G, int u); 
int getFinish(Graph G, int u) {
  if (G == NULL) {
    printf("Error in Graph ADT, getDiscover(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((1 <= u) && (u <= (getOrder(G) + 1))) {
    return G->finish[u];
  } 
  else {
    exit(EXIT_FAILURE);
  }
}





// Manipulation procedures ----------------------------------------------------


/* Pre: 1<=u<=n, 1<=v<=n */
//void addArc(Graph G, int u, int v);  
void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    printf("Error in Graph ADT: addArc(), G is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u < 1) || (v < 1) || (u > (getOrder(G) + 1)) || (v > (getOrder(G) + 1))) { 
    printf("Error in Graph ADT: addArc() ");
    exit(EXIT_FAILURE);
  }

  List adj = G->neighbors[u];
  moveFront(adj);
  for (int i = 0; i < length(adj); i++) {
    if (get(adj) == v) {
      break;
    }
    moveNext(adj);
  }

  // insertion
  if (length(G->neighbors[u]) == 0) {
    append(G->neighbors[u], v);
    G->size++;
  } 
  else {
    moveBack(G->neighbors[u]);
    while (index(G->neighbors[u]) != -1) {

      if (v == get(G->neighbors[u])) {
        return;
      } 
      else if (v < get(G->neighbors[u])) {
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




// Visit() - recursive segment of DFS - changes color
void Visit(Graph G, List stack, int x) {
  G->discover[x] = ++(G->time); 
  //grey
  G->color[x] = 1; 
  List adj = G->neighbors[x];

  moveFront(adj); // least to greatest DFS
  for (int i = 0; i < length(adj); i++) {
    if (G->color[get(adj)] == 0) {
      G->parent[get(adj)] = x; 
      Visit(G, stack, get(adj)); //recursive
    }

    moveNext(adj); 
  }
  //black
  G->color[x] = 2;  
  prepend(stack, x); 
  G->finish[x] = ++(G->time);
}




/* Pre: length(S)==getOrder(G) */
//void DFS(Graph G, List S);
void DFS(Graph G, List S) {
  if (G == NULL) {
    printf("Error in Graph ADT: DFS(), G is NULL");
    exit(EXIT_FAILURE);
  }
  if (S == NULL) {
    printf("Error in Graph ADT: DFS(), S is NULL");
  }
  if (length(S) != getOrder(G)) {
    printf("Error in Graph ADT: DFS()");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->color[i] = 0;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }

  G->time = 0;
  int stlen = length(S);
  moveFront(S);

  for (int i = 0; i < stlen; i++) { 
    if (G->color[get(S)] == 0) {
      Visit(G, S, get(S));
    }
    moveNext(S);
  }
  for (int j = 0; j < stlen; j++) {
    moveBack(S); 
    delete (S);
  }
}




// Other operations -----------------------------------------------------------

//Graph transpose(Graph G);
Graph transpose(Graph G) {
  if (G == NULL) {
    printf("Error in Graph ADT: transpose(), G is NULL!");
    exit(EXIT_FAILURE);
  }
  
  Graph transposed = newGraph(getOrder(G));
  List adj = newList();
  int a = 0;

  for (int i = 1; i < (getOrder(G) + 1); i++) {
    adj = G->neighbors[i];
    moveFront(adj);

    for (int j = 0; j < length(adj); j++) {
      a = get(adj);
      addArc(transposed, a, i);
      moveNext(adj);
    }
  }
  return transposed;
}




//Graph copyGraph(Graph G);
Graph copyGraph(Graph G) {
  if (G == NULL) {
    printf("Error in Graph ADT: copyGraph(), G is NULL");
    exit(EXIT_FAILURE);
  }
  Graph copy = newGraph(getOrder(G));
  List adj = newList();
  int a = 0;
  
  for (int i = 1; i < (getOrder(G) + 1); i++) {
    adj = G->neighbors[i];
    moveFront(adj);
    for (int j = 0; j < length(adj); j++) {
      a = get(adj);
      addArc(copy, i, a);
      moveNext(adj);
    }
  }
  return copy;
}



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








