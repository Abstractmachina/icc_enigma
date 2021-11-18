#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "structs.h"

class Reflector
{
private:
  static const int NUM_LETTERS = 26;
  int _mapping[NUM_LETTERS];

  bool checkValidMapping();

public:
  Reflector();

  void scramble(int& digit);
  int load(const char* refConfig);
  void print();

  ~Reflector()
  {
  }
};

#endif
