#ifndef ROTOR_H
#define ROTOR_H

#include "structs.h"

class Rotor
{
  int _mapping[26];
  int _startPos = 0;
  int _rotation = 0;
  Node<int>* _notches = NULL;

public:
  Rotor(char* rotConfig);

  int load(char* rotConfig);
  void setStartPos(int pos) { _startPos = pos; }
};

#endif
