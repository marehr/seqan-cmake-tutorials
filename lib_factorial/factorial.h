#ifndef LIB_HEADER_FACTORIAL_H
#define LIB_HEADER_FACTORIAL_H

#include <stdlib.h>

#ifndef _MSC_VER
#define __shared_export
#else
#define __shared_export __declspec(dllexport)
#endif

/**
 * calculate n!
 */
__shared_export
size_t factorial(size_t n);

#undef __shared_export

#endif // #ifndef LIB_HEADER_FACTORIAL_H

