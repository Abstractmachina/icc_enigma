#include <iostream>
#include <cstdio>
#include <string>

#include "Enigma.h"

using namespace std;

Enigma* enigma;

int main(int argc, char** argv)
{
	enigma = new Enigma();

	int loadStatus = enigma->load(argc, argv);
	if (loadStatus != 0) return loadStatus;

	//enigma->printRotors();
	//enigma->printReflector();
	//enigma->printPlugboard();

	string out = "";
	int encryptionStatus = enigma->encrypt(cin, out);
	if (encryptionStatus != 0) return encryptionStatus;

	//cerr << "Output: " << out << endl;
	cout << out;

	return 0;
}
