//#include <fstream>
#include <cstdio>
//#include <iostream>
#include <string>

#include "Plugboard.h"
#include "errors.h"

using namespace std;

//CONSTRUCTORS

/*************FUNCTIONS****************/
//What does this function do? LC
void Plugboard::scramble(int& digit)
{
  digit = _mapping[digit];
}

/*load number pairs from a config file*/
int Plugboard::load(const char* pbConfig)
{
  ifstream in(pbConfig);
  if (!in) {
    cerr << "Loading plugboard failed!\n";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  //check for even number of values -> pairs
  int count = 0; //count of number found in config file.
  int validNumStatus = checkValidNumbers(in, count);
  if (validNumStatus != 0) return validNumStatus;

  createMapping(in, count);

  in.close();

  //check if closing file was successful. LC

  int validMappingStatus = checkValidMapping();
  if (validMappingStatus != 0) return validMappingStatus;

  return 0;
}

int Plugboard::checkValidNumbers(ifstream& in, int& count)
{
  count = 0;
  int first = -1; // store first letter to compare with second of pair
  while (!in.eof())
  {
    int temp = -1;
    in >> temp;
    //check for non-numberic val
    if (in.fail() && !in.eof())
    {
      cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
      return NON_NUMERIC_CHARACTER;
    }
    if (temp == -1) break; // end of file

    if (temp < 0 || temp > 25)
    {
      cerr << "Invalid Index in plugboard config!\n";
      return INVALID_INDEX;

    }
    //check if number maps to itself;
    if (count % 2 == 0 || count == 0) first = temp; //store first number of pair
    else // compare first and second number
    {
      if (first == temp)
      {
        cerr << "Number maps to itself in plugboard file plugboard.pb" << endl;
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
    if (temp != -1) count++;
  }
  //check if there is even number and less than 26 in total
  if ( (count % 2 != 0 && count != 0) || count > 26)
  {
    cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!

  return NO_ERROR;
}

void Plugboard::createMapping(ifstream& in, int numDigits)
{
  //init with standard mapping
  for (int i = 0; i < LETTER_COUNT; i++)_mapping[i] = i;
  //map pairs
  for (int i = 0; i < numDigits/2; i++) //
  {
    int A = -1;
    int B = -1;
    in >> A;
    in >> B;

    _mapping[A] = B;
    _mapping[B] = A;
  }
}

int Plugboard::checkValidMapping()
{
  for (int i = 0; i < LETTER_COUNT - 1; i++)
  {
    for (int j = i + 1; j < LETTER_COUNT; j++)
    {
      if (_mapping[i] == _mapping[j])
      {
        cerr << "Duplicate mapping\n";
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
  }
  return 0;
}


// Make sure ti=o remove function at end. LC
void Plugboard::print(){
  cerr << "Plugboard Mapping:\n";
  for (int i = 0; i < LETTER_COUNT; i++)
  {
    cerr << "{ " << i << " ; " << _mapping[i] << " }\n";
  }
  cerr << endl;
}
