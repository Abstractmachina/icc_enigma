#include <iostream>
#include <fstream>
#include <cstdio>

#include "Reflector.h"

using namespace std;

//CONSTRUCTORS
Reflector::Reflector(const char* refConfig)
{
  load(refConfig);
}

//FUNCTIONS
int Reflector::load(const char* refConfig)
{
  ifstream in(refConfig);
  if (!in) {
    cout << "Loading reflector config failed!\n";
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

  if (count != MAX_PAIR*2) return 10;
  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!

  count = 0;
  while (!in.eof())
  {
    int a = -1;
    int b = -1;
    in >> a;
    in >> b;
    if (a == -1 || b == -1) break; //end of file
    NumPair* pair = new NumPair(a,b);

    pairs[count++] = pair;

  }
  in.close();
  return 0;
}

void Reflector::print()
{
  cout << "Reflector Pairs:\n";
  for (auto i = 0; i < MAX_PAIR; i++)
  {
    cout << pairs[i]->getString() << endl;
  }
}
