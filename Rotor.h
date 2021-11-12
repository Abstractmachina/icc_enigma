#ifndef ROTOR_H
#define ROTOR_H

#include "structs.h"

class Rotor
{
  static const int NUM_LETTERS = 26;
  int _index = -1;
  int _mapping[26];
  int _startPos = 0;
  int _rotation = 0;
  int* _notches = NULL;

  bool isInvalidMapping(int a[], int b[]);
  bool hasValidNumber(ifstream& in, int& counter);

public:
  Rotor();

  int load(char* rotConfig, char* startPos, int index);
  int loadStartPosition(char* startPosConfig, int index);
  bool loadNotches(ifstream& in, int const digitCounter);
  void print();

  void setStartPos(int pos) { _startPos = pos; }
  void setIndex(int index){ if (index < 0) return;
    _index = index; }

  ~Rotor()
  {
    delete[] _notches;
  }

};

#endif
