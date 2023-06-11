//-----------------------------------------------------------------------------
// WordFrequency.cpp
// main file
// 1872442
// pa8
// CSE101 Tantalo
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300


int main(int argc, char * argv[]){

   int token_count, line_count;
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }




   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }




    Dictionary sol;

   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      len = line.length();
      
      token_count = 0;
      tokenBuffer = "";

      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);

      
      while( token!="" ){  
         token_count++;
      for (int z = 0; z < (int) token.length(); z++) {
          token[z] = tolower(token[z]);
      }

       if (sol.contains(token)) {
            sol.setValue(token, sol.getValue(token)+1);
        }
        else {
            sol.setValue(token, 1);
        }


         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);

      }


   }

   out << sol << endl;


   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

