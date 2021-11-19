//#include <fstream>
#include <cstdio>
//#include <iostream>
#include <string>

#include "Plugboard.h"
#include "errors.h"

using namespace std;

//CONSTRUCTORS

/*************FUNCTIONS****************/

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
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  //check for even number of values -> pairs
  int count = 0; //count of number found in config file.
  checkValidNumbers(in, count);

  //init mapping
  for (int i = 0; i < LETTER_COUNT; i++)_mapping[i] = i;
  //map pairs
  for (int i = 0; i < count/2; i++) //
  {
    int A = -1;
    int B = -1;
    in >> A;
    in >> B;

    _mapping[A] = B;
    _mapping[B] = A;
  }

  in.close();

  return 0;
}

void Plugboard::checkValidNumbers(ifstream& in, int& count)
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
      throw NON_NUMERIC_CHARACTER;
    }
    if (temp == -1) break; // end of file

    if (temp < 0 || temp > 25)
    {
      cerr << "Invalid Index in plugboard config!\n";
      throw INVALID_INDEX;

    }
    //check if number maps to itself;
    if (count % 2 == 0 || count == 0) first = temp; //store first number of pair
    else // compare first and second number
    {
      if (first == temp)
      {
        cerr << "Number maps to itself in plugboard file plugboard.pb" << endl;
        throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
    if (temp != -1) count++;
  }
  //check if there is even number and less than 26 in total
  if ( (count % 2 != 0 && count != 0) || count > 26)
  {
    cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
    throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  }

  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!
}

void Plugboard::checkValidMapping()
{
  for (int i = 0; i < LETTER_COUNT - 1; i++)
  {
    for (int j = i + 1; j < LETTER_COUNT; j++)
    {
      if (_mapping[i] == _mapping[j])
      {
        cerr << "Duplicate mapping\n";
        throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
  }
}

//OBSOLETE
/*Check if any numbers are mapped to themselves or multiple times.*/
bool Plugboard::isInvalidMapping(int a[], int b[], int length)
{
  for (int i = 0; i < length; i++)
  {
    auto left = a[i]; //value to compare
    //check left hand side
    for (int j = 0; j < length; j++)
    {
      if (i != j)
      {
        if (left == a[j])
        {
          cerr << "Invalid plugboard mapping!\n";
          return true;
        }
      }
    }
    //check right hand side
    for (int j = 0; j < length; j++)
    {
      if (left == b[j])
      {
        cerr << "Invalid plugboard mapping!\n";
        return true;
      }
    }
    auto right = b[i]; //value to compare
    //check left hand side
    for (int j = 0; j < length; j++)
    {
      if (right == a[j])
      {
        cerr << "Invalid plugboard mapping!\n";
        return true;
      }
    }
    //check right hand side
    for (int j = 0; j < length; j++)
    {
      if (i != j)
      {
        if (right == b[j])
        {
          cerr << "Invalid plugboard mapping!\n";
          return true;
        }
      }
    }
  }
  return false;
}
void Plugboard::print(){
  cerr << "Plugboard Mapping:\n";
  for (int i = 0; i < LETTER_COUNT; i++)
  {
    cerr << "{ " << i << " ; " << _mapping[i] << " }\n";
  }
  cerr << endl;
}

/***********************DESTRUCTOR**************************/
Plugboard::~Plugboard()
{

}
