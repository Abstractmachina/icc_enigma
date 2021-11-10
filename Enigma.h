#ifndef ENIGMA_H
#define ENIGMA_H

#include "Plugboard.h"

class Enigma
{
  Plugboard* plugboard;

public:
  //Constructors
  Enigma();
  Enigma(const char* pbConfig, const char* reflector, const char* rotors, int startPosition);

  void printPlugboard();

  ~Enigma()
  {
    delete plugboard;
  }

};


#endif
