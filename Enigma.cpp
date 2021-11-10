#include <iostream>
#include <string>
#include "Enigma.h"

Enigma::Enigma(){}

Enigma::Enigma(const char* pbConfig, const char* refConfig, const char* rotors, int startPosition)
{
  plugboard = new Plugboard(pbConfig);
  reflector = new Reflector(refConfig);
}

void Enigma::printPlugboard()
{
  plugboard->print();
}

void Enigma::printReflector()
{
  reflector->print();
}
