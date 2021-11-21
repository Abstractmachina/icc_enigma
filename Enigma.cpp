#include <iostream>
#include <string>
#include <cstdio>

#include "Enigma.h"
#include "errors.h"

using namespace std;

int Enigma::load(int argc, char** argv)
{
  /*LOAD PLUGBOARD*/
  plugboard = new Plugboard();
  int pbStatus = plugboard->load(argv[1]);
  if (pbStatus != 0) return pbStatus;

  /*LOAD REFLECTOR*/
  reflector = new Reflector();
  int refStatus = reflector->load(argv[2]);
  if (refStatus != 0) return refStatus;

  /*LOAD ROTORS*/
  _numRotors = argc - 4; //subtract pb, ref, exe name, start pos
  _rotors = new Rotor[_numRotors];
  for (int i = 0; i < _numRotors; i++)
  {
    _rotors[i] = *(new Rotor());
    int rotorLoadStatus = _rotors[i].load(argv[i+3], argv[argc-1], i);
    if (rotorLoadStatus != 0) return rotorLoadStatus;
  }

  return NO_ERROR;
}

/***********  Encryption functions ************************/
string Enigma::readInput(istream& cin)
{
  string rawInput = "";

  for (auto c = cin.get(); !cin.eof();)
  {
    rawInput += c;
    c = cin.get();
  }
  return rawInput;
}

int Enigma::encrypt(ostream& cout, string rawInput)
{
  for (int i = 0; i < (int)rawInput.length(); i++)
  {
    char c = rawInput[i];
    int checkCharStatus = checkValidChar(c);
    if (checkCharStatus != 0 && checkCharStatus != -1) return checkCharStatus;
    //-1 if space, tab or endl, so do nothing.
    if (checkCharStatus == 0)
    {
      _inputText += c;
      encryptChar(c);
      _outputText += c;
      cout << c;
    }
  }
  return NO_ERROR;
}

int Enigma::checkValidChar(char c)
{
  if (c == ' ' || c == '	' || c =='\n')
  {
    c = cin.get();
    return -1;
  }
  if (c < 'A' || c > 'Z')
  {
    cerr << (char) c << " is not a valid input character (input characters must be upper case letters A-Z)!\n";
    return INVALID_INPUT_CHARACTER;
  }
  return NO_ERROR;
}

void Enigma::encryptChar(char& c)
{
  int digit = c - 'A';
  scramblePlugboard(digit);
  scrambleRotors_RL(digit);
  scrambleReflector(digit);
  scrambleRotors_LR(digit);
  scramblePlugboard(digit);
  c = digit + 'A';//convert back to char
}

void Enigma::scramblePlugboard(int& digit) {plugboard->scramble(digit);}

void Enigma::scrambleRotors_RL(int& digit)
{
  /*ROTORS SCRAMBLE RIGHT TO LEFT*/
  if (_rotors != NULL)
  {
    bool isNotch = false;
    for (int i = _numRotors-1; i >= 0; i--)
    {
      if (i == _numRotors-1) //rightmost rotor
        _rotors[i].scramble(digit, true, isNotch, false);//first rotor always steps
      else
      {
        if (isNotch)
        {
          _rotors[i].scramble(digit, true, isNotch, false);
        }
        else _rotors[i].scramble(digit, false, isNotch, false);
      }
    }
  }
}

void Enigma::scrambleRotors_LR(int& digit)
{
  if (_rotors != NULL)
  {
    for (int i = 0; i <_numRotors; i++)
    {
      bool dummyNotch = false; //notch is never engage in reverse
      _rotors[i].scramble(digit, false, dummyNotch, true);
      //cerr << "Rotor " << i << " scramble: " << digit << endl;
    }
  }
}

void Enigma::scrambleReflector(int& digit) {reflector->scramble(digit);}


/************** UTILITY FUNCTIONS **********/

void Enigma::printIO()
{
  cerr << "Input: " << _inputText << endl;
  cerr << "Output: " << _outputText << endl;
}
void Enigma::printPlugboard() {plugboard->print(); }
void Enigma::printReflector(){ reflector->print(); }
void Enigma::printRotors() { for (int i = 0; i < _numRotors; i++) _rotors[i].print(); }
