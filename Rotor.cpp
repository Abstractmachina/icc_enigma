#include <fstream>
#include <iostream>

#include "Rotor.h"

Rotor::Rotor(char* rotConfig)
{
  load(rotConfig);
}


int Rotor::load(char* rotConfig)
{
  ifstream in(rotConfig);
  if (!in) {
    cout << "Loading rotor config failed!\n";
    return 11;
  }


  int count = 0;
  while (!in.eof())
  {
    int a = -1;
    in >> a;
    if (in.fail())
    {
      //TODO check error handling
      cout << "Invalid rotor mapping!\n";
      cout << "Input must be integers only.\n";
      return 7;
    }

    if (a == -1) break; //end of file

    if (count < 26) _mapping[count++] = a;

    else
    {
      int* a_ptr = &a;
      _notches->next = new Node<int>(a_ptr);
    }
  }
  in.close();
  return 0;
}
