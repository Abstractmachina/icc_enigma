#ifndef ROTOR_H
#define ROTOR_H

#include <fstream>
#include <iostream>


using namespace std;

struct Node_int
{
  int val = -1;
  Node_int* next = NULL;
  Node_int(int input) : val(input){}
};

class Rotor
{
  static const int NUM_LETTERS = 26;
  int _index = -1;
  int _mapping[26];
  int _startPos = 0;
  int _rotation = 0;
  Node_int* _notches = NULL;

  int isInvalidMapping(int a[], int b[]);
  int checkValidNumbers(ifstream& in);

public:
  Rotor();

  void scramble(int& digit, bool step, bool& isNotch, bool reverse);
  int load(char* rotConfig, char* startPos, int index);
  int loadStartPosition(char* startPosConfig, int index);
  void createMapping(ifstream& in);


  void print();
  void printNotches();
  void setStartPos(int pos) { _startPos = pos; }
  void setIndex(int index){ if (index < 0) return;_index = index; }

  //OBSOLETE
  int loadNotches(ifstream& in, int const digitCounter);

  ~Rotor()
  {
    for (auto it = _notches; it != NULL; it = it->next)
    {
      auto tmp = it;
      delete it;
      it = tmp->next;
    }
  }

};

#endif
