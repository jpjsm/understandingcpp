//
//  main.cpp
//  TestLowerBound
//
//  Created by Juan Jofre on 10/16/18.
//  Copyright © 2018 Juan Jofre. All rights reserved.
//


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <tuple>
using namespace std;

template<class T> bool gt(T a, T b)
{
    return a > b;
}

template<class T> bool ge(T a, T b)
{
    return a >= b;
}

template<class T> bool lt(T a, T b)
{
    return a < b;
}

template<class T> bool le(T a, T b)
{
    return a <= b;
}

template<class T> bool comparison(string boolcomparator, T a, T b)
{
    string bc;
    transform(boolcomparator.begin(), boolcomparator.end(), bc.begin(), ::tolower);

    if ( boolcomparator == ">" || boolcomparator == "-gt" || boolcomparator == "gt") return gt(a,b);
    if ( boolcomparator == ">=" || boolcomparator == "-ge" || boolcomparator == "ge") return ge(a,b);
    if ( boolcomparator == "<" || boolcomparator == "-lt" || boolcomparator == "lt") return lt(a,b);
    if ( boolcomparator == "<=" || boolcomparator == "-le" || boolcomparator == "le") return le(a,b);

    throw "Unkown comparison operator!";
}

template<class T> int FindLessEqual(const vector<T> l, const T v, int floor, int ceiling)
{
    // validate arguments
    
    if (v < l[floor]) return -1;
    if (v > l[ceiling]) return ceiling;
    
    bool isdiffone = false;
    int index = ((ceiling - floor + 1) / 2) + floor;
    T li = l[index];
    while ((li != v) && (floor < ceiling))
    {
        if ( v < li)
        {
            ceiling = index;
        }
        else if ( v > li)
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

template<class T> void print(const vector<T>& L)
{
    if (L.size() == 0)
    {
        cout << '\n';
        return;
    }
    
    typename vector<T>::const_iterator i = L.begin();
    cout << *i;
    
    for (i++; i != L.end(); i++)
        cout << ", " << *i;
    cout << '\n';
}



int main(int argc, const char * argv[]) {
    vector<int> numbers = {1, 3, 5, 7, 9, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
    vector<tuple<int,int>> test = {};
    int f = 12;
    cout << "Test vector: ";
    print(numbers);
    
    auto index = lower_bound(numbers.begin(), numbers.end(), f) - numbers.begin();
    cout << "Lowest match for " << f << " is " << numbers[index] << " at position " << index << "\n";
    
    index = lower_bound(numbers.begin(), numbers.end(), f, gt<int>) - numbers.begin();
    cout << "Lowest match for " << f << " is " << numbers[index] << " at position " << index << " using '>' comparator\n";
    
    index = lower_bound(numbers.begin(), numbers.end(), f, ge<int>) - numbers.begin();
    cout << "Lowest match for " << f << " is " << numbers[index] << " at position " << index << " using '>=' comparator\n";
    
    index = lower_bound(numbers.begin(), numbers.end(), f, lt<int>) - numbers.begin();
    cout << "Lowest match for " << f << " is " << numbers[index] << " at position " << index << " using '<' comparator\n";
    
    index = lower_bound(numbers.begin(), numbers.end(), f, le<int>) - numbers.begin();
    cout << "Lowest match for " << f << " is " << numbers[index] << " at position " << index << " using '<=' comparator\n";

    for (int i = 0; i < 45; i++) {
        index = FindLessEqual(numbers, i, 0, numbers.size()-1);
        if (index == -1)
        {
            cout << "No match for " << i << " in list, smallest element is greater than seek value\n";
            continue;
        }
        
        cout << "Lowest match for " << i << " is " << numbers[index] << " at position " << index << "\n";
    }
    return 0;
}
