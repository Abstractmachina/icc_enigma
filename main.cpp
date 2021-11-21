/*-------------------------------------------------------
Taole Chen 211120
This program is a simulation of the Enigma encryption used
by the Nazis in WWII. It encrypts an input message through
a user specified configuration taken from a number of config
files through the command line.
This is a coursework for the Integrated Lab at Imperial College
London.

---------------------------------------------------------*/
#include <iostream>
#include <cstdio>
#include <string>

#include "Enigma.h"
#include "errors.h"

using namespace std;

Enigma* enigma;

int main(int argc, char** argv)
{
	if (argc < 4)//insufficient amount of arguments
	{
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
		return INSUFFICIENT_NUMBER_OF_PARAMETERS; // Change number to name specified in error.h LC
	}

	/*load enigma with configuration files*/
	enigma = new Enigma();
	int loadStatus = enigma->load(argc, argv);
	if (loadStatus != 0) return loadStatus;
	/*process and encrypt input message.
	encrypted message is outputted
	to redirected cout into txt file.*/
	string rawInput = enigma->readInput(cin);
	int encryptionStatus = enigma->encrypt(cout, rawInput);
	if (encryptionStatus != 0) return encryptionStatus;

	return NO_ERROR;
}
