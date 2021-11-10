#include <iostream>
#include <string>
#include "Enigma.h"

Enigma::Enigma(){}

Enigma::Enigma(const char* pbConfig, const char* reflector, const char* rotors, int startPosition)
{
  plugboard = new Plugboard(pbConfig);
}

void Enigma::printPlugboard()
{
  plugboard->print();
}
