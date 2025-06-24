// SplitItemsInTwoGroupsEven.cpp : Defines the entry point for the console application.
//

//
//  main.cpp
//  Split a list of Items In Two Groups as Even as possible.
//
//  Created by Juan Jofre on 10/9/18.
//  Copyright © 2018 Juan Jofre. All rights reserved.
//
#include "stdafx.h"

#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// #include "general.h"
template<typename T> T Sum(const vector<T> L)
{
  T sum = 0;
  for (typename vector<T>::const_iterator i = L.begin(); i != L.end(); i++)
    sum += *i;
  return sum;
};

template<typename T> T removeat(vector<T>& l, size_t at)
{
  T v = l.at(at);
  l.erase(l.begin() + at);
  return v;
};

template<typename T> long long FindLessEqual(const vector<T> l, const T v, long long floor, long long ceiling)
{
  // validate arguments

  if (v < l[floor]) return -1;
  if (v > l[ceiling]) return ceiling;

  bool isdiffone = false;
  long long index = ((ceiling - floor + 1) / 2) + floor;
  T li = l[index];
  while ((li != v) && (floor < ceiling))
  {
    if (v < li)
    {
      ceiling = index;
    }
    else if (v > li)
    {
      floor = index;
    }
    else
    {
      break;
    }

    if (isdiffone)
    {
      index = ceiling = floor;
      break;
    }

    index = ((ceiling - floor + 1) / 2) + floor;
    li = l[index];
    if ((ceiling - floor) == 1) isdiffone = true;
  }

  return index;
}

template<typename T> void print(const vector<T> L)
{
  if (L.size() == 0)
  {
    cout << '\n';
    return;
  }

  auto i = L.begin();
  cout << *i;

  for (i++; i != L.end(); i++)
    cout << ", " << *i;
  cout << '\n';
}

// #include "SplitItemsInTwoGroupsEven.h"
enum ClosestDifferenceType { Up, DownUp, DownDown };

template<typename T> struct ABlists
{
  unsigned long long difference;
  vector<T> A;
  vector<T> B;
};

template<typename T> bool SplitTrivial(const vector<T> l, ABlists<T> *r)
{
  if (l.size() == 0) return true;
  if (l.size() == 1)
  {
    r->A.push_back(l[0]);
    return true;
  }

  if (l.size() == 2)
  {
    r->A.push_back(l[0]);
    r->B.push_back(l[1]);
    return true;
  }

  return false;
}

template<typename T> ABlists<T> SplitExhaustive(vector<T> l)
{
  if (l.size() > 64)
  {
    cout << "List too long to evaluate.\nSize() <= 64, current size: " << l.size() << "\n";
    throw;
  }

  unsigned long long MinDifference = 0xFFFFFFFFFFFFFFFF;
  T SumA, SumB;
  ABlists<T> results;

  results.A = {}; // new vector<T>(l.size() / 2); //{};
  results.B = {}; // new vector<T>(l.size() / 2); //{};

  if (SplitTrivial(l, &results)) return results;

  T goal = Sum(l) & 0x1 ? T(1) : T(0);
  unsigned long long maxcombination = 1;
  for (unsigned int i = 0; i < (l.size() - 1); i++)
  {
    maxcombination = (maxcombination << 1) | 1;
  }

  T limit = (maxcombination>>1) + 1;
  for (unsigned long i = 1; i < maxcombination; i++)
  {
    SumA = SumB = T(0);
    int index = 0;
    for (unsigned long j = 1; j != 0 && j < maxcombination; j <<= 1)
    {
      if ((i & j) != 0)
      {
        SumA += l[index];
      }
      else
      {
        SumB += l[index];
      }

      index++;
    }

    T diff = SumA > SumB ? SumA - SumB : SumB - SumA;
    if (MinDifference > diff)
    {
      MinDifference = diff;
      results.A.clear();
      results.B.clear();
      int index = 0;
      for (unsigned long j = 1; j != 0 && j < maxcombination; j <<= 1)
      {
        if ((i & j) != 0)
        {
          results.A.push_back(l[index]);
        }
        else
        {
          results.B.push_back(l[index]);
        }

        index++;
      }

      results.difference = MinDifference;

      if (MinDifference == goal) // no need to search for more
      {
        return results;
      }
    }
  }

  return results;
};

template<typename T> ABlists<T> SplitGreedy(vector<T> l)
{
  T SumA, SumB;
  ABlists<T> results;
  results.A = {}; // new vector<T>(l.size() / 2); //{};
  results.B = {}; // new vector<T>(l.size() / 2); //{};

  if (SplitTrivial(l, &results)) return results;

  sort(l.begin(), l.end());
  SumA = SumB = T(0);
  auto i = l.rbegin();
  while (i != l.rend())
  {
    results.A.push_back(*i);
    SumA += *i;
    i++;
    while (i != l.rend() && SumB < SumA)
    {
      results.B.push_back(*i);
      SumB += *i;
      i++;
    }
  }

  results.difference = SumA > SumB ? SumA - SumB : SumB - SumA;
  return results;
}

template<typename T> ABlists<T> SplitClosestDifference(vector<T> l, ClosestDifferenceType cdt)
{
  T SumA, SumB, currentdiff, value;
  long long index;
  ABlists<T> results;
  results.A = {}; // new vector<T>(l.size() / 2); //{};
  results.B = {}; // new vector<T>(l.size() / 2); //{};

  if (SplitTrivial(l, &results)) return results;

  sort(l.begin(), l.end());
  SumA = SumB = T(0);
  while (l.size() > 0)
  {
    value = removeat(l, l.size() - 1);
    results.A.push_back(value);
    SumA += value;
    while (l.size() > 0 && SumB < SumA)
    {
      currentdiff = SumA - SumB;
      if (cdt == ClosestDifferenceType::Up)
      {
        auto lb = lower_bound(l.begin(), l.end(), currentdiff);
        if (lb == l.end())
        {
          index = l.size() - 1;
        }
        else
        {
          index = lb - l.begin();
        }
      }
      else
      {
        index = FindLessEqual(l, currentdiff, 0, l.size() - 1);

        if (cdt == ClosestDifferenceType::DownUp)
        {
          if (index == -1) index = 0;
        }
        else if (cdt == ClosestDifferenceType::DownDown)
        {
          if (index == -1) break;
        }
        else
        {
          throw "Not implement ClosestDifferenceType";
        }
      }

      value = removeat(l, index);
      results.B.push_back(value);
      SumB += value;
    }
  }

  results.difference = SumA > SumB ? SumA - SumB : SumB - SumA;
  return results;
}

template<typename T> ABlists<T> SplitClosestDifferenceUp(vector<T> l)
{
  return SplitClosestDifference(l, ClosestDifferenceType::Up);
};

template<typename T> ABlists<T> SplitClosestDifferenceDownUp(vector<T> l)
{
  return SplitClosestDifference(l, ClosestDifferenceType::DownUp);
};

template<typename T> ABlists<T> SplitClosestDifferenceDownDown(vector<T> l)
{
  return SplitClosestDifference(l, ClosestDifferenceType::DownDown);
};


typedef unsigned int NumType;
typedef vector<unsigned int>::const_iterator LI;
typedef ABlists<unsigned int>(*SE)(vector<NumType>);
typedef tuple<string, SE> Method;

int main(int argc, const char * argv[]) {
  cout << "starting ... \n";
  vector<Method> methods;

  methods.push_back(tuple<string, SE>("Exhaustive", SplitExhaustive<unsigned int>));
  methods.push_back(tuple<string, SE>("Greedy", SplitGreedy<unsigned int>));
  methods.push_back(tuple<string, SE>("cd-UP", SplitClosestDifferenceUp<unsigned int>));
  methods.push_back(tuple<string, SE>("cd-DownUp", SplitClosestDifferenceDownUp<unsigned int>));
  methods.push_back(tuple<string, SE>("cd-DownDown", SplitClosestDifferenceDownDown<unsigned int>));

  vector< vector<NumType> > test = {
    { 98, 23, 71, 83, 14, 93, 14, 52, 27, 48, 97, 86, 56, 45, 92, 66 },
    { 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,   1 },
    { 1, 3, 5, 9, 17, 33, 65, 129, 257 },
    { 11, 13, 15 },
    {  8, 7, 6, 5, 4 }
  };


  for (unsigned int t = 0; t < test.size(); t++)
  {
    cout << "Original list: ";
    print(test[t]);
    ABlists<unsigned int> results;
    for (size_t m = 0; m < methods.size(); m++)
    {
      results = get<1>(methods[m])(test[t]);
      cout << "   Splitted in two lists by " << get<0>(methods[m]) << " search, with a difference of " << results.difference << "\n";
      /*
      cout << "      List A: Sum = " << Sum(results.A) << ", values: ";
      print(results.A);
      cout << "      List B: Sum = " << Sum(results.B) << ", values: ";
      print(results.B);
      */
    }
  }

  return 0;
}
