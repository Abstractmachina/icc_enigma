#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard
{
private:

  //static int const _BUFFER_PLUGBOARD = 56;
  int _numberPairs[52];

public:
  Plugboard();
  Plugboard(const char* pbConfig);

  /*load number pairs from a config file*/
  void load(const char* pbConfig);
  void print();
};

#endif
