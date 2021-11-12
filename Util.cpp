#include <iostream>

#include "Util.h"

using namespace std;


bool Util::checkInvalidMapping(int a[13], int b[13])
{
  // check for invalid reflector mapping
  for (int i = 0; i < 13; i++)
  {
    int count = 0;
    for (int j = 0; j < 13; j++)
    {
        if (a[j] == i || b[j] == i) count++;
        if (a[j] == b[j]) //if it maps to itself
        {
          cout << "Invalid reflector mapping!\n";
          return true;
        }
    }
    if (count != 1) //if there is duplicate mapping
    {
      cout << "Invalid reflector mapping!\n";
      return true;
    }
  }
  return false;
}
