/*-------------------------------------------------------
Taole Chen 211120
The Reflector class is a subcomponent of the Enigma encryption
machine. It contains 13 number pairs (must all be assigned)
that swap with each other on pass through.
---------------------------------------------------------*/
#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "structs.h"

class Reflector
{
private:
  static const int DIGIT_COUNT = 26;
  int _mapping[DIGIT_COUNT];

  /*Note: no error checking, as input is assumed to be processed
  beforehand and valid*/
  void createMapping(ifstream& in);
  /*check if there are exactly 13 pairs, 0-25*/
  int checkValidNumbers(ifstream& in);
    /*Check if any number is mapped to itself or duplicate*/
  int checkValidMapping();

public:
  void scramble(int& digit);
  int load(const char* refConfig);
  /*  DEBUG */
  void print();

  ~Reflector()
  {
  }
};

#endif
