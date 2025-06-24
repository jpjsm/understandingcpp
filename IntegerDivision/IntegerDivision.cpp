//
//  main.cpp
//  IntegerDivision
//
//  Created by Juan Jofre on 10/5/18.
//  Copyright © 2018 Juan Jofre. All rights reserved.
//

#include <iostream>
struct division_pair
{
    long long quotient;
    long long remainder;
};

division_pair division(long long a, long long b)
{
    if (b == 0)
    {
        std::cout << "ERROR: Division by Zero\n";
        throw;
    }
    
    long long q = 0;
    long long r = a;
    
    while( r >= b)
    {
        long long i = 1;
        long long bb = b;
        while (r >= bb)
        {
            i <<= 1;
            bb <<= 1;
        }
        
        i >>= 1;
        bb >>= 1;
        q |= i;
        r -= bb;
    }
    
    division_pair result = {q, r};
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    long long numerator = 19;
    long long denominator = 5;
    division_pair r = division(numerator, denominator);
    std::cout << numerator << " / " << denominator << " = " << r.quotient << " and " << r.remainder << " remainder\n";
    return 0;
}
