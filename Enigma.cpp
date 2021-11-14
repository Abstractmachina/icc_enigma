#include <iostream>
#include <string>

#include "Enigma.h"

Enigma::Enigma(){}


int Enigma::load(int argc, char** argv)
{
  plugboard = new Plugboard();
  int pbStatus = plugboard->load(argv[1]);
  if (pbStatus != 0) return pbStatus;

  reflector = new Reflector();
  int refStatus = reflector->load(argv[2]);
  if (refStatus != 0) return refStatus;

  _numRotors = argc - 4; //-reflector, plugboard, startpos and filename
  _rotors = new Rotor[_numRotors];
  for (int i = 0; i < _numRotors; i++)
  {
    _rotors[i] = *(new Rotor());
    _rotors[i].load(argv[i+3], argv[argc-1], i);
  }
  return 0;
}

int Enigma::encrypt(istream& cin, string& output)
{
  int cleanStatus = cleanInputText(cin, output);
  if (cleanStatus != 0) return cleanStatus;

  cerr << "Input: " << output <<endl;

  for (auto i =0; i < (int)output.length(); i++) encryptChar(output[i]);
  return 0;
}

int Enigma::encryptChar(char& c)
{
  cerr << "Char: " << c<< endl;
  int digit = c - 65;

  //pass Plugboard
  plugboard->scramble(digit);
  cerr << "pb scramble: " << digit << endl;

  //pass rotors right to left
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
    cerr << "Rotor " << i << " scramble: " << digit << endl;
  }

  //pass reflector
  reflector->scramble(digit);
  cerr << "ref scramble: " << digit << endl;

  //pass rotor left to right
  for (int i = 0; i <_numRotors; i++)
  {
    bool dummyNotch = false;
    _rotors[i].scramble(digit, false, dummyNotch);
    cerr << "Rotor " << i << " scramble: " << digit << endl;
  }

  //pass plugboard
  plugboard->scramble(digit);
  cerr << "pb scramble: " << digit << endl;

  //convert to char
  c = digit + 65;

  return 0;
}

int Enigma::cleanInputText(istream& cin, string& message)
{
	char c = cin.get();
	while (!cin.eof())
	{
		if (c == ' ' || c == '	' || c =='\n')
		{
			c = cin.get();
			continue;
		}
    if (c < 65 || c > 90)
    {
      cerr << "Invalid Input! Must be upper case letters A-Z.\n";
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
