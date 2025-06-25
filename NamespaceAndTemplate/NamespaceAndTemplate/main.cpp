// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NamespaceAndTemplate.hpp"
#include <iostream>

using namespace std;
//using namespace foobar;

template<class T> T Sum(const vector<T> &l)
{
  T result = T(0);
  for (typename vector<T>::const_iterator i = l.begin(); i != l.end(); i++)
  {
    result += *i;
  }

  return result;
}

int main()
{
  vector<int> l = { 1,2,3,4,5,6 };
  cout << "Hello Word\n";
  cout << "the sum of L is " << Sum(l) << "\n";
  return 0;
}
