#include <iostream>
#include "Enigma.h"

Enigma::Enigma()
{
}

Enigma::Enigma(const char* pbConfig, char* reflector, char* rotors, int startPosition)
{
  plugboard = new Plugboard(pbConfig);
}

void Enigma::printPlugboard()
{
  plugboard->print();
}
