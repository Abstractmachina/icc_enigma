/*-------------------------------------------------------
                    Taole Chen 20 Nov 2021
Enigma class contains all functional components (plugboard,
reflector, rotors) of the enigma encryption machine
developed in WWII.
-processes input text from 


---------------------------------------------------------*/


#ifndef ENIGMA_H
#define ENIGMA_H

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

class Enigma
{
private:
  Plugboard* plugboard;
  Reflector* reflector;
  Rotor* _rotors;
  int _numRotors = 0;
  string _inputText = "";
  string _outputText = "";

  /*Setup functions*/

  int checkValidChar(char c);

  /*Encryption functions*/
  void encryptChar(char& c);
  void scramblePlugboard(int& digit);
  void scrambleRotors_RL(int& digit);
  void scrambleRotors_LR(int& digit);
  void scrambleReflector(int& digit);

public:
  //Constructors
  Enigma();

  /**********  Setup functions ***********/
  int load(int argc, char** argv);

  /*Encryption functions*/
  int encrypt(istream& cin, ostream& cout, string& output); //OBSOLETE
  int encrypt(ostream& cout, string rawInput);

  /*Utility functions*/
  string readInput(istream& cin);
  void printIO(); //print input and output msg
  void printPlugboard();
  void printReflector();
  void printRotors(); //

  //Destructor
  ~Enigma()
  {
    delete plugboard;
    delete reflector;
    delete[] _rotors;
  }
};
#endif
