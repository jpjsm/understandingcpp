//
//  main.cpp
//  Multiplication
//
//  Created by Juan Jofre on 10/5/18.
//  Copyright © 2018 Juan Jofre. All rights reserved.
//

#include <iostream>

unsigned long long multiply(unsigned long long a, unsigned long long b)
{
    unsigned long long result = 0;
    
    if (a == 0 || b == 0) return result;
    if (a == 1) return b;
    if (b == 1) return a;
    
    result = 0;
    while (b > 0)
    {
        if ((b & 0x1) == 0x1)
            result += a;
        b >>= 1;
        a <<= 1;
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    unsigned long long result;
    for (unsigned long long a = 0; a < 100; a++)
    {
        for (unsigned long long b = 0; b < 100; b++) {
            result = multiply(a, b);
            if (result != (a * b))
            {
                std::cout << "ERROR: multiply( " << a << ", " << b << ") returned " << result << " instead of " << a * b;
            }
        }
    }
    
    std::cout << "Successful test of multiply()!";
    return 0;
}
