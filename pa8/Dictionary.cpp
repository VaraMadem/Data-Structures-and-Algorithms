//-----------------------------------------------------------------------------
// Dictionary.cpp
// Vara Neha Madem
// 1872442
// CSE101 Tantalo pa8
//-----------------------------------------------------------------------------
#include <cmath>
#include <string>
#include "Dictionary.h"




// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
   key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
   color = 0;
}




Dictionary::Dictionary() {
   nil = new Node("nil", 0);
  nil->parent = nil;
  nil->left = nil;
  nil->right = nil;
   nil->color = 1;
   root = nil;
  current = nil;
  num_pairs = 0;
}


Dictionary::Dictionary(const Dictionary &D) {
   nil = new Node("\0", 0);
   nil->color = 1; 
   root = nil;
   current = nil;
   num_pairs = 0;

   preOrderCopy(D.root, D.nil); 
}



Dictionary::~Dictionary() {
  postOrderDelete(root);
  delete nil;
}



// Helper Functions (Optional) ---------------------------------------------

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
  void Dictionary::inOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    inOrderString(s, R->left);
    std::string entry = (R->key + " : " + std::to_string(R->val) + "\n");
    s += entry;
    inOrderString(s, R->right);
  }
}

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string will consist of keys only, with the order determined by a pre-order
   // tree walk. The keys stored in black Nodes will be appended as "key\n", and
   // the keys stored in red Nodes will be appended as "key (RED)\n". The output 
   // of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
   void Dictionary::preOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    s += (R->key + "\n");
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}

   // BST_insert()
   // Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
   //void BST_insert(Node* M);

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   void Dictionary::preOrderCopy(Node *R, Node *N) {
  if (R->key != "nil") {
    setValue(R->key, R->val);

    preOrderCopy(R->left, N->left);
    preOrderCopy(R->right, N->right);
  }
}

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R.
   void Dictionary::postOrderDelete(Node *R) {
  if (R != nil) {
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    num_pairs--;
    delete R;
  }
  R = nil;
}

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
   //Node* search(Node* R, keyType k) const;
   Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
  if (R == nil || k == R->key) {
    return R;
  } 
  else if (k < R->key) {
    return search(R->left, k);
  } 
  else { 
    return search(R->right, k);
  }
}

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
   //Node* findMin(Node* R);
   Dictionary::Node *Dictionary::findMin(Node *R) {
  if (R == nil) {
    return R;
  }
  Node *n = R;
  while (n->left != nil) {
    n = n->left;
  }
  return n;
}


   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
  // Node* findMax(Node* R);
   Dictionary::Node *Dictionary::findMax(Node *R) {
  if (R == nil) {
    return nil;
  }
  Node *n = R;
  while (n->right != nil) {
    n = n->right;
  }
  return n;
}

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
   //Node* findNext(Node* N);
   Dictionary::Node *Dictionary::findNext(Node *R) {
  Node *n = R;
  if (n->right != nil) {
    return findMin(n->right);
  }
  Node *m = n->parent; 
  while (m != nil && n == m->right) {
    n = m;
    m = m->parent;
  }
  return m;
}

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
   //Node* findPrev(Node* N);
   Dictionary::Node *Dictionary::findPrev(Node *R) {
  if (R == nil) {
    return nil;
  }

  Node *n = R;
  if (n->left != nil) {
    return findMax(n->left);
  }
  Node *m = n->parent; 
  while (m != nil && n == m->left) {
    n = m;
    m = m->parent;
  }
  return m;
}


   // RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node *N) {
   Node *L = N->right; 
   N->right = L->left;

   if (L->left != nil) {
      L->left->parent = N;
   }

   L->parent = N->parent;

   if (N->parent == nil) {
      root = L;
   } 

   else if (N == N->parent->left) {
      N->parent->left = L;
   } 

   else {
      N->parent->right = L;
   }

   L->left = N;
   N->parent = L;
}


   // RightRotate()
   //void RightRotate(Node* N);
   void Dictionary::RightRotate(Node *N) {
   Node *R = N->left; 
   N->left = R->right;

   if (R->right != nil) {
      R->right->parent = N;
   }

   R->parent = N->parent;

   if (N->parent == nil) {
      root = R;
   } 

   else if (N == N->parent->right) {
      N->parent->right = R;
   } 

   else {
      N->parent->left = R;
   }

   R->right = N;
   N->parent = R;
}

   // RB_InsertFixUP()
   //void RB_InsertFixUp(Node* N);
   void Dictionary::RB_InsertFixUp(Node *N) {
   while (N->parent->color == 0) { 
      if (N->parent == N->parent->parent->left) {
         Node *F = N->parent->parent->right;
         if (F->color == 0) {
            N->parent->color = 1;
            F->color = 1;
            N->parent->parent->color = 0;
            N = N->parent->parent;
         } 
         else {
            if (N == N->parent->right) {
               N = N->parent;
               LeftRotate(N);
            }
            N->parent->color = 1;
            N->parent->parent->color = 0;
            RightRotate(N->parent->parent);
         }
      } 
      else {
         Node *F = N->parent->parent->left;
         if (F->color == 0) {
            N->parent->color = 1;
            F->color = 1;
            N->parent->parent->color = 0;
            N = N->parent->parent;
         } 
         else {
            if (N == N->parent->left) {
               N = N->parent;
               RightRotate(N);
            }
            N->parent->color = 1;
            N->parent->parent->color = 0;
            LeftRotate(N->parent->parent);
         }
      }
   }
   root->color = 1;
}

   // RB_Transplant()
   void Dictionary::RB_Transplant(Node *u, Node *v) {
   if (u->parent == nil) {
      root = v;
   } 
   else if (u == u->parent->left) {
      u->parent->left = v;
   } 
   else {
      u->parent->right = v;
   }
   v->parent = u->parent;
}

void Dictionary::RB_Delete(Node *N) {
   Node *y = N;
   Node *x;
   int before = y->color;
   if (N->left == nil) {
      x = N->right;
      RB_Transplant(N, N->right);
   } 
   else if (N->right == nil) {
      x = N->left;
      RB_Transplant(N, N->left);
   } 
   else {
      y = findMin(N->right);
      before = y->color;
      x = y->right;
      if (y->parent == N) {
         x->parent = y;
      } 
      else {
         RB_Transplant(y, y->right);
         y->right = N->right;
         y->right->parent = y;
      }
      RB_Transplant(N, y);
      y->left = N->left;
      y->left->parent = y;
      y->color = N->color;
   }
   if (before == 1) {
      RB_DeleteFixUp(x);
   }
}


   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node *N) {
   while (N != root && N->color == 1) {

      if (N == N->parent->left) {
         Node *w = N->parent->right;

         if (w->color == 0) {
            w->color = 1;
            N->parent->color = 0;
            LeftRotate(N->parent);
            w = N->parent->right;
         }

         if (w->left->color == 1 && w->right->color == 1) {
            w->color = 0;
            N = N->parent;
         } 

         else {
            if (w->right->color == 1) {
               w->left->color = 1;
               w->color = 0;
               RightRotate(w);
               w = N->parent->right;
            }
            w->color = N->parent->color;
            N->parent->color = 1;
            w->right->color = 1;
            LeftRotate(N->parent);
            N = root;
         }
      } 

      else {
         Node *w = N->parent->left;

         if (w->color == 0) {
            w->color = 1;
            N->parent->color = 0;
            RightRotate(N->parent);
            w = N->parent->left;
         }

         if (w->right->color == 1 && w->left->color == 1) {
            w->color = 0;
            N = N->parent;
         } 

         else {
            if (w->left->color == 1) {
               w->right->color = 1;
               w->color = 0;
               LeftRotate(w);
               w = N->parent->left;
            }
            w->color = N->parent->color;
            N->parent->color = 1;
            w->left->color = 1;
            RightRotate(N->parent);
            N = root;
         }
      }
   }
   N->color = 1;
}



   // RB_Delete()
   //void RB_Delete(Node* N);





   // Access functions --------------------------------------------------------

   // size() returns size of this Dictionary
int Dictionary::size() const { 
  return num_pairs; 
}





// contains() returns true if there exists a pair such that key == k, false
// otherwise
bool Dictionary::contains(keyType k) const {
  Node *result = search(root, k); 
  if (result == nil) {
    return false;
  } 
  else {
    return true;
  }
}

 

 // getValue() returns reference to value of key k
// pre: contains(k)
valType &Dictionary::getValue(keyType k) const {
  if (contains(k)) {
    Node *n = search(root, k);
    return n->val;
  } 
  else {
    throw std::length_error("getValue()error");
  }
}



  // hasCurrent() returns true if current iterator is defined, returns false
// otherwise.
bool Dictionary::hasCurrent() const {
  if (current != nil) {
    return true;
  } 
  else {
    return false;
  }
}




// currentKey() returns the current key.
// precondition: hasCurrent()
keyType Dictionary::currentKey() const {
  if (hasCurrent()) {
    return current->key;
  } 
  else {
    throw std::length_error("currentKey()error");
  }
}




// currentVal() returns a reference to the current value
// precondition: hasCurrent()
valType &Dictionary::currentVal() const {
  if (hasCurrent()) {
    return current->val;
  } 
  else {
    throw std::logic_error("currentVal()error");
  }
}


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
 
void Dictionary::clear() {
   postOrderDelete(root);
   root = nil;
   current = nil;
   num_pairs = 0;
}


   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   //void setValue(keyType k, valType v);
   void Dictionary::setValue(keyType k, valType v) {

   Node *b = nil;
   Node *a = root;
   while (a != nil) {
      b = a;
      if (k < a->key) {
         a = a->left;
      } 
      else if (k == a->key) {
         a->val = v;
         return;
      }
      else {
         a = a->right;
      }
   }

   Node *N = new Node(k, v);
   N->left = nil;
   N->right = nil;
   N->parent = b;
   if (b == nil) {
      root = N; 
   } 
   else if (N->key < b->key) {
      b->left = N;
   }  
   else {
      b->right = N;
   }

   num_pairs += 1;
   N->color = 0; 
   RB_InsertFixUp(N);
}

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).


void Dictionary::remove(keyType k) {

   if (contains(k)) {
      Node *N = search(root, k);
      if (N == current) {
         current = nil;
      }
      RB_Delete(N);
      delete N;
      N = nullptr;
      num_pairs -= 1;
   }

   else {
      throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
   }
}

// begin() places current iterator at first key value pair. otherwise, does
// nothing. based on < operator on keys
void Dictionary::begin() { 
  current = findMin(root); 
}



// end() places current iterator at last key value pair.
void Dictionary::end() { 
  current = findMax(root); 
}





// next() advances current iterator to the next pair if it is not at the last
// pair. if current isat the last iterator, make current undefined. pre:
// hasCurrent()
void Dictionary::next() {
  if (hasCurrent()) {
    if (current == findMax(root)) {
      current = nil;
      return;
    }
    current = findNext(current);
  } 
  else {
    throw std::length_error("next()error");
  }
}




void Dictionary::prev() {
  if (hasCurrent()) {
    if (current == findMin(root)) {
      current = nil;
      return;
    }
    current = findPrev(current);
  } 
  else {
    throw std::length_error("prev() error");
  }
}



   // Other Functions ---------------------------------------------------------

// to_string() returns string representation of this Dictionary. Consecutive key
// value pairs
std::string Dictionary::to_string() const {
  std::string n = ""; 
  inOrderString(n, root);
  return n;
}



// pre_string() returns consisting of all keys in the dictionary.
std::string Dictionary::pre_string() const {
  std::string n = ""; 
  preOrderString(n, root);
  return n;
}



// equals() returns true if and only if this dictionary contains the same key
// value pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const {
  std::string thisstring = to_string();
  std::string Dstring = D.to_string();
  return (thisstring == Dstring);
}




   

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// to_string
std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
  return stream << D.to_string();
}




// operator ==() returns true if and only if Dict A == Dict B, as defined by
// equals().
bool operator==(const Dictionary &A, const Dictionary &B) {
  return A.equals(B);
}




// operator=()
// Overwrites state of Dictionary with state of D
Dictionary &Dictionary::operator=(const Dictionary &D) {
  if (this != &D) {
    Dictionary tempD = D;
    std::swap(nil, tempD.nil);
    std::swap(root, tempD.root);
    std::swap(current, tempD.current);
    std::swap(num_pairs, tempD.num_pairs);
  }
  return (*this);
}










