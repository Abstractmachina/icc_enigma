#ifndef ROTOR_H
#define ROTOR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


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
  int _index = -1; //rotor index within assembly. left-most = 0;
  int _mapping[26];
  int _startPos = 0;
  int _rotation = 0;
  Node_int* _notches = NULL;

  /*check if numbers are integers and between 0-25
   and whether all inputs are mapped.*/
  int checkValidNumbers(ifstream& in);

public:
  Rotor();
  int load(char* rotConfig, char* startPos, int index);
  int loadStartPosition(char* startPosConfig, int index);
  void createMapping(ifstream& in);
  void scramble(int& digit, bool step, bool& isNotch, bool reverse);

  void print();
  void printNotches();
  void setStartPos(int pos) { _startPos = pos; }
  void setIndex(int index){ if (index < 0) return;_index = index; }


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
