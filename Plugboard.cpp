#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>

#include "Plugboard.h"
//#include "NumPair.h"

using namespace std;


Plugboard::Plugboard(const char* pbConfig)
{
  load(pbConfig);
}

/*load number pairs from a config file*/
void Plugboard::load(const char* pbConfig){
  ifstream in(pbConfig);
  if (!in) {
    cout << "Loading plugboard failed!\n";
  }

  while (!in.eof()){
    int a = -1;
    int b = -1;
    in >> a;
    in >> b;
    if (a == -1 || b == -1) break;
    NumPair* pair = new NumPair(a,b);
    //_numberPairs[count++] = pair;

    if (numPairList == NULL)
      numPairList = new NumPairListNode(pair);
    else
    {
      NumPairListNode* node = numPairList;
      while (node->next != NULL) node = node->next;
      node->next = new NumPairListNode(pair);
    }

  }
  in.close();
}

void Plugboard::print(){
  cout << "Plugboard\n\nNumber Pairs:\n";
  for (auto it = numPairList; it != NULL; it = it->next)
  {
    cout << it->numPair->getString() << endl;
  }
  /*
  for (int i = 0; i < _BUFFER_PLUGBOARD; i++){
    cout << _numberPairs[i]->getString() << endl;
  }
  */
}
