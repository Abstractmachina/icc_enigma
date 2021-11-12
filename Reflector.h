#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "structs.h"

class Reflector
{
  static const int MAX_PAIR = 13;
  NumPair* pairs[MAX_PAIR];

public:
  Reflector(const char* refConfig);

  int load(const char* refConfig);
  void print();

  ~Reflector()
  {
    for (int i = 0; i < MAX_PAIR; i++)
    {
      delete pairs[i];
    }
  }
};

#endif
