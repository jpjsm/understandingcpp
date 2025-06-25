//
//  main.cpp
//  Combinations
//
//  Created by Juan Jofre on 10/1/18.
//  Copyright © 2018 Juan Jofre. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

typedef list<int>::const_iterator LI;

void print(list<int>& L)
{
    for (LI i = L.begin(); i != L.end(); i++)
        cout << *i;
    cout << '\n';
}

void checkcombinearguments(list<int>& R, list<int>& U, const int K)
{
    if (K > U.size() + R.size())
    {
        cout << "Invalid argument!\nK must be less or equal to U.size + R.size.\n";
        throw;
    }
    
    if (K < 1)
    {
        cout << "Invalid argument!\nK must be greater or equal to 1.\n";
        throw;
    }
}

/* ------------------------------------------------------------------------
 This function will recursively find all combinations of length k from a
 list U, of at least k elements, and print the resulting combinations.
 
 To use combine you start with an empty list R, the list of all U elements,
 and the k depth of combinations
 
 -----------------------------------------------------------------------*/
void combine(list<int>& R, list<int>& U, const int K)
{
    checkcombinearguments(R, U, K);
    
    if (R.size() == K)
    {
        print(R);
        return;
    }
    
    for (LI j = U.begin(); j != U.end(); j++)
    {
        /* make a copy of R and append *j */
        list<int> R1;
        copy(R.begin(), R.end(), back_inserter(R1));
        R1.push_back(*j);
        
        /* make a copy of all elements after j of U */
        list<int> U1;
        for (LI l = next(j,1); l != U.end(); l++)
            U1.push_back(*l);
        
        /* bail out if not enough elements to combine */
        if (R1.size() + U1.size() < K)
            return;
        
        combine(R1, U1, K);
    }
}

void permutations(list<int>& L, int K)
{
    list<int> R;
    combine(R, L, K);
}

int main()
{
    list<int> P({ 1, 2, 3, 4, 5 });
    
    for (int i = 1; i <= 5; i++)
    {
        cout << "Combinations of " << i << " out of " << P.size() << " elements\n";
        permutations(P, i);
        cout << "--------------------------------------------------------------\n\n";
    }
    
    return 0;
}


