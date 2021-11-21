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
  Rotor* _rotors; //pointer to uninit array
  int _numRotors = 0;
  string _inputText = "";
  string _outputText = "";

  /*******  Encryption functions  *******/
  /*encrypts chars individually. goes through
  error checking first. if error detected, already
  processed content is saved in output destination*/
  void encryptChar(char& c);
  /*Sub encryption functions taking
  input digit through each component.*/
  void scramblePlugboard(int& digit);
  void scrambleRotors_RL(int& digit);
  void scrambleRotors_LR(int& digit);
  void scrambleReflector(int& digit);
  /*check if char is a letter A-Z.
  returns -1 if char is space, tab or endl.*/
  int checkValidChar(char c);

public:
  /**********  Setup functions *********/
  /*load all components through config files.
  argc = number of arguments in array
  argv = arguments array
  order of args: plugboard, reflector, rotors,
  rotors start position. plugboard can be empty,
  rotors can be null.*/
  int load(int argc, char** argv);

  /********  Encryption functions  *******/
  /*main encryption function. calls all sub encryption
  tasks in the correct order and saves encrypted msg
  to output destination.*/
  int encrypt(ostream& cout, string rawInput);

  /*********  Utility functions **********/
  /*returns stream content as raw string without
  any error checking.*/
  string readInput(istream& cin);

  /***  Debug ***/
  void printIO(); //print input and output msg
  void printPlugboard();
  void printReflector();
  void printRotors();

  //Destructor
  ~Enigma()
  {
    delete plugboard;
    delete reflector;
    delete[] _rotors;
  }
};
#endif
