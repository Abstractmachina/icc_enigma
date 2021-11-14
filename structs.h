#ifndef STRUCTS_H
#define STRUCTS_H

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



/********linked list impl. for number pairs***********/
struct NumPairListNode
{
 NumPair* numPair;
 NumPairListNode(NumPair* p) : numPair(p){};
 NumPairListNode* next = nullptr;
};

struct ListNode_int
{
  int val;
  ListNode_int* next = NULL;
  ListNode_int(int val_) : val(val_){};
};
/********linked list impl. for ints***********/


/***************** GENERIC LINKED LIST *********/

template <typename T>
struct Node
{
  T* val;
  Node<T>* next = NULL;
  Node<T>* prev = NULL;
  Node<T>(T* val_)
  {
    val = val_;
  };



};


#endif
