#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>

#include "Plugboard.h"
//#include "NumPair.h"

using namespace std;

//CONSTRUCTORS
Plugboard::Plugboard(const char* pbConfig)
{
  load(pbConfig);
}

/*************FUNCTIONS****************/

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
  cout << "Plugboard Pairs:\n";
  for (auto it = numPairList; it != NULL; it = it->next)
  {
    cout << it->numPair->getString() << endl;
  }
}

/***********************DESTRUCTOR**************************/
Plugboard::~Plugboard()
{
  for (auto it = numPairList; it != NULL; it = it->next)
  {
    auto tmp = it->next;
    delete it;
    it = tmp;
  }
}
