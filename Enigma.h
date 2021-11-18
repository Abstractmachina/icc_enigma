#ifndef ENIGMA_H
#define ENIGMA_H

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

#include <string>

class Enigma
{
private:
  const int ASCII_A = 65;
  const int ASCII_Z = 90;
  Plugboard* plugboard;
  Reflector* reflector;
  Rotor* _rotors;
  int _numRotors = 0;
  string _inputText = "";
  string _outputText = "";

  /*Setup functions*/
  int cleanInputText(istream& cin, ostream& cout, string& message);
  /*Encryption functions*/
  int encryptChar(char& c);
  void scramblePlugboard(int& digit);
  void scrambleRotors_RL(int& digit);
  void scrambleRotors_LR(int& digit);
  void scrambleReflector(int& digit);

public:
  //Constructors
  Enigma();

  /*Setup functions*/
  int load(int argc, char** argv);

  /*Encryption functions*/
  int encrypt(istream& cin, ostream& cout, string& output);

  /*Utility functions*/
  void printIO(); //print input and output msg
  void printPlugboard();
  void printReflector();
  void printRotors();

  //Destructor
  ~Enigma()
  {
    delete plugboard;
    delete reflector;
    delete[] _rotors;
  }
};
#endif
