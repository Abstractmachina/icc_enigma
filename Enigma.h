#ifndef ENIGMA_H
#define ENIGMA_H

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

#include <string>

class Enigma
{
  Plugboard* plugboard;
  Reflector* reflector;
  Rotor* _rotors;
  int _numRotors = 0;
  string _inputText = "";

  int encryptChar(char& c);

public:
  //Constructors
  Enigma();

  int load(int argc, char** argv);
  int encrypt(istream& cin, string& output);
  int cleanInputText(istream& cin, string& message);

  void printPlugboard();
  void printReflector();
  void printRotors();

  ~Enigma()
  {
    delete plugboard;
    delete reflector;
    delete[] _rotors;
  }
};
#endif
