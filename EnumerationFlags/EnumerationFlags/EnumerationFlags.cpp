// EnumerationFlags.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
    enum MyEnum : unsigned long long
    {
        Pos1 = 0x1ULL,
        Pos2 = 0x1ULL << 1,
        Pos3 = 0x1ULL << 2,
        AllDefined = ~0x0ULL
    };

    MyEnum alldefined = AllDefined;
    unsigned long long verybig = 0x1ULL << 63;
    MyEnum top63 = (MyEnum)verybig;
    MyEnum Pos123 = static_cast<MyEnum>(Pos1 | Pos2 | Pos3);
    return 0;
}

