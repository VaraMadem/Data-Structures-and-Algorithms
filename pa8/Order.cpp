//-----------------------------------------------------------------------------
// Order.cpp
// main file
// 1872442
// pa7
// CSE101 Tantalo
//-----------------------------------------------------------------------------

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Dictionary.h"
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

 
  Dictionary D;


  line_count = 0;
  while (getline(in, line)) {
    line_count++;
    D.setValue(line, line_count);
  }
  out << D << endl;
  string prestring = D.pre_string();
  out << prestring;

  return (EXIT_SUCCESS);
}


