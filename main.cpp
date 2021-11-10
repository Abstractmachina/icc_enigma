#include <iostream>
#include <cstdio>

#include "Enigma.h"

using namespace std;

Enigma* enigma;

int main(int argc, char** argv)
{

	enigma = new Enigma("plugboards/II.pb", "reflectors/I.rf", NULL, 0);

	enigma->printPlugboard();
	enigma->printReflector();


	return 0;
}
