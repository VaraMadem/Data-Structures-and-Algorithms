/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#2
* FindPath.c
* main file
*********************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 1024


int main(int argc, char * argv[]){

   FILE *in, *out;
   int vertices;
   if(argc != 3){
      fprintf(stderr, "Usage: %s <input file> <outputfile>\n",argv[0]);
      return EXIT_FAILURE;
   }


   in = fopen(argv[1], "r");
   if(in == NULL){
      fprintf(stderr, "ERROR: Unable to open file: %s for reading\n",argv[1]);
      return EXIT_FAILURE;
   }
   out = fopen(argv[2], "w");
   if(out == NULL){
      fprintf(stderr, "ERROR: Unable to open file: %s for writing\n",argv[2]);
      return EXIT_FAILURE;
   }




   //vertices
   char buffer[MAX_LEN];
   if ((fgets(buffer, MAX_LEN, in)) == NULL){
      fprintf(stderr,"ERROR: Bad Read of the number of vertices\n");
      return EXIT_FAILURE;
   }

   buffer[strlen(buffer) - 1] = '\0';
   vertices = strtol(buffer, NULL, 10);
   

  


   List L = newList();
   Graph G = newGraph(vertices);
   int v,u;
   int input;
   u = v = -1;


   
   while (v != 0 && u != 0){
      if((input = fscanf(in, "%d %d\n", &u, &v)) != EOF){ 
         if(input == 0){
            fprintf(stderr, "Malformed line while reading vertices\n");
            return EXIT_FAILURE;
         }

         if( u != 0 && v != 0){
            addEdge(G,u,v);
         }
      }
   }
   printGraph(out, G);
   fprintf(out,"\n");

   

   //shortest path
   u = v = -1;

   while(v != 0 && u != 0){

      if((input = fscanf(in, "%d %d\n", &u, &v)) != EOF){
         if(input == 0){
            fprintf(stderr, "Malformed line while reading source and destination\n");
            return EXIT_FAILURE;
         }


         if(u != 0 && v != 0){
            BFS(G, u);
            getPath(L, G, v);

            if(getDist(G,v) != INF){ 
               fprintf(out,"The distance from %d to %d is %d\n", u, v, getDist(G,v));
               fprintf(out,"A shortest %d-%d path is: ",u, v);
               printList(out, L);
               fprintf(out,"\n\n");
            } 
            else {
               fprintf(out,"The distance from %d to %d is infinity\n", u, v);
               fprintf(out,"No %d-%d path exists",u, v);
               fprintf(out,"\n\n");
            }
         }

         clear(L);


      }
   }

 

   freeGraph(&G);
   freeList(&L);
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}





