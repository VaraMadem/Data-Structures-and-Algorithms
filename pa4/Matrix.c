/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#4
* Matrix.c
* Matrix ADT
*********************************************************************************/
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Matrix.h"


//structs
typedef struct EntryObj *Entry;


typedef struct EntryObj {
  int col;
  double val;
} EntryObj;

typedef struct MatrixObj {
  int size;
  List *rows;
} MatrixObj;



// Constructors-Destructors ---------------------------------------------------


// newEntry() returns a new EntryObj with col and val
Entry newEntry(int column, double value) {
  Entry E = malloc(sizeof(EntryObj));
  E->col = column;
  E->val = value;
  return E;
}

void freeEntry(Entry *pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    *pE = NULL;
    pE = NULL; 
  }
}


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));
  if (M) {
    M->size = n;
    M->rows = (List *)malloc(sizeof(List) * (M->size + 1));
    for (int i = 1; i < (M->size + 1); i++) {
      M->rows[i] = newList();
    }
    return M;
  } 
  else {
    printf("Error in Matrix ADT: newMatrix(), not enough memory for M!\n");
    exit(EXIT_FAILURE);
  }
}


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM) {
  if (pM != NULL && *pM != NULL) {
    makeZero(*pM);
    for (int i = 1; i < ((*pM)->size + 1); i++) {
      freeList(&((*pM)->rows[i]));
    }
    free((*pM)->rows);
    (*pM)->rows = NULL;
    free(*pM);
    *pM = NULL;
  }
}


// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
  if (M == NULL) {
    printf("Error in Matrix ADT: size(), M is NULL!\n");
    exit(EXIT_FAILURE);
  }
  return M->size;
}



// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
  if (M == NULL) {
    printf("Error in Matrix ADT: NNZ(), M is NULL\n");
    exit(EXIT_FAILURE);
  }
  int nnz = 0;
  for (int i = 1; i < (size(M) + 1); i++) {
    if (length(M->rows[i]) != 0) {
      nnz += length(M->rows[i]);
    }
  }
  return nnz;
}



// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
  if (A == NULL && B == NULL) {
    return 1;
  }
  if (A == NULL) {
    printf("Error in Matrix ADT: equals(), A is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (B == NULL) {
    printf("Error in matrix ADT: equals(), B is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    return 0;
  }

  Matrix copyM = copy(B);

  for (int i = 1; i < (size(A) + 1); i++) {
    if (length(A->rows[i]) != length(copyM->rows[i])) {
      freeMatrix(&copyM);
      return 0;
    }
    moveFront(A->rows[i]);
    moveFront(copyM->rows[i]);

    while (index(A->rows[i]) != -1) {
      Entry AE = (Entry)get(A->rows[i]);
      Entry BE = (Entry)get(copyM->rows[i]);

      if ((AE->col != BE->col) || (AE->val != BE->val)) {
        freeMatrix(&copyM);
        return 0;
      }
      moveNext(A->rows[i]);
      moveNext(copyM->rows[i]);
    }
  }
  freeMatrix(&copyM);
  
  return 1;
}



// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
  if (M == NULL) {
    printf("Error in Matrix ADT: makeZero(), M is NULL!\n");
    exit(EXIT_FAILURE);

  }
  for (int i = 1; i < (size(M) + 1); i++) {
    moveFront(M->rows[i]);

    while (index(M->rows[i]) != -1) {
      Entry delete = (Entry)get(M->rows[i]);
      moveNext(M->rows[i]);
      freeEntry(&delete);
    }
    clear(M->rows[i]);
  }

}



// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
  if (M == NULL) {
    printf("Error in Matrix ADT: changeEntry(), M is NULL!\n");
    exit(EXIT_FAILURE);
  }
  if ((1 > i) || (i > size(M))) {
    printf("Error in Matrix ADT: changeEntry(), i (row) is out of bounds.\n");
    exit(EXIT_FAILURE);
  }
  if (j > size(M) || 1 > j) {
    printf("Error in Matrix ADT: changeEntry(), j (col) is out of bounds!\n");
    exit(EXIT_FAILURE);
  }
 
  if (length(M->rows[i]) == 0 && x != 0) {
    Entry E = newEntry(j, x);
    append(M->rows[i], E);
  } 
  else if (length(M->rows[i]) > 0) {
    moveBack(M->rows[i]);

    while (index(M->rows[i]) != -1) {
      Entry c = (Entry)get(M->rows[i]);

      if (j == c->col) {
        if (x == 0) {
          delete (M->rows[i]);
          freeEntry(&c);
          return;
        }
        c->val = x;
        return;
      } 
      else if (j < c->col) {
        movePrev(M->rows[i]);
      } 
      else {
        break;
      }
    }
 
    if (index(M->rows[i]) == -1) {
      Entry E = newEntry(j, x);
      prepend(M->rows[i], E);
      return;

    } 
    else if (x == 0) {
      return;
    } 

    else {
      Entry E = newEntry(j, x);
      insertAfter(M->rows[i], E);
      return;
    }
  }
}



// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
  if (A == NULL) {
    printf("Error in matrix ADT: copy(), M is NULL\n");
    exit(EXIT_FAILURE);
  }
  Matrix mat = newMatrix(A->size);
  for (int i = 1; i < (mat->size + 1); i++) {
    moveFront(A->rows[i]);
    while (index(A->rows[i]) != -1) {
      Entry E = (Entry)get(A->rows[i]);
      changeEntry(mat, i, E->col, E->val);
      moveNext(A->rows[i]);
    }
  }
  return mat;
}


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
  if (A == NULL) {
    printf("Error in Matrix ADT; transpose(), A is NULL\n");
    exit(EXIT_FAILURE);
  }
  
  Matrix mat = newMatrix(A->size);
  for (int i = 1; i < (mat->size + 1); i++) {
    moveFront(A->rows[i]);

    while (index(A->rows[i]) != -1) {
      Entry E = (Entry)get(A->rows[i]);

      changeEntry(mat, E->col, i, E->val);
      moveNext(A->rows[i]);
    }
  }
  
  return mat;
}



// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
  if (A == NULL) {
    printf("Error in Matrix ADT: scalarMult(), A is NULL!\n");
    exit(EXIT_FAILURE);
  }
  Matrix mat = newMatrix(A->size);
  if (x == 0) {
    return mat;
  }
  for (int i = 1; i < (mat->size + 1); i++) {
    moveFront(A->rows[i]);

    while (index(A->rows[i]) != -1) {
      Entry E = (Entry)get(A->rows[i]);

      double mult = x * E->val;
      changeEntry(mat, i, E->col, mult);
      moveNext(A->rows[i]);
    }
  }

  return mat;
}







// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Error in Matrix ADT: sum(), A or B is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Error in Matrix ADT: sum(), A and B do not have matching sizes!\n");
    exit(EXIT_FAILURE);
  }

  Matrix tempM = copy(B);
  Matrix mat = newMatrix(A->size);

  double newSum = 0.0; 

  for (int i = 1; i < (A->size + 1); i++) {
    moveFront(A->rows[i]);
    moveFront(tempM->rows[i]);
    if (length(A->rows[i]) == 0 && length(tempM->rows[i]) != 0) {

      while (index(tempM->rows[i]) != -1) {
        Entry EB = (Entry)get(tempM->rows[i]);

        changeEntry(mat, i, EB->col, EB->val);
        moveNext(tempM->rows[i]);
      }
    }

    if (length(tempM->rows[i]) == 0 && length(A->rows[i]) != 0) {

      while (index(A->rows[i]) != -1) {
        Entry EA = (Entry)get(A->rows[i]);
        changeEntry(mat, i, EA->col, EA->val);
        moveNext(A->rows[i]);
      }
    }
    while (index(A->rows[i]) != -1 || index(tempM->rows[i]) != -1) {
      if (index(A->rows[i]) != -1 && index(tempM->rows[i]) != -1) {
        Entry EA = (Entry)get(A->rows[i]);
        Entry EB = (Entry)get(tempM->rows[i]);

        if (EA->col == EB->col) {
          newSum = EA->val + EB->val;
          if (newSum != 0) {
            changeEntry(mat, i, EA->col, newSum);
          }
          moveNext(A->rows[i]);
          moveNext(tempM->rows[i]);
        } 
        else if (EA->col < EB->col) {
          changeEntry(mat, i, EA->col, EA->val);
          moveNext(A->rows[i]);
        } 
        else {
          changeEntry(mat, i, EB->col, EB->val);
          moveNext(tempM->rows[i]);
        }
      } 
      else if (index(A->rows[i]) != -1) {
        Entry EA = (Entry)get(A->rows[i]);
        changeEntry(mat, i, EA->col, EA->val);
        moveNext(A->rows[i]);
      } 
      else {
        Entry EB = (Entry)get(tempM->rows[i]);
        changeEntry(mat, i, EB->col, EB->val);
        moveNext(tempM->rows[i]);
      }
    }
  }
  freeMatrix(&tempM);
  return mat;
}








// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B).
Matrix diff(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Error in Matrix ADT: sum(), A or B is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Error in Matrix ADT: sum(), A and B do not have matching sizes!\n");
    exit(EXIT_FAILURE);
  }
  Matrix tempM = copy(B);
  Matrix newM = newMatrix(A->size);
  double newSum = 0.0; 
  for (int i = 1; i < (A->size + 1); i++) {
    moveFront(A->rows[i]);
    moveFront(tempM->rows[i]);

    if (length(A->rows[i]) == 0 && length(tempM->rows[i]) != 0) {
      while (index(tempM->rows[i]) != -1) {
        Entry EB = (Entry)get(tempM->rows[i]);
        changeEntry(newM, i, EB->col, (EB->val * -1));
        moveNext(tempM->rows[i]);
      }
    }

    if (length(tempM->rows[i]) == 0 && length(A->rows[i]) != 0) {
      while (index(A->rows[i]) != -1) {
        Entry EA = (Entry)get(A->rows[i]);
        changeEntry(newM, i, EA->col, EA->val);
        moveNext(A->rows[i]);
      }
    }

    while (index(A->rows[i]) != -1 || index(tempM->rows[i]) != -1) {
      if (index(A->rows[i]) != -1 && index(tempM->rows[i]) != -1) {
        Entry EA = (Entry)get(A->rows[i]);
        Entry EB = (Entry)get(tempM->rows[i]);
        if (EA->col == EB->col) {
          newSum = EA->val - EB->val;
          if (newSum != 0) {
            changeEntry(newM, i, EA->col, newSum);
          }
          moveNext(A->rows[i]);
          moveNext(tempM->rows[i]);
        } 
        else if (EA->col < EB->col) {
          //
          changeEntry(newM, i, EA->col, EA->val);
          moveNext(A->rows[i]);
        } 
        else {
          changeEntry(newM, i, EB->col, (EB->val * -1));
          moveNext(tempM->rows[i]);
        }
      } 
      else if (index(A->rows[i]) != -1) {
        Entry EA = (Entry)get(A->rows[i]);
        changeEntry(newM, i, EA->col, EA->val);
        moveNext(A->rows[i]);
      } 
      else {
        Entry EB = (Entry)get(tempM->rows[i]);
        changeEntry(newM, i, EB->col, (EB->val * -1));
        moveNext(tempM->rows[i]);
      }
    }
  }
  freeMatrix(&tempM);
  return newM;
}




//double vectorDot(List P, List Q)
// helper function
double vectorDot(List P, List Q) {

  moveFront(P);
  moveFront(Q);
  double total = 0.0;
  if (length(P) == 0 || length(Q) == 0) {
    return total;
  }
  while (index(P) != -1 && index(Q) != -1) {

    Entry EA = (Entry)get(P);
    Entry EB = (Entry)get(Q);
    if (EA->col == EB->col) {

      total += (EA->val * EB->val);
      moveNext(P);
      moveNext(Q);
    } 
    else if (EA->col < EB->col) {

      moveNext(P);
    } 
    else {

      moveNext(Q);
    }
  }

  return total;
}




// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Error in Matrix ADT: product(), A or B is NULL!\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Error in Matrix ADT: product(), A and B do not match sizes!\n");
    exit(EXIT_FAILURE);
  }
  Matrix newM = newMatrix(size(A));
  Matrix tempM = transpose(B);
  for (int i = 1; i < (size(A) + 1); i++) {
    for (int j = 1; j < (size(tempM) + 1); j++) {
      double prod = vectorDot(A->rows[i], tempM->rows[j]);
      if (prod != 0) {
        changeEntry(newM, i, j, prod);
      }
    }
  }

  freeMatrix(&tempM);
  return newM;
}




// helper function
void printEntry(FILE *out, Entry E) {
  fprintf(out, "(%d, %.1lf) ", E->col, E->val);
}



// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE *out, Matrix M) {
  if (M == NULL) {
    printf("Error in Matrix ADT: printMatrix, M is NULL!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < (size(M) + 1); i++) {
    if (length(M->rows[i]) != 0) {
      moveFront(M->rows[i]);
      fprintf(out, "%d: ", i);

      while (index(M->rows[i]) != -1) {
        Entry tempEn = (Entry)get(M->rows[i]);
        printEntry(out, tempEn);
        moveNext(M->rows[i]);
      }
      fprintf(out, "\n");
    }
  }
}

