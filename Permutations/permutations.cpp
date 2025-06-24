//
//  main.cpp
//  Permutations
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

void checkpermutearguments(list<int>& R, list<int>& U, const int K)
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
 This function will recursively find all permutations of length k from a
 list U, of at least k elements, and print the resulting permutations.
 
 To use permute you start with an empty list R, the list of all U elements,
 and the k depth of permutations
 
 -----------------------------------------------------------------------*/
void permute(list<int>& R, list<int>& U, const int K)
{
    checkpermutearguments(R, U, K);
    
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
        
        /* make a copy of U without *j */
        list<int> U1;
        for (LI l = U.begin(); l != U.end(); l++)
        {
            if (*l != *j)
                U1.push_back(*l);
        }
        
        permute(R1, U1, K);
    }
}

void permutations(list<int>& L, int K)
{
    list<int> R;
    permute(R, L, K);
}

int main()
{
    list<int> P({ 1, 2, 3, 4, 5 });
    
    for (int i = 1; i <= 5; i++)
    {
        cout << "Permutations of " << i << " out of " << P.size() << " elements\n";
        permutations(P, i);
    }
    
    return 0;
}

