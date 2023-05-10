/*********************************************************************************
 * Vara Neha Madem, vmadem
 * 2023 Spring CSE101 PA4
 * Sparse.c
 * main file
 *********************************************************************************/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Matrix.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {
  int line_count;
  FILE *in, *out;
  char line[MAX_LEN];
  char ignore[MAX_LEN];
 



  if (argc != 3) {
    fprintf(stderr, "Usage: <input file> <output file>\n");
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




  int msize = 0;
  int nnzA = 0;
  int nnzB = 0;
  fscanf(in, "%d %d %d", (&msize), (&nnzA), (&nnzB));
  Matrix A = newMatrix(msize);
  Matrix B = newMatrix(msize);

  fgets(ignore, MAX_LEN, in);

  int row = 0;
  int col = 0;
  double val = 0.0;

  for (int i = 0; i < nnzA; i++) {
    fscanf(in, "%d %d %lf", (&row), (&col), (&val));
    changeEntry(A, row, col, val);
  }
  
  fgets(ignore, MAX_LEN, in);



//b
  for (int j = 0; j < nnzA; j++) {
    fscanf(in, "%d %d %lf", (&row), (&col), (&val));
    changeEntry(B, row, col, val);
  }




//print
  fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
  printMatrix(out, A);
  fprintf(out, "\n");
  fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
  printMatrix(out, B);
  fprintf(out, "\n");

  // 1.5 Scalar Multiplication
  fprintf(out, "(1.5)*A =\n");
  Matrix C = scalarMult(1.5, A);
  printMatrix(out, C);
  fprintf(out, "\n");

  // A + B 
  fprintf(out, "A+B =\n");
  Matrix D = sum(A, B);
  printMatrix(out, D);
  fprintf(out, "\n");

  // A + A 
  fprintf(out, "A+A =\n");
  Matrix E = sum(A, A);
  printMatrix(out, E);
  fprintf(out, "\n");

  // B - A 
  fprintf(out, "B-A =\n");
  Matrix F = diff(B, A);
  printMatrix(out, F);
  fprintf(out, "\n");

  // A - A
  fprintf(out, "A-A =\n");
  Matrix G = diff(A, A);
  printMatrix(out, G);
  fprintf(out, "\n");

  //A transpose
  fprintf(out, "Transpose(A) =\n");
  Matrix H = transpose(A);
  printMatrix(out, H);
  fprintf(out, "\n");

  // A * B 
  fprintf(out, "A*B =\n");
  Matrix I = product(A, B);
  printMatrix(out, I);
  fprintf(out, "\n");

  // B * B 
  fprintf(out, "B*B =\n");
  Matrix J = product(B, B);
  printMatrix(out, J);




  fclose(in);
  fclose(out);

  // Freeing Matrices
  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&E);
  freeMatrix(&F);
  freeMatrix(&G);
  freeMatrix(&H);
  freeMatrix(&I);
  freeMatrix(&J);
  return 0;
}



