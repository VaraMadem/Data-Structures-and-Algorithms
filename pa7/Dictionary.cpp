//-----------------------------------------------------------------------------
// Dictionary.cpp
// Vara Neha Madem
// 1872442
// pa7
//CSE101 Tantalo
//-----------------------------------------------------------------------------

#include <cmath>
#include <string>
#include "Dictionary.h"



Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;

}




// Class Constructors & Destructors ----------------------------------------

Dictionary::Dictionary() {
  nil = new Node("nil", 0);
  nil->parent = nil;
  nil->left = nil;
  nil->right = nil;
  
  root = nil;
  current = nil;
  num_pairs = 0;
}



Dictionary::Dictionary(const Dictionary &D) {
  nil = new Node("nil", 0);
  nil->parent = nil;
  nil->left = nil;
  nil->right = nil;
  
  root = nil;
  current = nil;
  num_pairs = 0;
  preOrderCopy(D.root, root);
  num_pairs = D.num_pairs;
}



Dictionary::~Dictionary() {
  postOrderDelete(root);
  delete nil;
}







// Helper Functions (Optional) ---------------------------------------------


// transplant()
// puts node v into node u
//void transplant(Node* u, Node* v);
void Dictionary::transplant(Node *u, Node *v) {
  if (u->parent == nil) {
    root = v;
  } 
  else if (u == u->parent->left) {
    u->parent->left = v;
  } 
  else {
    u->parent->right = v;
  }
  if (v != nil) {
    v->parent = u->parent;
  }
}





// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
//void inOrderString(std::string& s, Node* R) const;
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
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
//void preOrderString(std::string& s, Node* R) const;
void Dictionary::preOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    s += (R->key + "\n");
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}




// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
//void preOrderCopy(Node* R, Node* N);
void Dictionary::preOrderCopy(Node *R, Node *N) {
  if (R->key != "nil") {
    setValue(R->key, R->val);

    preOrderCopy(R->left, N->left);
    preOrderCopy(R->right, N->right);
  }
}




// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
//void postOrderDelete(Node* R);
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
//Node* findMax(Node* R);
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


// clear() resets dictionary to 0 state with no pairs
void Dictionary::clear() {
  postOrderDelete(root);
  num_pairs = 0;
  current = nil;
  root = nil;
}




// setValue() inserts node with key k and value v into this Dictionary. If key
// already exists, overwrite the value. Otherwise, insert the new node.
void Dictionary::setValue(keyType k, valType v) { //psuedocode
  Node *insertN = new Node(k, v); 
  insertN->left = nil;
  insertN->right = nil;
  Node *y = nil;
  Node *x = root;
  while (x != nil) {
    y = x;
    if (k < x->key) {
      x = x->left;
    } 
    else {
      x = x->right;
    }
  }
  insertN->parent = y;
  if (y == nil) {
    root = insertN; 
  } 
  else if (k < y->key) {
    y->left = insertN;
  } 
  else if (k > y->key) {
    y->right = insertN;
  } 
  else {
    y->val = v;
    delete insertN;
    num_pairs--;
  }
  num_pairs++;
}






// remove() deletes any pair with key == k. If pair is current, then current
// becomes undefined. pre contains(k)
void Dictionary::remove(keyType k) {  //psuedocode
  if (contains(k)) {
    Node *removeN = search(root, k);
    if (removeN == current) {
      current = nil;
    }
    if (removeN->left == nil) {
      transplant(removeN, removeN->right);
    } 
    else if (removeN->right == nil) {
      transplant(removeN, removeN->left);
    } 
    else {
      Node *min = findMin(removeN->right);
      if (min->parent != removeN) {
        transplant(min, min->right);
        min->right = removeN->right;
        min->right->parent = min;
      }
      transplant(removeN, min);
      min->left = removeN->left;
      min->left->parent = min;
    }
    delete removeN;
    num_pairs--;
  } 
  else {
    throw std::length_error("remove()error");
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




