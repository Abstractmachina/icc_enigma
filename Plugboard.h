/*-------------------------------------------------------
Taole Chen 211120
The Plugboard class is a subcomponent of the Enigma encryption
machine. It contains a set of number pairs (can be null) that
swap with each other pass through.
---------------------------------------------------------*/
#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>

class Plugboard
{
private:
  static const int LETTER_COUNT = 26;
  int _mapping[LETTER_COUNT];

  /*checks if 0-25, doesnt map to itself and is pair*/
  int checkValidNumbers(std::ifstream& in, int& count);
  /*Note: no error checking, as input is assumed to be processed
  beforehand and valid*/
  void createMapping(std::ifstream& in, int numDigits);
  /*check if there is duplicate mapping*/
  int checkValidMapping();

public:
  int load(const char* pbConfig);
  void scramble(int& digit);

  /*  DEBUG */
  void print();
};

#endif
