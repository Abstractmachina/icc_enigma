#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <fstream>
#include <iostream>

/*The Plugboard class contains a list of number Pairs
which specify the letters to be swapped with each other.*/
class Plugboard
{
private:
  static const int LETTER_COUNT = 26;
  int _mapping[LETTER_COUNT];

  int checkValidNumbers(std::ifstream& in, int& count);
  int checkValidMapping();
  void createMapping(std::ifstream& in, int numDigits);

public:
  int load(const char* pbConfig);
  void scramble(int& digit);
  void print(); // Remove at the end. LC

  ~Plugboard();


  //OBSOLETE FUN
    bool isInvalidMapping(int a[], int b[], int length);
};

#endif
