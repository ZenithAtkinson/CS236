#include <iostream>
#include <fstream>
#include "Token.h"
#include "Scanner.h"
//compile with... g++ -Wall -std=c++17 -g main.cpp -o main

using namespace std;

int main(int argc, char** argv) {
  
  //Takes input file (argv[1]), turns it into one string.
    string s;
    string sTotal;
    ifstream in;
    in.open(argv[1]);
    while (getline(in, s)) {
    sTotal += s + "\n";
  }
    in.close();
    //cout << sTotal;
     //why am i getting a seg fault
     
  Scanner SCAN = Scanner(sTotal); 
  Token t = SCAN.scanToken();
  int count = 0;
  while (t.getType() != EOFILE){
    cout << t.toString() << endl;
    t = SCAN.scanToken(); //error happening here
    count++;
      //make this into a while look that goes until EOF
  }
  t = SCAN.scanToken();
  cout << t.toString() << endl;
  count ++;


  cout << "Total tokens = " << count <<endl;
  
}