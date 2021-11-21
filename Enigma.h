/*-------------------------------------------------------
Taole Chen 211120
Enigma class contains all functional components (plugboard,
reflector, rotors) of the enigma encryption machine
developed in WWII.
-processes input text from redirected cin ostream
-saves encrypted message to output file.
-loads components from config files and aggregates all
error checks.
-coordinates encryption process.
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


  int checkValidChar(char c);
  /*Encryption functions*/
  void encryptChar(char& c);
  /*Sub encryption functions taking
  input digit through each component.*/
  void scramblePlugboard(int& digit);
  void scrambleRotors_RL(int& digit);
  void scrambleRotors_LR(int& digit);
  void scrambleReflector(int& digit);

public:
  //Constructors

  /**********  Setup functions ***********/
  int load(int argc, char** argv);

  /*Encryption functions*/
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
