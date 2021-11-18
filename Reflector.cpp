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
    return 11;
  }

  //check for correct number of pairs
  int count = 0;
  while (!in.eof())
  {
    int temp = -1;
    in >> temp;

    if (in.fail() && !in.eof())
    {
      cerr<< "Non-numeric character in reflector file reflector.rf" << endl;
      return 4;
    }
    if (temp == -1) break; //end of file
    //check for invalid index
    if (temp < 0 || temp > 25)
    {
      cerr << "Reflector::Invalid Index!\n";
      return 3;
    }
    if (temp != -1) count++;
  }

  if (count < NUM_LETTERS && count % 2 == 0)
  {
    cerr << "Insufficient number of mappings in reflector file: reflector.rf\n";
    return 10;
  }
  else if (count % 2 != 0)
  {
    cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf\n";
    return 10;
  }

  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!

  for (int i =0; i < NUM_LETTERS/2; i++)
  {
    int A = -1;
    int B = -1;
    in >> A;
    in >> B;

    _mapping[A] = B;
    _mapping[B] = A;
  }
  in.close();

  checkValidMapping();

  return 0;
}


/*Check if any number is mapped to itself or multiple times,
*/
bool Reflector::checkValidMapping()
{
  // check for invalid reflector mapping
  for (int i = 0; i < NUM_LETTERS-1; i++)
  {
    if (_mapping[i] == i)
    {
      throw INVALID_REFLECTOR_MAPPING;
    }
    for (int j = i + 1; j < NUM_LETTERS; j++)
    {
      //if duplicate mapping
        if (_mapping[i] == _mapping[j])
        {
          throw INVALID_REFLECTOR_MAPPING;
        }
    }
  }
  return false;
}

void Reflector::print()
{
  cerr << "Reflector Mapping:\n";
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    cerr << "{ " << i << " ; " << _mapping[i] << " }\n";
  }
  cerr << endl;
}
