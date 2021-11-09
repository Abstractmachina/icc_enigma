//#include <iostream>
#include <fstream>
#include <cstdio>

#include "Plugboard.h"

using namespace std;


Plugboard::Plugboard(const char* pbConfig){
  load(pbConfig);
}

/*load number pairs from a config file*/
void Plugboard::load(const char* pbConfig){
  ifstream in(pbConfig);
  if (!in) {
    cout << "Loading plugboard failed!\n";
  }
  int count = 0;
  while (!in_stream.eof() && count < _BUFFER_PLUGBOARD){
    in >> _numberPairs[count++];
  }
  in.close();
}

void Plugboard::print(){
  cout << "Plugboard\n\nNumber Pairs:\n";
  for (int i = 0; i < _BUFFER_PLUGBOARD; i++){
    cout << _numberPairs[i] << endl;
  }
}
