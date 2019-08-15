#ifndef C_MUSMATH_H /* Include guard */
#define C_MUSMATH_H

#include <stdlib.h>

unsigned int gcd(unsigned int u, unsigned int v);
unsigned long gcdl(unsigned long u, unsigned long v);

unsigned int lcm(unsigned int u, unsigned int v);
unsigned long lcml(unsigned long u, unsigned long v);

unsigned int alcm(unsigned int *u, size_t len);
unsigned long alcml(unsigned long *u, size_t len);


// continued fraction
int cff(int *res, float f, int iterations);
int cf(int *res, double d, int iterations);

#endif
