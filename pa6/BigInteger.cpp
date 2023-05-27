//-----------------------------------------------------------------------------
// BigInteger.cpp
// Vara Neha Madem
// 1872442
// pa6
//CSE101 Tantalo
//-----------------------------------------------------------------------------

#include "BigInteger.h"
#include "List.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>


const int power = 9;
const long base = pow(10.0, power);





// BigInteger()
   // Constructor that creates a new BigInteger in the zero state:
   // signum=0, digits=().
   //BigInteger();
BigInteger::BigInteger() {
  signum = 0;
}





// BigInteger()
   // Constructor that creates a new BigInteger from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
  // BigInteger(std::string s);

/*
will create a BigInteger object representing the integer specified by s. The string s will begin with an
optional sign ('+' or '-'), followed by decimal digit characters {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}. If this constructor
is called on a non-empty string that cannot be parsed as a signed integer, it will throw an
invalid_argument exception (from the standard library <stdexcept> with the error message:
"BigInteger: Constructor: non-numeric string"
If called on an empty string, it will throw an invalid_argument exception with the error message
"BigInteger: Constructor: empty string"
*/


BigInteger::BigInteger(std::string s) {
  if (s.length() == 0) {
    throw std::invalid_argument("BigInteger: constructor, nothing in string s");
  }

//sign
  signum = 1;
  if (s[0] == '-') {
    signum = -1;
    s.erase(s.begin()); 
  } 
  else if (s[0] == '+') {
    s.erase(s.begin());
  }
  s.erase(0, s.find_first_not_of('0'));


  if (s.length() != 0) {
    digits.moveFront();
    int c = s.length(); 
    while (c > 0) {     
      c -= power;
      if (c < 0) {
        c += power;

        std::string d =s.substr(s.find_first_not_of("0"), c); 

        ListElement digitl = stol(d);
        digits.insertAfter(digitl);
        break;
      }
      std::string d = s.substr(c, power);

      //list
      ListElement digitl = stol(d);
      digits.insertAfter(digitl);
    }
  } 


  else {
    signum = 0;
    digits.clear(); 
  }
}





// BigInteger()
   // Constructor that creates a copy of N.
   //BigInteger(const BigInteger& N);

BigInteger::BigInteger(const BigInteger &N) {

  this->digits = N.digits;
    signum = N.signum;
}






// Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is negative,
   // positive or 0, respectively.
int BigInteger::sign() const { 
  return signum; 
}






// compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.


   // first, check, if one is negative is less
int BigInteger::compare(const BigInteger &N) const {

  List a = this->digits;
  List n = N.digits;
 
  if (signum == 0 && N.signum == 0) {
    return 0;
  }
  int check = 0;
  if (signum > N.signum) {
    return 1;
  } 
  else if (signum < N.signum) {
    return -1;
  } 
  else {
    check = signum;
  }


  if ((a.length() > n.length() && check == -1) ||
      (a.length() < n.length() && check == 1)) {
    return -1;
  } 
  else if ((a.length() < n.length() && check == -1) ||
             (a.length() > n.length() && check == 1)) {
    return 1;
  } 

  else {
    a.moveFront();
    n.moveFront();
    for (int i = 0; i < a.length(); i++) {
      ListElement value = a.moveNext();
      ListElement forN = n.moveNext();
      if (value > forN) {
        return (1 * check);
      } 
      else if (value < forN) {
        return (-1 * check);
      }
    }
    return 0;
  }
}




 // Manipulation procedures -------------------------------------------------    -> done

   // makeZero()
   // Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
  digits.clear();
  List d;
  digits = d;
  signum = 0;
}





// negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of
   // this BigInteger positive <--> negative.
void BigInteger::negate() {
  if (signum != 0) {
    signum *= -1;
  }
}




// Helper Functions -----------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
   ListElement x;
   L.moveFront();
   while(L.position()<L.length()){
      x=L.moveNext();
      if(x!= 0){
         L.insertBefore(x*(-1));
      }
   }
}





// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
   S.clear();

   A.moveBack();
   B.moveBack();

   ListElement x;
   ListElement y;

   while(A.position()>0 && B.position()>0){
      x=A.peekPrev();
      y=B.peekPrev();
      S.insertAfter(x + (y* sgn));
      //x=A.movePrev();
      A.movePrev();

      //y=B.movePrev();
      
      B.movePrev();
     
      //cout << x + (y* sgn) << endl;
   }

   while(A.position()>0){
      x=A.peekPrev();
     
      //x=A.movePrev();
      S.insertAfter(x);
       A.movePrev();
   }

   while(B.position()>0){
      y=B.peekPrev();
      
      //y= B.movePrev();
      S.insertAfter((y*sgn));
      B.movePrev();
   }


}






// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().

int normalizeList(List& L)
{

   int carry =0;
   int sign =1;
   L.moveBack();

   ListElement x;

   while(L.position()>0){
      x = L.peekPrev(); //from back, looking at previous element
      x = x + carry;

      carry = 0;   // resetting carry as 0 after adding carry to x

      if(x>base){
         carry = x/base;
         x= x%base;
      }

      else if( x<0){
         if(L.position() == 1){ //if the first element is has x less than 0, whole int is negative
            sign = -1;
         }

         else{
            if(x % base ==0) {
                  carry = x/base;
               }
            else{
               carry = (x/base) -1;// ex: -33, p =2, -33/100 = 0; -1 is the carry
            } 
 
            x= x + -(carry*base);   //ex: x = -1(-1*100) = -33 +100 = 67
         }

      }
      L.setBefore(x); //setting the element before with this new x
      L.movePrev(); // skippung over the changed element
   }


//when the position is  =0 and carry is still >0, insert the remainaing carry in front
   if(carry > 0){
      L.insertBefore(carry);
   }


   L.moveBack();
   //interate through whole list and when comes to front, delete the leading zeros
   while((L.position()> 0) && (L.front() ==0)){
         L.eraseBefore();

   }
      //L.movePrev();


   if(L.length() == 0){
      return 0;
   }

   return sign;


}





// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){

   ListElement x;
   if(m!=1){
      L.moveFront();
      while(L.position()<L.length()){
         x = L.moveNext();
         L.setBefore(m*x);
      }
   }
}






// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
   L.moveBack();
   for(int i=0; i<p; i++){
      L.insertAfter(0);
   }
}






// BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.

BigInteger BigInteger::add(const BigInteger &N) const {
 
  if (N.signum == 0) {
    BigInteger output(*this);
    return output;
  } 
  else if (signum == 0) {
    BigInteger output(N);
    return output;
  }

  // with vectors
  List forN = N.digits;       
  List d = this->digits; 

  BigInteger output;
  output.signum = 1;
  d.moveBack();
  forN.moveBack();
  output.digits.moveFront();


  int one = 0;
  int second = 0;


  if (d.length() < forN.length()) {
    second = d.length();
  } 
  else {
    second = forN.length();
  }

  if (d.length() > forN.length()) {
    one = d.length();
  } 
  else {
    one = forN.length();
  }


//add
  for (int i = 0; i < second; i++) {

    ListElement num1 = d.movePrev() * signum;
    ListElement num2 = forN.movePrev() * N.signum;
    output.digits.insertAfter(num1 + num2);
  }


  for (int j = 0; j < (one - second); j++) {
    if (d.length() > forN.length()) {
      output.digits.insertAfter(d.movePrev() * signum);
    } 
    else {
      output.digits.insertAfter(forN.movePrev() * N.signum);
    }
  }


//normalize
  int carry = 0;
  do {
    output.digits.moveBack();

    carry = 0;
    for (int i = 0; i < output.digits.length(); i++) {

      ListElement element = (output.digits.movePrev() * output.signum) + carry;

      carry = 0;
      if (element >= base) {
        carry = 1;
        element -= base;
      } 
      else if (element < 0) {
        carry = -1;
        element += base;
      }

      if (i == (output.digits.length() - 1) && carry == -1) {
        output.digits.setAfter(element -= base);
        break;
      }

      output.digits.setAfter(element);
    }
    if (carry == 1) {

      output.digits.insertAfter(carry);
    } 
    else if (carry == -1) {
      output.signum *= -1;
    }
  } while (carry == -1);

  output.digits.moveFront();
  for (int k = 0; k < output.digits.length(); k++) {

    ListElement compare = output.digits.moveNext();
    if (compare == 0) {
      output.digits.eraseBefore();
      if (k == (output.digits.length() - 1)) {
        output.signum = 0;
      }
    } 
    else {
      break;
    }
  }
  return output;
}


  




// For sub, A-B. If B > A, then B-A * -1.
// sub() returns BigInteger representing this - N.
BigInteger BigInteger::sub(const BigInteger &N) const {

  BigInteger forN = N;
  BigInteger c = *this;
  BigInteger sub;

  if (c.compare(forN) == 0) {
    sub.makeZero(); 
    return sub;
  } 

  else if (c.compare(forN) == -1) {
    c.negate();
    sub = forN.add(c); 
    sub.negate();
    return sub;
  } 

  else {
    forN.negate();
    sub = c.add(forN); 
    return sub;
  }
}





//given pseudocode

 // BigInteger BigInteger::mult(const BigInteger& N) const{             
 //      List top, bottom;
 //      List C;
 //      BigInteger Prod, A;
 //      if(this->digits.length() <N.digits.length()){
 //         top = N.digits;
 //         bottom = this->digits;
 //      }else{
 //         top = this->digits;
 //         bottom = N.digits;
 //      }

 //      bottom.moveNext();
 //      int size= bottom.length();
 //      for (int shift =0; shift<size; shift++){
 //         C= top;
 //         shiftList(C, shift);
 //         ListElement x= bottom.movePrev();
 //         scalarMultList(C, x);
 //      }

 //      Prod.signum = this->signum * N.signum;

 //      return Prod;
 //   }




   // mult()
   // Returns a BigInteger representing the product of this and N.

BigInteger BigInteger::mult(const BigInteger &N) const {       

  BigInteger first = N;
  BigInteger second; 

  BigInteger thiscopy = *this;
  first.signum = 1;
  thiscopy.signum = 1; 
  thiscopy.digits.moveBack();
  first.digits.moveBack();
  BigInteger newB = BigInteger(); 


  for (int i = 0; i < thiscopy.digits.length(); i++) {

    second = N; 
    ListElement added = 0;

    ListElement scalar = thiscopy.digits.movePrev();
    shiftList(second.digits, i); 
    scalarMultList(second.digits, scalar);
    newB = second.add(newB);
    newB.digits.moveBack();
    added = 0;
   
    for (int j = 0; j < newB.digits.length(); j++) {
      // Normalize
      ListElement newB2 = (newB.digits.movePrev() + added);
      added = (ListElement)floor(newB2 / base);
      newB2 -= added * base;
      newB.digits.setAfter(newB2);
    }
    if (added >= 0) {
      newB.digits.insertAfter(added);
    }
  }

  for (int k = 0; k < newB.digits.length(); k++) {
    ListElement check = newB.digits.moveNext();
    if (check == 0) {
      newB.digits.eraseBefore();
    } 
    else {
      break;
    }
  }
  newB.signum = N.sign() * this->sign();

  return newB;
}







// Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.



std::string BigInteger::to_string() {
 
  if (this->signum == 0) {
    return "0";
  }

  std::string output;
  ListElement digit;
  List thisdigits = this->digits;
  thisdigits.moveFront();
  for (int i = 0; i < thisdigits.length(); i++) {
    digit = thisdigits.moveNext();
    if (digit == 0) {
      std::string out = std::to_string(digit);
 
      while ((int)out.length() != power) {
        out.insert(0, "0");
      }
      output += out;
      continue;
    }
    std::string out = std::to_string(digit);

    while ((int)out.length() != power) {
      out.insert(0, "0");
    }
    output += out;
  }
 std::string completed = output.substr(output.find_first_not_of("0")); 



  if (this->signum == -1) {
    completed.insert(0, "-");
  }
  return completed;
}







//Overriden Operators -----------------------------------------------------



   
   // operator<<()
   // Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, BigInteger N) {
  return stream << N.to_string();
}



// operator==()
   // Returns true if and only if A equals B.
bool operator==(const BigInteger &A, const BigInteger &B) {
  return A.compare(B) == 0;
}



   // operator<()
   // Returns true if and only if A is less than B.
bool operator<(const BigInteger &A, const BigInteger &B) {
  return A.compare(B) == -1;
}



   // operator<=()
   // Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B) {
  return (A.compare(B) == -1 || A.compare(B) == 0);
}



  // operator>()
   // Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B) {
  return A.compare(B) == 1;
}



   // operator>=()
   // Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B) {
  return (A.compare(B) == 1 || A.compare(B) == 0);
}



   // operator+()
   // Returns the sum A+B.
BigInteger operator+(const BigInteger &A, const BigInteger &B) {
  BigInteger output = A.add(B);
  return output;
}


   // operator+=()
   // Overwrites A with the sum A+B.

BigInteger operator+=(BigInteger &A, const BigInteger &B) {
  A = A.add(B);
  return A;
}


   // operator-()
   // Returns the difference A-B.
BigInteger operator-(const BigInteger &A, const BigInteger &B) {
  BigInteger output = A.sub(B);
  return output;
}


   // operator-=()
   // Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B) {
  A = A.sub(B);
  return A;
}


// operator*()
   // Returns the product A*B.
BigInteger operator*(const BigInteger &A, const BigInteger &B) {
  BigInteger output = A.mult(B);
  return output;
}


   // operator*=()
   // Overwrites A with the product A*B.
BigInteger operator*=(BigInteger &A, const BigInteger &B) {
  A = A.mult(B);
  return A;
}




