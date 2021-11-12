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
  Node<Rotor>* rotors;

  int processInput(int argc, char** argv);

public:
  //Constructors
  Enigma();
  Enigma(const char* pbConfig, const char* refConfig,
    const char* rotConfig, int startPosition);
  Enigma(int argc, char** argv);

  void printPlugboard();
  void printReflector();

  ~Enigma()
  {
    delete plugboard;
    delete reflector;
    for (auto it = rotors; it != NULL; it = it->next)
    {
      auto tmp = it;
      delete it;
      it = tmp;
    }
  }
};
#endif
