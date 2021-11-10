#ifndef ENIGMA_H
#define ENIGMA_H

#include "Plugboard.h"
#include "Reflector.h"

class Enigma
{
  Plugboard* plugboard;
  Reflector* reflector;

public:
  //Constructors
  Enigma();
  Enigma(const char* pbConfig, const char* refConfig, const char* rotConfig, int startPosition);

  void printPlugboard();
  void printReflector();

  ~Enigma()
  {
    delete plugboard;
    delete reflector;
  }
};
#endif
