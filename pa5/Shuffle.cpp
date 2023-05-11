//-----------------------------------------------------------------------------
// Shuffle.cpp
// Vara Neha Madem
// 1872442
// pa5
//CSE101 Tantalo
//main file and shuffle function
//-----------------------------------------------------------------------------
#include <iostream>
#include "List.h"
#include <string>
#include <stdexcept>
#include <iomanip>



using namespace std;

using std::setw;

// Function prototype
//void shuffle(List& D);



void shuffle(List& D)
{
    
        
        int Dlength = D.length();
        int first_length = Dlength / 2;
        int sec_length = Dlength - first_length;
        List first = List();
        List sec = List();
        //List C = List();
        
        D.moveFront();
        //cout << "after D move front" << endl;


        //add the elements from &D to A and B
        for (int i = 0; i < first_length; ++i)
        {
            first.insertBefore(D.peekNext());
            D.moveNext();
            //first.insertBefore(D.moveNext());
        }
        for (int i = 0; i < sec_length; ++i)
        {
            sec.insertBefore(D.peekNext());
            D.moveNext();
        }

        //shuffle
        first.moveFront();
        sec.moveFront();
        D.clear();

       

        while ( (first.position() < first.length()) || (sec.position() < sec.length()) )// while lists are not empty
        {
            if (sec.position() < sec.length()){
                D.insertBefore(sec.peekNext());
            
            sec.moveNext();
            }

            if (first.position() < first.length()){
                D.insertBefore(first.peekNext());
            
            first.moveNext();

        }
        }
        first.clear();
        sec.clear();
    }






int main(int argc, char* argv[]) {

   // Check command line arguments
   if (argc < 2) {
      cerr << "Usage: " << argv[0] << " <max_deck_size>" << endl;
      exit(EXIT_FAILURE);
   }

   // Get the maximum deck size from command line arguments
   int max_deck_size = stoi(argv[1]);

   // Print header for output
   cout<< left << setw(16) <<"deck size" << "shuffle count" << endl;
    cout <<setfill('-') << setw(30) << "" << setfill(' ') <<endl;


   // Iterate over deck sizes from 1 to max_deck_size
   for (int a = 1; a <= max_deck_size; a++) {

      // Create the deck of size n
      List deck;
      for (int i = 0; i < a; i++) {
         deck.insertBefore(i);
      }
      deck.moveFront();

      //cout << "deck front is "<< deck.peekNext() << endl;

      // Shuffle the deck until it returns to its original order
      int shuffle_count = 1;
      //int shuffle_count = 0;


      

     //List compare = deck;
    // List CM1(deck);
     //List original = deck ;



     List original = deck;
      shuffle(deck);


      while(!(deck == original))
       {
         shuffle(deck);
         shuffle_count++;

         //cout << "printing the deck" << endl;
    //cout << deck << endl;
    //cout << "after printing the deck" << endl;

    //cout << "printing the compare" << endl;
    //cout << original << endl;
    //cout << "after printing the compare" << endl;

      }
      cout <<left << setw(16) <<a<< shuffle_count <<endl;


      //cout << n << " " << shuffle_count << endl;
      original.clear();
      deck.clear();
      //cout << n << " " << shuffle_count << endl;
  }

   return 0;



}

