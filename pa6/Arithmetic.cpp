//-----------------------------------------------------------------------------
// Arithmetic.cpp
// main file
// 1872442
// pa6
// CSE101 Tantalo
//-----------------------------------------------------------------------------
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "BigInteger.h"
#include "List.h"
using namespace std;
#define MAX_LEN 300


int main(int argc, char *argv[]) {


  int line_count;
  ifstream in;
  ofstream out;
  string line;


  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return (EXIT_FAILURE);
  }
  in.open(argv[1]);
  if (!in.is_open()) {
    cerr << "Unable to open file " << argv[1] << " for reading" << endl;
    return (EXIT_FAILURE);
  }
  out.open(argv[2]);
  if (!out.is_open()) {
    cerr << "Unable to open file " << argv[2] << " for writing" << endl;
    return (EXIT_FAILURE);
  }


  BigInteger A;
  BigInteger B;



  line_count = 0;
  while (getline(in, line)) {
    if (line_count == 0) {
      A = BigInteger(line);
    }
    if (line_count == 2) {
      B = BigInteger(line);
    }
    line_count++;
  }



  // A
  out << A << endl << endl;

  // B
  out << B << endl << endl;

  // A + B
  BigInteger C = A + B;
  out << C << endl << endl;

  // A - B
  BigInteger D = A - B;
  out << D << endl << endl;

  // A - A
  BigInteger E = A - A;
  out << E << endl << endl;

  // 3A - 2B
  BigInteger three = BigInteger("3");
  BigInteger two = BigInteger("2");
  BigInteger threeA = (three * A);
  BigInteger twoB = (two * B);
  BigInteger threeaminus2b = (threeA - twoB);
  out << threeaminus2b << endl << endl;

  // AB
  BigInteger F = (A * B);
  out << F << endl << endl;

  // A^2
  BigInteger G = (A * A);
  out << G << endl << endl;

  // B^2
  BigInteger H = (B * B);
  out << H << endl << endl;

  // 9A^4 + 16B^5
  BigInteger nine = BigInteger("9");
  BigInteger sixteen = BigInteger("16");

  // A^4
  BigInteger I = (A * A); // A^2
  BigInteger J = (I * I); // A^2^2 == A^4

  // B^4
  BigInteger K = (B * B); 
  BigInteger L = (K * K); 
  BigInteger M = (L * B); 

  // 9A^4
  BigInteger nineA4 = (J * nine);

  // 16B^5
  BigInteger sixteenB5 = (sixteen * M);

  // 9A4 + 16B5
  BigInteger bigsum = (nineA4 + sixteenB5);
  out << bigsum << endl;


  in.close();
  out.close();

  return (EXIT_SUCCESS);
}
