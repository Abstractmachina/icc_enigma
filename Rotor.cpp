#include "Rotor.h"
#include "errors.h"

using namespace std;

Rotor::Rotor(){}

/*********  SETUP FUNCTIONS ***********/

/*Init rotor from configuration files. */
int Rotor::load(char* rotConfig, char* startPosConfig, int ind)
{
  setIndex(ind);

  //start in stream
  ifstream in(rotConfig);
  if (!in)
  {
    cerr << "Loading rotor config failed!\n";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  //error checking of individual digits
  int validNumStatus = checkValidNumbers(in);
  if (validNumStatus != 0) return validNumStatus;

  //assign mapping and notches
  createMapping(in);
  in.close();

  //check if mapping is correct
  int validMappingStatus = checkValidMapping();
  if (validMappingStatus != 0) return validMappingStatus;

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
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  if (in.peek() == std::ifstream::traits_type::eof())
  {
    cerr << "No starting position for rotor 0 in rotor position file: rotor.pos\n";
    return NO_ROTOR_STARTING_POSITION;
  }

  string word = "";
  char c;
  int count = 0;
  in >> std::noskipws;
  while (in >> c)
  {
    cerr << "Rotor " << _index << "position feed: " << c << endl;
    if (c != ' ' && c != '\0' && c != 10)
    {
      if (!isdigit(c))
      {
        cerr << "pre error log | c: " << (int)c << endl;
        cerr << "Non-numeric character in rotor positions file rotor.pos\n";
        return NON_NUMERIC_CHARACTER;
      }
      else word += c;
    }
    else
    {
      //cerr << "notch read: " << word << endl;
      if (count == _index)
      {
        int startPos = std::stoi(word);
        _startPos = startPos;
        break;
      }
      word = "";
      count++;
    }
  }
  in.close();
  return NO_ERROR;
}


//********************  ENCRYPTION FUNCTIONS ****************/

void Rotor::scramble(int& digit, bool step, bool& notchHit, bool reverse)
{
  if (step) _rotation++; //step once if notch hit or right most rotor
  int offset = _startPos + _rotation;
  int translation = digit + offset;
  if (translation > NUM_LETTERS - 1 ) translation %= NUM_LETTERS;

  //check for notches;
  notchHit = isNotch(offset);

  //scramble
  if (!reverse) //right to left
    translation = _mapping[translation];
  else // left to right
  {
    for (int i = 0; i < NUM_LETTERS; i++)
      if (_mapping[i] == translation)
      {
        translation = i;
        break;
      }
  }

  digit = translation - offset; //

  //loop backward to get to correct index if value negative
  if (digit < 0)
  {
    while (digit < 0)
    {
      digit = NUM_LETTERS + digit;
    }
  }
}

bool Rotor::isNotch(int offset)
{
  bool notchHit = false;
  if (_notches != NULL)
  {
    for (auto it = _notches; it != NULL; it = it->next)
    {
      if (offset == it->val)
      {
        notchHit = true;
        break;
      }
    }
  }
  return notchHit;
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
        return NON_NUMERIC_CHARACTER;
      }
      else
      {
        cerr << "Non-numeric character in rotor positions file rotor.pos\n";
        return NON_NUMERIC_CHARACTER;
      }
    }

    //check for invalid index
    if (val < 0 || val >= NUM_LETTERS)
    {
      cerr << "Invalid Index!\n";
      cerr << "val: " << val << endl;
      return INVALID_INDEX;
    }
    digitCounter++;
  }

  //Ccheck sufficient number of inputs
  if (digitCounter < NUM_LETTERS)
  {
    cerr << "Not all inputs mapped in rotor file: rotor.rot\n";
    return INVALID_ROTOR_MAPPING;
  }
  in.clear();                 // clear fail and eof bits
  in.seekg(0, std::ios::beg); // back to the start!
  return NO_ERROR;
}

int Rotor::checkValidMapping()
{
  for (int i = 0; i < NUM_LETTERS; i++)
  {
    for (int j = i + 1; j < NUM_LETTERS; j++)
    {
        if (_mapping[i] == _mapping[j])
        {
          cerr << "Invalid mapping of input "
          << j << " to output " << _mapping[j] << " (output "
          << _mapping[j] << " is already mapped to from input "
          << i <<") in";
          return INVALID_ROTOR_MAPPING;
        }
    }
  }
  return NO_ERROR;
}


/************** DEBUG ******************/
void Rotor::print()
{
  cerr << "Rotor " << _index << ":"<< endl;
  cerr <<"Start Position: " << _startPos << " ; "
  << "Rotation: " << _rotation << " }\n";
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
