#include <iostream>
#include <fstream>
#include <cstdio>

#include "Reflector.h"

using namespace std;

/*************  CONSTRUCTORS  *************/
Reflector::Reflector(){}
Reflector::Reflector(const char* refConfig)
{
  //for (int i = 0; i < 26; i++) _mapping[i] = i;
  load(refConfig);
}

//FUNCTIONS

int Reflector::load(const char* refConfig)
{
  ifstream in(refConfig);
  if (!in) {
    cerr << "Loading reflector config failed!\n";
    return 11;
  }

  //check for correct number of pairs
  int count = 0;
  while (!in.eof())
  {
    int temp = -1;
    in >> temp;
    if (temp != -1) count++;
  }
  if (count != MAX_PAIR*2)
  {
    cerr << "Invalid number of pairs!\n";
    return 10;
  }
  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!

  int index[MAX_PAIR];
  int value[MAX_PAIR];

  //assign pairs
  for (int i = 0; i < MAX_PAIR*2; i++)
  {
    int val;
    in >> val;

    //check for invalid index
    if (val < 0 || val > 25)
    {
      cerr << "Invalid Index!\n";
      return 3;
    }

    if (i == 0) index[0] = val;
    else if (i % 2 == 0) index[i/2] = val;
    else value[(i-1) / 2] = val;
  }

  if(checkInvalidMapping(index, value)) return 10;

  //translate to mapping
  for (int i = 0; i < MAX_PAIR; i++)
  {
    _mapping[index[i]] = value[i];
    _mapping[value[i]] = index [i];
  }

  in.close();

  return 0;
}


/*Check if any number is mapped to itself or multiple times,
*/
bool Reflector::checkInvalidMapping(int a[MAX_PAIR], int b[MAX_PAIR])
{
  // check for invalid reflector mapping
  for (int i = 0; i < MAX_PAIR*2; i++)
  {
    int count = 0;
    for (int j = 0; j < MAX_PAIR; j++)
    {
        if (a[j] == i || b[j] == i) count++;
        if (a[j] == b[j]) //if it maps to itself
        {
          cerr << "Invalid reflector mapping!\n";
          return true;
        }
    }
    if (count != 1) //if there is duplicate mapping
    {
      cerr << "Invalid reflector mapping!\n";
      return true;
    }
  }
  return false;
}

void Reflector::print()
{
  cerr << "Reflector Mapping:\n";
  for (int i = 0; i < MAX_PAIR*2; i++)
  {
    cerr << "{ " << i << " ; " << _mapping[i] << " }\n";
  }
  cerr << endl;
}
