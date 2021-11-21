/*-------------------------------------------------------
Taole Chen 211120
The Rotor class is a subcomponent of the Enigma encryption machine.
it houses a user-specified scrambled mapping of the alphabet
and contains all mechanical functionality of the rotor object.
---------------------------------------------------------*/

#ifndef ROTOR_H
#define ROTOR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Rotor
{
private:
  static const int NUM_LETTERS = 26;
  int _index = -1; //rotor index within assembly. left-most = 0;
  int _mapping[26];
  int _startPos = 0;
  int _rotation = 0;
  /*integer linked list to store notches.
  defined here as not used anywhere else*/
  struct Node_int
  {
    int val = -1;
    Node_int* next = NULL;
    Node_int(int input) : val(input){}
  };
  Node_int* _notches = NULL;

  /*********  SETUP FUNCTIONS *********/
  int loadStartPosition(char* startPosConfig, int index);
  void createMapping(std::ifstream& in);
  /*check if numbers are integers and between 0-25
   and whether all inputs are mapped.*/
  int checkValidNumbers(std::ifstream& in);
  /*check if any numbers are mapped twice*/
  int checkValidMapping();

  /*****  Encryption Functions  *******/
  bool isNotch(int offset);

public:
  Rotor(); //required for uninit array
  int load(char* rotConfig, char* startPosConfig, int index);
  void scramble(int& digit, bool step, bool& isNotch, bool reverse);

  /*DEBUG*/
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
