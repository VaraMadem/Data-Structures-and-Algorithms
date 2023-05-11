
//-----------------------------------------------------------------------------
// List.cpp
// Vara Neha Madem
// 1872442
// pa5
//CSE101 Tantalo
//-----------------------------------------------------------------------------


#include<iostream>
#include<string>
#include "List.h"

using namespace std;

// Node constructor
List::Node::Node(ListElement x) {
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors

// Creates new List in the empty state.
List::List() {
   frontDummy = new List::Node(-99);
   backDummy = new List::Node(-99);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
}

// Copy constructor.
List::List(const List& L) {
   frontDummy = new List::Node(-99);
   backDummy = new List::Node(-99);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   
   Node* temp = L.frontDummy->next;
   while (temp != L.backDummy) {
      insertBefore(temp->data);
      temp = temp->next;
   }
   moveFront();
}


// Destructor
List::~List() {
    while(num_elements !=0){
   clear();
}
   delete frontDummy;
   delete backDummy;
}

// Access functions

// length()
// Returns the length of this List.
int List::length() const {
   return num_elements;
}

// front()
   // Returns the front element in this List.
   // pre: length()>0
ListElement List::front() const {
   if (num_elements == 0) {
    throw std::length_error("List Error: front() empty List");
      //cerr << "List Error: front() called on empty List" << endl;
      exit(EXIT_FAILURE);
   }
   return frontDummy->next->data;
}

// back()
   // Returns the back element in this List.
   // pre: length()>0
ListElement List::back() const {
   if (num_elements == 0) {
    throw std::length_error("List Error: back() empty List");
      //cerr << "List Error: back() called on empty List" << endl;
      exit(EXIT_FAILURE);
   }
   return backDummy->prev->data;
}

// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
   return pos_cursor;
}

// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
   if (pos_cursor == num_elements || num_elements == 0) {
    throw std::range_error("peekNext() called at end of List");
      //cerr << "List Error: peekNext() called at end of List" << endl;
      exit(EXIT_FAILURE);
   }
   return afterCursor->data;
}

// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
   if (pos_cursor == 0 || num_elements == 0) {
    throw std::range_error("peekPrev() called at start of List");
      //cerr << "List Error: peekPrev() called at start of List" << endl;
        exit(EXIT_FAILURE);
   }
   return beforeCursor->data;
}






// Manipulation procedures

// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    this->moveBack();
    while(num_elements>0){
        this->eraseBefore();
    }
}



// Moves cursor to position 0 in this List.
void List::moveFront() {
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
   pos_cursor = 0;
}



// moveBack()
   // Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
ListElement List::moveNext() {
    if(pos_cursor>= length()){
        throw std::range_error("moveNext() called at end of List");
    }
    if (pos_cursor < num_elements) {
        beforeCursor = beforeCursor->next;
        //beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        pos_cursor++;
        return beforeCursor->data;
    } else {
        return -1;  // Error
    }
}



// movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
ListElement List::movePrev() {
    if(pos_cursor<= 0){
        throw std::range_error("movePrev() called at start of List");
    }

    this->beforeCursor = this->beforeCursor->prev;
    this->afterCursor = this->afterCursor->prev;
    pos_cursor--;
    return(this->afterCursor->data);
}


// insertAfter()
void List::insertAfter(ListElement x) {
    Node* new_node = new Node(x);
    new_node->next = afterCursor;
    new_node->prev = beforeCursor;
    afterCursor->prev = new_node;
    beforeCursor->next = new_node;
    afterCursor = new_node;
    //pos_cursor++;
    num_elements++;
}


// insertBefore()
   // Inserts x before cursor.

void List::insertBefore(ListElement x) {
    Node* new_node = new Node(x);
    new_node->next = afterCursor;
    new_node->prev = beforeCursor;
    afterCursor->prev = new_node;
    beforeCursor->next = new_node;
    beforeCursor = new_node;
    pos_cursor++;
    num_elements++;
}


// setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
void List::setAfter(ListElement x) {
    if(pos_cursor>= length()){
        throw std::range_error("setAfter() called at start of List");
    }
    if (pos_cursor < num_elements) {
        afterCursor->data = x;
    }
}

// setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
void List::setBefore(ListElement x) {
    if(pos_cursor<= 0){
        throw std::range_error("setBefore() called at start of List");
    }
    if (pos_cursor > 0) {
        beforeCursor->data = x;
    }
}

// eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
void List::eraseAfter() {
    if (position() >= length()) {
                throw std::range_error("List::eraseBefore(): invalid cursor position");
        }
    if (pos_cursor < num_elements) {
        Node* temp = afterCursor;
        //cout << "tmp data" << temp->data << endl;
        //cout << "tmp prev data" << temp->prev->data << endl;
        afterCursor = afterCursor->next;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
        num_elements--;
        //cout << "tmp data" << temp->data << endl;
        delete temp;

    }
}


// eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
void List::eraseBefore() {
        if (position() <= 0) {
                throw std::range_error("List::eraseBefore(): invalid cursor position");
        }
        Node* temp = beforeCursor;
        beforeCursor = beforeCursor->prev;
        afterCursor->prev = beforeCursor;
        beforeCursor->next = afterCursor;
        pos_cursor--;
        num_elements--;
        delete temp;
}


// Other Functions ---------------------------------------------------------

// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
    //Node* N = afterCursor;
    //int i = pos_cursor;
    while (position() != length()) {

            beforeCursor = beforeCursor->next;
            afterCursor = afterCursor->next;
            pos_cursor++;
            if (beforeCursor->data == x) {
            return pos_cursor;
        }
        }
        pos_cursor = num_elements;
    return -1;
    
    }
    


// findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    while(this->beforeCursor != this->frontDummy){
        if(this->beforeCursor->data ==x) {
            this->movePrev();
            return(pos_cursor);
        }
        this->movePrev();
    }
    return -1;



}



/*
void List::cleanup()
{
    Node* aa = frontDummy->next;
    for(int x = 0; x < length(); ++x)
    {
        ListElement elem = aa->data;
        Node* b = frontDummy->next;
        
        bool alreadyVisited = false;
        for(int y = 0; y < length(); ++y)
        {
            ListElement e = b->data;
            if(elem == e)
            {
                if (alreadyVisited)
                {
                    Node* a = b->prev;
                    Node* c = nullptr;
                    if (b->next != nullptr)
                        c = b->next;
                    a->next = c;
                    if (c != nullptr)
                        c->prev = a;
                    //pos_cursor -= 1;
                    delete b;

                    num_elements = num_elements - 1; 
                }
                else
                {
                    alreadyVisited = true;
                }
            }
            b = b->next;
        }
        aa = aa->next;
    }
}

*/


/*

Node* toBeFreed = NULL;
Node* node = frontDummy->next;

while (node != backDummy){
Node* nodeI = frontDummy->next;
int pos = 1;
Node* next = node->next;


bool found = false;
while (!found && nodeI != node)
{
   found = (nodeI->data == node->data);
    if (found) // delete node
    {
       node->prev->next = node->next;
       node->next->prev = node->prev;
       num_elements--;
       toBeFreed = node;

       if((node <= beforeCursor)){
         pos_cursor--;
       }
       else if (node == beforeCursor)
           beforeCursor = beforeCursor->prev;
       else if (node == afterCursor)
           afterCursor = afterCursor->next;


       

      }
      else
        nodeI = nodeI->next;
}
  
  node = next;
  
  if(toBeFreed){
      delete toBeFreed;
  }
      
  pos++;
}
    
    
    */



  // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    Node* node = frontDummy->next;
    Node* toBeFreed =NULL;

    while (node != backDummy){
    Node* nodeI = node->next;

    while ( nodeI != backDummy)
    {
        if(nodeI->data == node->data)
        {
            //  unlink the node from linked list
            nodeI->prev->next = nodeI->next;
            nodeI->next->prev = nodeI->prev;
            num_elements--;
        
            
            if((nodeI <= beforeCursor)){
                pos_cursor--;
            }
            else if (nodeI == beforeCursor)
             beforeCursor = beforeCursor->prev;
            else if (nodeI == afterCursor)
                afterCursor = afterCursor->next;
            
            toBeFreed = nodeI;
            
        }
        
        nodeI = nodeI->next;
        if (toBeFreed != NULL){
            delete toBeFreed;
            toBeFreed= NULL;
        }
    }
      
      node = node->next;
      
    }
    

   }

/*
 Node* node = frontDummy->next;
 Node* toBeFreed =NULL;

 while (node != backDummy){
 Node* nodeI = node->next;

 while ( nodeI != backDummy)
 {
     if(nodeI->data == node->data)
     {
         //  unlink the node from linked list
         nodeI->prev->next = nodeI->next;
         nodeI->next->prev = nodeI->prev;
         num_elements--;
     
         
         if((nodeI <= beforeCursor)){
             pos_cursor--;
         }
         else if (nodeI == beforeCursor)
          beforeCursor = beforeCursor->prev;
         else if (nodeI == afterCursor)
             afterCursor = afterCursor->next;
         
         toBeFreed = nodeI;
         
     }
     
     nodeI = nodeI->next;
     if (toBeFreed != NULL){
         delete toBeFreed;
         toBeFreed= NULL;
     }
 }
   
   node = node->next;
   
 }
 

}

*/


// concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List new_list;
    Node* N = frontDummy->next;
    while (N != backDummy) {
        new_list.insertAfter(N->data);
        N = N->next;
    }
    N = L.frontDummy->next;
    while (N != L.backDummy) {
        new_list.insertAfter(N->data);
        N = N->next;
    }
    new_list.moveFront();
    return new_list;
}

// to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string str = "(";
    Node* N = frontDummy->next;
    while (N != backDummy) {
        str += std::to_string(N->data);
        if (N->next != backDummy) {
            str += ",";
        }
        N = N->next;
    }
    str += ")";
    return str;
}


// equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const
{
   if (num_elements != R.num_elements)
      return false;
   Node* N = frontDummy->next;
   Node* M = R.frontDummy->next;
   while (N != backDummy)
   {
      if (N->data != M->data)
         return false;
      N = N->next;
      M = M->next;
   }
   return true;
}


// Overriden Operators -----------------------------------------------------
   


/*
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List& L) {
    stream << L.to_string();
    return stream;
}
*/

//repeated

// operator<<()
   // Inserts string representation of L into stream.
ostream& operator<<(ostream& stream, const List& L){
   for (List::Node* N = L.frontDummy->next; N != L.backDummy; N = N->next){
      stream << N->data << " ";
   }
   return stream;
}




// operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B){
   bool equal = true;
   if (A.length() == B.length()){
      List::Node* N = A.frontDummy->next;
      List::Node* M = B.frontDummy->next;
      while (N != A.backDummy){
         if (N->data != M->data){
            equal = false;
            break;
         }
         N = N->next;
         M = M->next;
      }
   }
   else {
      equal = false;
   }
   return equal;
}

// operator=()



// operator=()
   // Overwrites the state of this List with state of L.
List& List::operator=(const List& L){
    frontDummy = new List::Node(-5);
    backDummy = new List::Node(-4);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
    Node *val = L.frontDummy->next;
    while(val != L.backDummy){
        insertBefore(val->data);
        val = val->next;
    }
    moveFront();

    return *this;

   
};








