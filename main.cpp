#include <iostream>
#include <cstdio>

#include "Enigma.h"
#include "Plugboard.h"

using namespace std;

Enigma* enigma;

int main(int argc, char** argv)
{

	enigma = new Enigma("plugboards/II.pb", NULL, NULL, 0);

	enigma->printPlugboard();


	return 0;
}
