#ifndef ENIGMA_H
#define ENIGMA_H

#include "Plugboard.h"

class Enigma
{
private:
  Plugboard* plugboard;
public:
  //Constructors
  Enigma();
  Enigma(const char* pbConfig, char* reflector, char* rotors, int startPosition);

  void printPlugboard();


};


#endif
