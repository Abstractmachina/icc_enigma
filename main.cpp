#include <iostream>
#include <cstdio>

#include "Enigma.h"

using namespace std;

Enigma* enigma;

int main(int argc, char** argv)
{

 	cout<< "The number of arguments is " << argc << endl;

	
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}

	//enigma = new Enigma(argc, argv);
	//enigma = new Enigma("plugboards/II.pb", "reflectors/I.rf", NULL, 0);

	//enigma->printPlugboard();
//	enigma->printReflector();


	return 0;
}
