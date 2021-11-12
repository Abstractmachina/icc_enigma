#include <iostream>
#include <string>

#include "Enigma.h"

Enigma::Enigma(){}

Enigma::Enigma(const char* pbConfig, const char* refConfig,
  const char* rotors, int startPosition)
{
  plugboard = new Plugboard(pbConfig);
  reflector = new Reflector(refConfig);
}

Enigma::Enigma(int argc, char** argv)
{
  processInput(argc, argv);
}

void Enigma::printPlugboard()
{
  plugboard->print();
}

void Enigma::printReflector()
{
  reflector->print();
}

int Enigma::processInput(int argc, char** argv)
{

  plugboard = new Plugboard(argv[1]);
  reflector = new Reflector(argv[2]);

  for (int i = 3; i < argc; i++)
  {
    Rotor* rot = new Rotor(argv[i]);
    rotors->next = new Node<Rotor>(rot);
  }

  return 0;
}
