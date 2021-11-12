#include <iostream>
#include <string>

#include "Enigma.h"

Enigma::Enigma()
{

}

Enigma::Enigma(int argc, char** argv)
{
  load(argc, argv);
}

int Enigma::load(int argc, char** argv)
{
  plugboard = new Plugboard();
  int pb = plugboard->load(argv[1]);

  reflector = new Reflector();
  reflector->load(argv[2]);


  _numRotors = argc - 4; //-reflector, plugboard, startpos and filename
  _rotors = new Rotor[_numRotors];
  for (int i = 0; i < _numRotors; i++)
  {
    _rotors[i] = *(new Rotor());
    _rotors[i].load(argv[i+3], argv[argc-1], i);
  }
  return 0;
}

void Enigma::printPlugboard() {plugboard->print(); }
void Enigma::printReflector(){ reflector->print(); }
void Enigma::printRotors() { for (int i = 0; i < _numRotors; i++) _rotors[i].print(); }
