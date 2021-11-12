#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "structs.h"

/*The Plugboard class contains a list of number Pairs
which specify the letters to be swapped with each other.*/
class Plugboard
{
  Node<NumPair>* numPairList; //linked list of number pairs

public:
  Plugboard(const char* pbConfig);

  /*load number pairs from a config file*/
  void load(const char* pbConfig);
  void print();

  ~Plugboard();
};

#endif
