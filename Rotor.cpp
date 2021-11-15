#include "Rotor.h"

using namespace std;

/************ CONSTRUCTORS  *******/
Rotor::Rotor() {}

/*********  FUNCTIONS ***********/

void Rotor::scramble(int& digit, bool step, bool& isNotch)
{
  if (step) _rotation++; //step once
  int translation = (digit + _startPos + _rotation);
  if (translation > NUM_LETTERS - 1 ) translation %= NUM_LETTERS;

  //check for notches;
  isNotch = false;
  if (_notches != NULL)
  {
    for (auto it = _notches; it != NULL; it = it->next)
    {
      if (translation == it->val)
      {
        isNotch = true;
        break;
      }
    }
  }
  //scramble
  digit = _mapping[translation];

  //offset back to correct position
  digit -= _rotation + _startPos;
  //loop backward to get to correct index;
  if (digit < 0)
  {
    while (digit < 0)
    {
      digit = NUM_LETTERS + digit;
    }
  }

}

/*Init rotor from configuration files. */
int Rotor::load(char* rotConfig, char* startPosConfig, int ind)
{
  setIndex(ind);

  //start in stream
  ifstream in(rotConfig);
  if (!in)
  {
    cerr << "Loading rotor config failed!\n";
    return 11;
  }

  int digitCounter = 0; //
  
  int validNumStatus = hasValidNumber(in, digitCounter);
  if (validNumStatus != 0) return validNumStatus;

  int index[NUM_LETTERS/2];
  int value[NUM_LETTERS/2];
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    int val = -1;
    in >> val;

    //check for invalid type
    if (in.fail() && !in.eof())
    {
      //TODO check error handling
      cerr << "A Non-numeric character for mapping in rotor file rotor.rot\n";
      return 4;
    }
    //check for invalid index
    if (val < 0 || val >= NUM_LETTERS - 1)
    {
      cerr << "Invalid Index!\n";
      return 3;
    }

    if (i == 0) index[0] = val;
    else if (i % 2 == 0) index[i/2] = val;
    else value[(i-1) / 2] = val;

    //_mapping[i] = val;
  }

  loadNotches(in, digitCounter);
  //printNotches();

  in.close();

  if (isInvalidMapping(index, value)) return 7;

  //translate to mapping
  for (int i = 0; i < NUM_LETTERS/2; i++)
  {
    _mapping[index[i]] = value[i];
    _mapping[value[i]] = index [i];
  }

  //load start position
  int sp = loadStartPosition(startPosConfig, ind);
  if (sp != 0) return sp;

  return 0;
}


/*read notch parameters from config file and load into Rotor

*/
bool Rotor::loadNotches(ifstream& in, int const digitCounter)
{
  int numNotches = digitCounter - NUM_LETTERS;

  for(int i = 0; i < numNotches && !in.eof(); i++)
  {
    int nVal = -1;
    in >> nVal;

    if (nVal != -1 && i == 0)
    {
      _notches = new Node_int(nVal);
    }
    else if (nVal != -1)
    {
      auto end = _notches;
      while (end->next != NULL) end = end->next;
      auto n = new Node_int(nVal);
      n->prev = end;
      end->next = n;
    }
    else return false;
  }

  return true;
}

int Rotor::loadStartPosition(char* startPosConfig, int index)
{
  //load start position
  ifstream in(startPosConfig);
  if (!in) {
    cerr << "Loading start position config failed!\n";
    return 11;
  }
  int startPos = -1;
  for (int i = 0; i <= index; i++)
  {
    in >> startPos;
    if (in.fail() && !in.eof())
    {
      cerr << "Non-numeric character in rotor positions file rotor.pos\n";
      return 4;
    }
  }
  if (startPos == -1)
  {
    cerr << "No rotor starting position found!" << endl;
    return 8;
  }
  in.close();
  _startPos = startPos;

  return 0;
}


/***********  UTILITY FUNCTIONS *************************/
int Rotor::hasValidNumber(ifstream& in, int& digitCounter)
{
  digitCounter = 0;
  while (!in.eof())
  {
    int temp = -1;
    in >> temp;
    if (temp != -1) digitCounter++;
    if (in.fail() && !in.eof())
    {
      cerr << "Non-numeric character for mapping in rotor file rotor.rot\n";
      return 4;
    }
  }

  if (digitCounter < NUM_LETTERS)
  {
    cerr << "Not all inputs mapped in rotor file: rotor.rot\n";
    return 7;
  }
  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!
  return 0;
}

int Rotor::isInvalidMapping(int a[], int b[])
{
  // check for invalid reflector mapping
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    int count = 0;
    for (int j = 0; j < NUM_LETTERS/2; j++)
    {
        if (a[j] == i || b[j] == i) count++;
        if (a[j] == b[j]) //if it maps to itself
        {
          cerr << "Invalid rotor mapping!\n";
          return true;
        }
    }
    if (count != 1) //if there is duplicate mapping
    {
      cerr << "Invalid rotor mapping!\n";
      return true;
    }
  }
  return false;
}

void Rotor::print()
{
  cerr << "Rotor " << _index << ":"<< endl;
  cerr <<"Start Position: " << _startPos << " ; " << "Rotation: " << _rotation << " }\n";
  cerr << "Mapping: \n";
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    cerr << "{ " << i << " ; " << _mapping[i] << " }\n";
  }
  cerr << endl;
}

void Rotor::printNotches()
{
  cerr << "Rotor " << _index << " notches: ";
  for (auto it = _notches; it != NULL; it = it->next)
  {
    cerr << it->val << " ";
  }
  cerr << endl;
}
