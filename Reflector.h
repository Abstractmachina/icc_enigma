#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "structs.h"

class Reflector
{
  static const int MAX_PAIR = 13;

  int _mapping[MAX_PAIR*2];

  bool checkInvalidMapping(int a[MAX_PAIR], int b[MAX_PAIR]);

public:
  Reflector();
  Reflector(const char* refConfig);

  void scramble(int& digit);
  int load(const char* refConfig);
  void print();

  ~Reflector()
  {
  }
};

#endif
