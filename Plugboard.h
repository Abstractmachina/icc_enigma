#ifndef PLUGBOARD_H
#define PLUGBOARD_H


/*The Plugboard class contains a list of number Pairs
which specify the letters to be swapped with each other.*/
class Plugboard
{
  static const int LETTER_COUNT = 26;
  int _mapping[LETTER_COUNT];

  bool isInvalidMapping(int a[], int b[], int length);
public:
  int load(const char* pbConfig);
  void scramble(int& digit);
  void print();

  ~Plugboard();
};

#endif
