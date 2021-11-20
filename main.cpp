#include <iostream>
#include <cstdio>
#include <string>

#include "Enigma.h"
#include "errors.h"

using namespace std;

Enigma* enigma;

int main(int argc, char** argv)
{
	//insufficient amount of arguments
	if (argc < 4)
	{
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
		return INSUFFICIENT_NUMBER_OF_PARAMETERS; // Change number to name specified in error.h LC
	}

	enigma = new Enigma();

	int loadStatus = enigma->load(argc, argv);
	if (loadStatus != 0) return loadStatus;

	//enigma->printRotors();
	//enigma->printReflector();
	//enigma->printPlugboard();

	string rawInput = enigma->readInput(cin);
	int encryptionStatus = enigma->encrypt(cout, rawInput);
	if (encryptionStatus != 0) return encryptionStatus;

	//enigma->printIO();

	return NO_ERROR;
}
