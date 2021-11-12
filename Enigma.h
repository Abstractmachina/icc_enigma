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

public:
  //Constructors
  Enigma();
  Enigma(int argc, char** argv);

  int load(int argc, char** argv);
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
