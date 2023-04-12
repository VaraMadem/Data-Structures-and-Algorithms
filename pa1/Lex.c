/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#1
* Lex.c
* main file
*********************************************************************************/ 


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_LEN 300



int main(int argc, char *argv[]) {
  int counter = 0;
  FILE *in, *out;
  char line[MAX_LEN];


  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
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


  while (fgets(line, MAX_LEN, in) != NULL) {
    counter++;
  }
  rewind(in);



 
  char **astring = (char **)calloc(counter, sizeof(char *));
  for (int i = 0; i < counter; i++) {

    fgets(line, MAX_LEN, in);
    astring[i] = (char *)calloc(strlen(line), sizeof(char));
    strcpy(astring[i], line);
  }
  
  List L = newList();
  append(L, 0);
  for (int i = 1; i < counter; i++) {

    moveBack(L);
    int compare = get(L);

    while ((index(L) != -1) && (strcmp(astring[compare], astring[i]) > 0)) {
      movePrev(L);
      if (index(L) == -1) {
        break;
      }
      compare = get(L);
    }

    if (index(L) == -1) { 
      prepend(L, i);
    } 
    else {
      insertAfter(L, i);
    }
  }


  moveFront(L);
  int n = 0;
  for (int i = 0; i < counter; i++) {
    n = get(L);
    fprintf(out, "%s", astring[n]);
    moveNext(L);
  }

 
  for (int i = 0; i < counter; i++) {
    free(astring[i]);
  }
  free(astring);

  freeList(&L);




  fclose(in);
  fclose(out);
  return (EXIT_SUCCESS);
}






