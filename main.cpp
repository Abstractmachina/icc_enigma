#include <iostream>
#include <cstdio>
#include <string>

#include "Enigma.h"

using namespace std;

Enigma* enigma;

int main(int argc, char** argv)
{
	cerr << "number of args: " << argc << '\n';
	cerr << "arguments:\n";
	for (int i = 0; i < argc; i++)
	{
		cerr << argv[i] << endl;
	}

	string inTxt = "";
	char c = cin.get();
	while (!cin.eof())
	{
		inTxt += c;
		cerr << c;
		c = cin.get();

	}

	cout << inTxt;

	enigma = new Enigma();
	enigma->load(argc, argv);
	enigma->printPlugboard();
	enigma->printReflector();
	enigma->printRotors();

	return 0;
}
