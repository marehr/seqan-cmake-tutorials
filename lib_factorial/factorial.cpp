#include "factorial.h"
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

