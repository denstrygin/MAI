//               cppid.cpp
#include <iostream>
#include <iomanip>
#include "fsm.h"
using namespace std;

int main()
{
  tFSM fsm;
///////////////////////
//  Постоить автомат
  addstr(fsm,0,"_",1);
  addrange(fsm,0,'A','Z',1);
  addrange(fsm,0,'a','z',1);
  addstr(fsm,1,"_",1);
  addrange(fsm,1,'A','Z',1);
  addrange(fsm,1,'a','z',1);
  addrange(fsm,1,'0','9',1);
  fsm.final(1);
///////////////////////

  cout << "Number of states = " << fsm.size()
       << "\n";

  while(true)
 {
  char input[81];
  cout << ">";
  cin.getline(input,81);
  if(!*input) break;
  int res = fsm.apply(input);
  cout << setw(res?res+1:0) << "^"
       << endl;
 }
 return 0;
}
    addstr(Adec,0,"-",1);
    addstr(Adec,0,"+",1);
    addrange(Adec,1,'0','9',1);
    addstr(Adec,1,".",2);
    addrange(Adec,2,'0','9',3);
    addrange(Adec,3,'0','9',3);
    addstr(Adec,3,"e",4);
    addstr(Adec,3,"E",4);
    addstr(Adec,2,"e",4);
    addstr(Adec,2,"E",4);
    addstr(Adec,4,"+",5);
    addstr(Adec,4,"-",5);
    addrange(Adec,5,'0','9',6);
    addrange(Adec,6,'0','9',6);
    Adec.final(6);
