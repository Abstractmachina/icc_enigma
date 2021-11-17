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
	if (argc < 3)
	{
		cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}

	enigma = new Enigma();
	int loadStatus = enigma->load(argc, argv);
	if (loadStatus != 0) return loadStatus;

	//enigma->printRotors();
	//enigma->printReflector();
	//enigma->printPlugboard();

	string message = "";
	int encryptionStatus = enigma->encrypt(cin, cout, message);
	if (encryptionStatus != 0) return encryptionStatus;

	enigma->printIO();
	cout << message;

	return 0;
}
