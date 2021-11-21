#include <iostream>
#include <fstream>
#include <cstdio>

#include "Reflector.h"
#include "errors.h"

using namespace std;

/*************  CONSTRUCTORS  *************/
Reflector::Reflector(){}

//FUNCTIONS
void Reflector::scramble(int& digit)
{
  digit = _mapping[digit];
}


int Reflector::load(const char* refConfig)
{
  ifstream in(refConfig);
  if (!in) {
    cerr << "Reflector::Loading reflector config failed!\n";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  //check for correct number of pairs
  int validNumStatus = checkValidNumbers(in);
  if (validNumStatus != 0) return validNumStatus;

  createMapping(in);

  int validMapStatus = checkValidMapping();
  if (validMapStatus != 0) return validMapStatus;

  return NO_ERROR;
}

void Reflector::createMapping(ifstream& in)
{
  for (int i =0; i < DIGIT_COUNT/2; i++)
  {
    int A = -1;
    int B = -1;
    in >> A;
    in >> B;

    _mapping[A] = B;
    _mapping[B] = A;
  }
}

int Reflector::checkValidNumbers(ifstream& in)
{
  //check for correct number of pairs
  int count = 0;
  while (!in.eof())
  {
    int temp = -1;
    in >> temp;

    if (in.fail() && !in.eof())
    {
      cerr<< "Non-numeric character in reflector file reflector.rf" << endl;
      return NON_NUMERIC_CHARACTER;
    }
    if (temp == -1) break; //end of file
    //check for invalid index
    if (temp < 0 || temp > DIGIT_COUNT-1)
    {
      cerr << "Reflector::Invalid Index!\n";
      return INVALID_INDEX;
    }
    if (temp != -1) count++;
  }

  if (count < DIGIT_COUNT && count % 2 == 0)
  {
    cerr << "Insufficient number of mappings in reflector file: reflector.rf\n";
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  else if (count % 2 != 0)
  {
    cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf\n";
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!
  return NO_ERROR;
}

int Reflector::checkValidMapping()
{
  // check for invalid reflector mapping
  for (int i = 0; i < DIGIT_COUNT-1; i++)
  {
    if (_mapping[i] == i)
    {
      cerr << "Invalid reflector mapping. "
      << i << " maps to itself.\n";
      return INVALID_REFLECTOR_MAPPING;
    }
    for (int j = i + 1; j < DIGIT_COUNT; j++)
    {
      //if duplicate mapping
        if (_mapping[i] == _mapping[j])
        {
          cerr << "invalid reflector mapping. "
          << _mapping[i] << " is already mapped to "
          << i << ".\n";
          return INVALID_REFLECTOR_MAPPING;
        }
    }
  }
  return NO_ERROR;
}

void Reflector::print()
{
  cerr << "Reflector Mapping:\n";
  for (int i = 0; i < DIGIT_COUNT; i++)
  {
    cerr << "{ " << i << " ; " << _mapping[i] << " }\n";
  }
  cerr << endl;
}
