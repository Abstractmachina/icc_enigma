#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>

#include "Plugboard.h"
//#include "NumPair.h"

using namespace std;

//CONSTRUCTORS
Plugboard::Plugboard(){}
Plugboard::Plugboard(const char* pbConfig)
{
  load(pbConfig);
}

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
  }

  //check for even number of values -> pairs
  int count = 0;
  while (!in.eof())
  {
    int temp = -1;
    in >> temp;
    if (temp != -1) count++;
  }
  if (count % 2 != 0 && count != 0)
  {
    cerr << "INCORRECT NUMBER OF PLUGBOARD PARAMETERS\n";
    return 6;
  }
  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!

  //assign pairs
  int index[count/2];
  int value[count/2];
  for (int i = 0; i < count; i++)
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
  in.close();

  if(isInvalidMapping(index, value, count/2)) return 10;

  //translate to mapping
  //init standard mapping
  for (int i = 0; i < LETTER_COUNT; i++) _mapping[i] = i;
  //assign new pairs
  for (int i = 0; i < count/2; i++)
  {
    _mapping[index[i]] = value[i];
    _mapping[value[i]] = index [i];
  }

  return 0;
}



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
