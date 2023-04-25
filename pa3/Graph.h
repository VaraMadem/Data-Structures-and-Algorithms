/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#3
* Graph.h
*********************************************************************************/ 
//#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "List.h"


#define UNDEF -100
#define NIL 0

typedef struct GraphObj *Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
/* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph G, int u);
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); 
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); 

// Manipulation procedures ----------------------------------------------------
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v);  
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); 
/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S);           

// Other operations -----------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);

