#include "Rotor.h"
#include "errors.h"

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
    throw 11;
  }
  //error checking
  int digitCounter = 0; //stores number of digits in file to calc notches after
  int validNumStatus = checkValidNumbers(in, digitCounter);
  if (validNumStatus != 0) return validNumStatus;

  //assign mapping and notches
  int counter = 0;
  while (!in.eof())
  {
    int val = -1;
    in >> val;
    if (counter < NUM_LETTERS) //assign to mapping
      _mapping[counter] = val;
    else //assign to notches
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
  in.close();

  /*check for invalid mapping -> if a number occurs
  twice it means there is duplicate mapping*/
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    for (int j = i+1; j < NUM_LETTERS; j++)
    {
        if (_mapping[i] == _mapping[j])
        {
          cerr << "Invalid mapping of input "
          << j << " to output " << _mapping[j] << " (output " << _mapping[j] << " is already mapped to from input "<< i <<")\n";
          throw INVALID_ROTOR_MAPPING;
        }
    }
  }

  //int loadNotchStatus = loadNotches(in, digitCounter);
  //if (loadNotchStatus != 0) return loadNotchStatus;

  //load start position
  int sp = loadStartPosition(startPosConfig, ind);
  if (sp != 0) return sp;

  return NO_ERROR;

  /*
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
        cerr << "Non-numeric character for mapping in rotor file rotor.rot\n";
        return 4;
      }
      //check for invalid index
      if (val < 0 || val >= NUM_LETTERS)
      {
        cerr << "Invalid Index!\n";
        return 3;
      }

      if (i == 0) index[0] = val;
      else if (i % 2 == 0) index[i/2] = val;
      else value[(i-1) / 2] = val;

    }

    int loadNotchStatus = loadNotches(in, digitCounter);
    if (loadNotchStatus != 0) return loadNotchStatus;

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
  */
}

int Rotor::loadStartPosition(char* startPosConfig, int index)
{
  //load start position
  ifstream in(startPosConfig);
  if (!in) {
    cerr << "Loading start position config failed!\n";
    return 11;
  }

  if (in.peek() == std::ifstream::traits_type::eof())
  {
    cerr << "No starting position for rotor 0 in rotor position file: rotor.pos\n";
    return 8;
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
    cerr << "No starting position for rotor 0 in rotor position file: rotor.pos" << endl;
    return 8;
  }
  in.close();
  _startPos = startPos;

  return 0;
}

/*read notch parameters from config file and load into Rotor
*/
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
int Rotor::checkValidNumbers(ifstream& in, int& digitCounter)
{
  digitCounter = 0;
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
