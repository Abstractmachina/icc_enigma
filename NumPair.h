#ifndef NUMPAIR_H
#define NUMPAIR_H

#include <string>

using namespace std;

struct NumPair
{
  int A;
  int B;

  NumPair(int a, int b) : A(a), B(b){}

  string getString()
  {
    string first = to_string(A);
    string second = to_string(B);
    string result = "{" + first + ";" + second + "}";
    return result;
  }
};

#endif

#ifndef NUMPAIRLISTNODE_H
#define NUMPAIRLISTNODE_H

/*linked list impl. for number pairs*/
struct NumPairListNode {
 NumPair* numPair;
 NumPairListNode(NumPair* p) : numPair(p){};
 NumPairListNode* next = nullptr;
};

#endif
