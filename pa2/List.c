/*********************************************************************************
* Vara Neha Madem, vmadem
* 2023 Spring CSE101 PA#1
* List.c
* List ADT
*********************************************************************************/  

#include "List.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeObj *Node;


//structs
typedef struct NodeObj {
  ListElement data;
  Node next;
  Node prev;
} NodeObj;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int index;
  int length;
} ListObj;


//create new node
Node newNode(int data) {
  Node n = malloc(sizeof(NodeObj));
  if (n) {
    n->next = NULL;
    n->prev = NULL;
    n->data = data;
    return n;
  } else {
    fprintf(stderr, "Not enough heap memory for node!");
    exit(EXIT_FAILURE);
  }
}


//free all memory/delete the node
void freeNode(Node *n) {
  if (n != NULL && *n != NULL) {
    free(*n);
    *n = NULL;
    n = NULL;
  }
}


// Constructors-Destructors ---------------------------------------------------


// Creates and returns a new empty List.
List newList(void) {
  List L = malloc(sizeof(ListObj));
  L->index = -1;
  L->length = 0;
  L->front = L->cursor = L->back = NULL;
  return L;
}



// Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    while (((*pL)->front != NULL) && length(*pL) != 0) {
      deleteFront(*pL);
    }
    
    free(*pL);
    *pL = NULL;
    pL = NULL;
  }
}


// Access functions -----------------------------------------------------------


// Returns the number of elements in L.
int length(List L) { 
  return L->length; 
}



// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
  return L->index;
}


// Returns front element of L. Pre: length()>0
int front(List L) {
  if (length(L) > 0) {
    return L->front->data;
  } 
  else {
    printf("List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
}




// Returns back element of L. Pre: length()>0
int back(List L) {
  if (length(L) > 0) {
    return L->back->data;
  } 
  else {
    printf("List Error: calling back() on an empty List\n");
    exit(EXIT_FAILURE);
  }
}




// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
  if (length(L) <= 0 || index(L) < 0) {
    printf("List Error: calling get() on empty List or index less than 0\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}




// Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
bool equals(List A, List B) {
  if (((A == NULL) && (B != NULL)) || ((A != NULL) && (B == NULL))) {
    return false;
  } 
  else if (A == NULL && B == NULL) {
    return true;
  }

  if ((A->length == B->length)) {
    Node A_track = A->front;
    Node B_track = B->front;

    for (int i = 0; i < A->length; i++) {
      if (A_track->data != B_track->data) {
        return false;
      }
      A_track = A_track->next;
      B_track = B_track->next;
    }
    return true;
  } 

  else {
    return false;
  }
}



// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
  if (L != NULL) {
    while (L->back != NULL) {
      deleteBack(L);
    }
    L->length = 0;
    L->index = -1;
  } 
  else {
    printf("List Error: calling clear() on a NULL List\n");
    exit(EXIT_FAILURE);
  }
}




// Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void set(List L, int x) {
  if (length(L) > 0 && index(L) >= 0) {
    L->cursor->data = x;
  } 
  else {
    printf("List Error: calling set() on an empty List\n");
    exit(EXIT_FAILURE);
  }
}





// If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L){
  if(L == NULL){
    printf("List Error: calling moveFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) > 0){
    L->cursor = L->front;
    L->index = 0;
  }

  return;
}




// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L){
  if(L == NULL){
    printf("ERROR: Trying to move cursor to the back of a NULL list\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) > 0){
    L->cursor = L->back;
    L->index = length(L) - 1;
  }
}




// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L) {
  if (L == NULL) {
    printf("List Error: movePrev(), L is null.");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    return;
  }
  if (L->cursor == L->front) {

    L->index = -1;
    L->cursor = NULL;
    return;
  }

  if ((L->cursor != NULL) && (L->cursor != L->front)) {
    L->cursor = L->cursor->prev;
    L->index--;
  }
}




// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing

void moveNext(List L) {
  if (L == NULL) {
    printf("List Error: moveNext(), L is null.");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    return;
  }
  if (L->cursor == L->back) {
    L->index = -1;
    L->cursor = NULL;
    return;
  }

  if ((L->cursor != NULL) && (L->cursor != L->back)) {
    L->cursor = L->cursor->next;
    L->index++;
  }
}



// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, int x) {
  if (L != NULL) {
    Node new = newNode(x);

    if (length(L) > 0) {
      L->front->prev = new;
      new->next = L->front;
    } 

    else if (length(L) == 0) {
      L->front = L->back = new;
    } 

    else {
      exit(EXIT_FAILURE);
    }
    L->front = new;
    L->length++;
    
    if (L->index != -1) {
      L->index++;
    }
  } 
  else {
    fprintf(stderr, "List Error: prepend(), L is NULL.");
    exit(EXIT_FAILURE);
  }
}




// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, int x) {
  if (L != NULL) {
    Node new = newNode(x);

    if (length(L) > 0) {
      L->back->next = new;
      new->prev = L->back;
    } 
    else if (length(L) == 0) {
      L->front = L->back = new;
    } 
    else {
      exit(EXIT_FAILURE);
    }

    L->back = new;
    L->length++;

   
  } 
  else {
    printf("List Error: append(), L is NULL.");
    exit(EXIT_FAILURE);
  }
}





// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
  if (L == NULL || length(L) <= 0 ||index(L) < 0) {
    exit(EXIT_FAILURE);
  }
  
  if (L->cursor == L->front) {
    prepend(L, x);
  } 
  else { 
    Node new = newNode(x);
    Node old = L->cursor->prev;

    L->cursor->prev = new; 
    new->next = L->cursor;
    
    new->prev = old;
    old->next = new;
    L->length++;
    L->index++;
  }
}




// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
  if (L == NULL || length(L) <= 0 || index(L) < 0) {
    exit(EXIT_FAILURE);
  }
  
  if (L->back == L->cursor) {
    append(L, x);
  } 
  else {
    Node new = newNode(x);
    Node old = L->cursor->next;
    L->cursor->next = new;
    new->prev = L->cursor;
    new->next = old;
    old->prev = new;
    L->length++;
  }
  
}






// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  if ((length(L) > 0)) {

    Node remove = L->front;

    if (L->front == L->cursor) {
      L->index = -1;
    } 
    else {
      L->index--;
    }
    if (length(L) > 1) {
      L->front = L->front->next;
    } 
    else {
      L->front = L->back = NULL;
    }

    L->length--;
    freeNode(&remove);
  } 
  else {
    exit(EXIT_FAILURE);
  }
}





// Delete the back element. Pre: length()>0
void deleteBack(List L) {

  if (length(L) > 0) { 

    Node remove = L->back;

    if (L->back == L->cursor) {
      L->index = -1;
    }
    if (length(L) > 1) {
      L->back = L->back->prev;
    } 
    else {
      L->back = L->front = NULL;
    }
    L->length--;
    freeNode(&remove);
  } 
  else {
    exit(EXIT_FAILURE);
  }
}





// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
void delete (List L) {
  if (L == NULL) {
    printf("List Error: delete(), L is NULL");
    exit(EXIT_FAILURE);
  }
  if (length(L) <= 0) {
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    exit(EXIT_FAILURE);
  }


  if (L->cursor == L->back) {
  
    deleteBack(L);
  } 
  else if (L->cursor == L->front) {
    deleteFront(L);
  } 
  else {
    Node curr = L->cursor;
    L->cursor->next->prev = L->cursor->prev;
    L->cursor->prev->next = L->cursor->next;
    L->index = -1;
    L->length--;
    freeNode(&curr);

  }
}




// Other operations -----------------------------------------------------------


// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
  if(L==NULL){
    printf("Error in List ADT: printList(), L appears to be NULL");
    exit(EXIT_FAILURE);
  }

  for(Node curr = L->front; curr != NULL; curr = curr->next){
    fprintf(out, "%d ",curr->data);
  }
  return;
}



// Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
  if (L != NULL) {
    List copy = newList();
    Node f = L->front;

    for (int i = 0; i < length(L); i++) {
      append(copy, f->data);
      f = f->next;
    }
    return copy;
  } 
  else {
    return NULL;
  }
}










