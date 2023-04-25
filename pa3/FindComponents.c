/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#3
* FindComponents.c
* main file
*********************************************************************************/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 300
#define UNDEF -100
#define NIL 0


int main(int argc, char *argv[]) {
  int line_count;
  FILE *in, *out;
  char line[MAX_LEN];


  if (argc != 3) {
    fprintf(stderr, "Usage: <input file> <output file\n");
    exit(EXIT_FAILURE);
  }
  in = fopen(argv[1], "r");

  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  out = fopen(argv[2], "w");

  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  line_count = 0;
  while (fgets(line, MAX_LEN, in) != NULL) {
    line_count++;
  }
  rewind(in);




  int vcount = 0;
  fscanf(in, "%d", (&vcount));
  Graph G = newGraph(vcount);
  int vfirst;
  int vsec;
  int trash = 1;

  for (trash = 1; trash < line_count; trash++) {
    fscanf(in, "%d %d", &vfirst, &vsec);

    if ((vfirst <= (getOrder(G))) && (vfirst > 0) && (vsec <= (getOrder(G))) && (vsec > 0)) {
      addArc(G, vfirst, vsec);
    } 
    else if (vfirst == 0 && vsec == 0) {
      break;
    }
  }



  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");



  // initializing stack
  List stack = newList();
  for (int i = 1; i < (getOrder(G) + 1); i++) {
    append(stack, i);
  }
  DFS(G, stack);

  Graph transposed = transpose(G);

  // DFS to get new stack
  DFS(transposed, stack);



  int counter = 0;


  List *scc = (List *)malloc(sizeof(List) * (getOrder(G) + 1));
  moveBack(stack);

  scc[counter] = newList();
  for (int j = 0; j < length(stack); j++) {

    if (getParent(transposed, get(stack)) != NIL) {
      append(scc[counter], get(stack));
    }
    if (getParent(transposed, get(stack)) == NIL) {
      append(scc[counter], get(stack));
      counter++;
      scc[(counter)] = newList();
    }

    movePrev(stack);
  }



  fprintf(out, "G contains %d strongly connected components: \n", counter);
  for (int i = 0; i < counter; i++) {
    moveBack(scc[i]);
    fprintf(out, "Component %d:", (i + 1));

    for (int k = 0; k < length(scc[i]); k++) {
      fprintf(out, " %d", get(scc[i]));
      movePrev(scc[i]);
    }

    fprintf(out, "\n");
  }

 
 
  fclose(in);
  fclose(out);



  // Free memory
  for (int l = 0; l < (getOrder(G) + 1); l++) {
    freeList(&(scc[l]));
  }
  free(scc);
  scc = NULL;
  freeList(&stack);
  freeGraph(&G);
  return 0;
}






