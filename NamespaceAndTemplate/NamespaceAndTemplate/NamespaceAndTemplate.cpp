// NamespaceAndTemplate.cpp : Defines designer namespace.
//
#include "stdafx.h"

#include "NamespaceAndTemplate.hpp"

//namespace foobar
//{
  template<class T> T Suma(const vector<T> &l)
  {
    T result = T(0);
    for (typename vector<T>::const_iterator i = l.begin(); i != l.end(); i++)
    {
      result += *i;
    }

    return result;
  }
//}

