#ifndef TEST_HEADER_FACTORIAL_H
#define TEST_HEADER_FACTORIAL_H

#include <stdlib.h>

size_t factorial(size_t n)
{
    size_t fac = 1;

    for(size_t i = 1; i < n; ++i)
    {
        fac *= i;
    }

    return fac;
}

#endif // #ifndef TEST_HEADER_FACTORIAL_H

