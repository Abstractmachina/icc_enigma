#include <iostream>
#include <string>

#include "Enigma.h"

Enigma::Enigma(){}


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
  _numRotors = argc - 4; //-reflector, plugboard, startpos and filename
  _rotors = new Rotor[_numRotors];

  for (int i = 0; i < _numRotors; i++)
  {
    _rotors[i] = *(new Rotor());
    int rotorLoadStatus = _rotors[i].load(argv[i+3], argv[argc-1], i);
    if (rotorLoadStatus != 0) return rotorLoadStatus;
  }

  return 0;
}

/*Main encryption function*/
int Enigma::encrypt(istream& cin, string& output)
{
  int cleanStatus = cleanInputText(cin, output);
  if (cleanStatus != 0) return cleanStatus;

  //cerr << "Input: " << output <<endl;

  for (auto i =0; i < (int)output.length(); i++) encryptChar(output[i]);
  return 0;
}

int Enigma::encryptChar(char& c)
{
  //cerr << "Char: " << c<< endl;
  int digit = c - 65;

  scramblePlugboard(digit);
  scrambleRotors_RL(digit);
  scrambleReflector(digit);
  scrambleRotors_LR(digit);
  scramblePlugboard(digit);

  //convert back to char
  c = digit + 65;

  return 0;
}

void Enigma::scramblePlugboard(int& digit)
{
  plugboard->scramble(digit);
  //cerr << "pb scramble: " << digit << endl;
}

void Enigma::scrambleRotors_RL(int& digit)
{
  /*ROTORS SCRAMBLE RIGHT TO LEFT*/
  if (_rotors != NULL)
  {
    for (int i = _numRotors-1; i >= 0; i--)
    {
      bool isNotch = false;
      if (i == _numRotors-1)
        _rotors[i].scramble(digit, true, isNotch);//first rotor always steps
      else
      {
        if (isNotch)_rotors[i].scramble(digit, true, isNotch);
        else _rotors[i].scramble(digit, false, isNotch);
      }
      //cerr << "Rotor " << i << " scramble: " << digit << endl;
    }
  }
}

void Enigma::scrambleRotors_LR(int& digit)
{
  if (_rotors != NULL)
  {
    for (int i = 0; i <_numRotors; i++)
    {
      bool dummyNotch = false;
      _rotors[i].scramble(digit, false, dummyNotch);
      //cerr << "Rotor " << i << " scramble: " << digit << endl;
    }
  }
}

void Enigma::scrambleReflector(int& digit)
{
  reflector->scramble(digit);
  //cerr << "ref scramble: " << digit << endl;
}



/************** UTILITY FUNCTIONS **********/


int Enigma::cleanInputText(istream& cin, string& message)
{
  for (auto c = cin.get(); !cin.eof();)
  {
    if (c == ' ' || c == '	' || c =='\n')
		{
			c = cin.get();
			continue;
		}
    if (c < 65 || c > 90)
    {
      cerr << message << endl;
      //cerr << (char) c << " is not a valid input character (input characters must be upper case letters A-Z)!\n";
      return 2;
    }
		message += c;
		c = cin.get();
  }

  return 0;
}

void Enigma::printPlugboard() {plugboard->print(); }
void Enigma::printReflector(){ reflector->print(); }
void Enigma::printRotors() { for (int i = 0; i < _numRotors; i++) _rotors[i].print(); }
