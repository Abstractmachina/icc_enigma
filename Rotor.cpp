#include "Rotor.h"
#include "errors.h"

using namespace std;

Rotor::Rotor(){}

/*********  FUNCTIONS ***********/

void Rotor::scramble(int& digit, bool step, bool& notchHit, bool reverse)
{
  if (step) _rotation++; //step once if notch hit or right most rotor
  int translation = (digit + _startPos + _rotation); //offset
  if (translation > NUM_LETTERS - 1 ) translation %= NUM_LETTERS;

  //check for notches;
  notchHit = false;
  if (_notches != NULL)
  {
    for (auto it = _notches; it != NULL; it = it->next)
    {
      if (translation == it->val)
      {
        notchHit = true;
        break;
      }
    }
  }

  //scramble
  //right to left
  if (!reverse)
    digit = _mapping[translation];
  // left to right
  else
  {
    for (int i = 0; i < NUM_LETTERS; i++)
    {
      if (_mapping[i] == translation)
      {
        digit = i;
      }
    }
  }
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
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }
  //error checking
  int validNumStatus = checkValidNumbers(in);
  if (validNumStatus != 0) return validNumStatus;

  //assign mapping and notches
  createMapping(in);
  in.close();

  /*check for invalid mapping -> if a number occurs
  twice it means there is duplicate mapping*/
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    for (int j = i + 1; j < NUM_LETTERS; j++)
    {
        if (_mapping[i] == _mapping[j])
        {
          cerr << "Invalid mapping of input "
          << j << " to output " << _mapping[j] << " (output " << _mapping[j] << " is already mapped to from input "<< i <<")\n";
          throw INVALID_ROTOR_MAPPING;
        }
    }
  }

  //load start position
  int sp = loadStartPosition(startPosConfig, ind);
  if (sp != 0) return sp;

  return NO_ERROR;
}

void Rotor::createMapping(ifstream& in)
{
  //assign mapping and notches
  int counter = 0;
  while (!in.eof())
  {
    int val = -1;
    in >> val;
    if (counter < NUM_LETTERS) //assign to mapping
      _mapping[counter] = val;
    else if (counter >= NUM_LETTERS && val != -1) //assign to notches
    {
      if (_notches == NULL) _notches = new Node_int(val);
      else
      {
        auto end = _notches;
        while (end->next != NULL) end = end->next;
        auto n = new Node_int(val);
        end->next = n;
      }
    }
    counter++;
  }
}

int Rotor::loadStartPosition(char* startPosConfig, int index)
{
  //load start position
  ifstream in(startPosConfig);
  if (!in) {
    cerr << "Loading start position config failed!\n";
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  if (in.peek() == std::ifstream::traits_type::eof())
  {
    cerr << "No starting position for rotor 0 in rotor position file: rotor.pos\n";
    throw NO_ROTOR_STARTING_POSITION;
  }

  int startPos = -1;
  for (int i = 0; i <= index; i++)
  {
    in >> startPos;
    if (in.fail() && !in.eof())
    {
      cerr << "Non-numeric character in rotor positions file rotor.pos\n";
      throw NON_NUMERIC_CHARACTER;
    }
  }
  if (startPos == -1)
  {
    cerr << "No starting position for rotor 0 in rotor position file: rotor.pos" << endl;
    throw NO_ROTOR_STARTING_POSITION;
  }
  in.close();
  _startPos = startPos;

  return NO_ERROR;
}

/*read notch parameters from config file and load into Rotor
OBSOLETE */
int Rotor::loadNotches(ifstream& in, int const digitCounter)
{
  int numNotches = digitCounter - NUM_LETTERS;

  for(int i = 0; i < numNotches && !in.eof(); i++)
  {
    int nVal = -1;
    in >> nVal;

    if (in.fail() && !in.eof())
    {
      cerr << "Non-numeric character in rotor positions file rotor.pos\n";
      return 4;
    }

    if (nVal != -1 && i == 0)
    {
      _notches = new Node_int(nVal);
    }
    else if (nVal != -1)
    {
      auto end = _notches;
      while (end->next != NULL) end = end->next;
      auto n = new Node_int(nVal);
      end->next = n;
    }
  }

  return 0;
}


/***********  UTILITY FUNCTIONS *************************/
int Rotor::checkValidNumbers(ifstream& in)
{
  int digitCounter = 0;
  while (!in.eof())
  {
    int val;
    in >> val;

    //check for non numeric chars
    if (in.fail() && !in.eof())
    {
      if (digitCounter < NUM_LETTERS)
      {
        cerr << "Non-numeric character for mapping in rotor file rotor.rot\n";
        return 4;
      }
      else
      {
        cerr << "Non-numeric character in rotor positions file rotor.pos\n";
        return 4;
      }
    }

    //check for invalid index
    if (val < 0 || val >= NUM_LETTERS)
    {
      cerr << "A Invalid Index!\n";
      cerr << "val: " << val << endl;
      return 3;
    }
    digitCounter++;
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

//OBSOLETE
int Rotor::isInvalidMapping(int a[], int b[])
{
  for (int left = 0; left < NUM_LETTERS/2; left++) {
    for (int right = 0; right < NUM_LETTERS/2; right++)
    {
      int current = a[left];
      //check if digit maps to itself
      if (left == right)
      {
        if(a[left] == b[right])
        {
          cerr << "index maps to itself.";
          return 7;
        }
      }
      if (b[right] == current)
      {
        cerr << "Invalid mapping of input "
        << current << " to output " << 3 << " (output 3 is already mapped to from input 6) in\n";
      }
    }
  }

  return 0;
}

void Rotor::print()
{
  cerr << "Rotor " << _index << ":"<< endl;
  cerr <<"Start Position: " << _startPos << " ; " << "Rotation: " << _rotation << " }\n";
  printNotches();
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
