
#include "musmath.h"


#define GCD(typename, sym) \
    typename gcd ## sym(typename u, typename v) { \
        int shift;                                \
        if (u == 0) return v;                     \
        if (v == 0) return u;                     \
        shift = __builtin_ctz(u | v);             \
        u >>= __builtin_ctz(u);                   \
        do {                                      \
            v >>= __builtin_ctz(v);               \
            if (u > v) {                          \
                typename t = v;                   \
                v = u;                            \
                u = t;                            \
            }                                     \
            v -= u;                               \
        } while (v != 0);                         \
        return u << shift;                        \
    }


#define LCM(typename, sym) \
    typename lcm ## sym(typename u, typename v) { \
        return u | v ? u * v / gcd(u, v) : u;     \
    }

#define ALCM(typename, sym) \
    typename alcm ## sym(typename* u, size_t len) { \
        typename base = *u;                         \
        for (size_t i = 1; i < len; ++i) {          \
            base = lcm ## sym(base, u[i]);          \
        }                                           \
        return base;                                \
    }


#define CF(typename, suf) 

#define DEFINE_ALL(typename, sym) \
    GCD(typename, sym)            \
    LCM(typename, sym)            \
    ALCM(typename, sym)


DEFINE_ALL(unsigned int,)
DEFINE_ALL(unsigned long, l)


#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


#define MAX 15
#define eps 1e-9


int cf(int *res, double x, int iterations) {
    int i;
    res -= 2;
    for(i=2; i<iterations; ++i) {
        res[i] = lrint(floor(x));
        if(fabs(x-res[i])<eps) {
            memset(res + i, 0, (iterations - i) * sizeof(int));
            return 1;
        }
        x = 1.0/(x - res[i]);
    }
    return 0;
}

/*

#define MAX 15
#define eps 1e-9

long p[MAX], q[MAX], a[MAX], len;
void find_cf(double x) {
  int i;
  //The first two convergents are 0/1 and 1/0
  p[0] = 0; q[0] = 1;
  p[1] = 1; q[1] = 0;
  //The rest of the convergents (and continued fraction)
  for(i=2; i<MAX; ++i) {
    a[i] = lrint(floor(x));
    p[i] = a[i]*p[i-1] + p[i-2];
    q[i] = a[i]*q[i-1] + q[i-2];
    printf("%ld:  %ld/%ld\n", a[i], p[i], q[i]);
    len = i;
    if(fabs(x-a[i])<eps) return;
    x = 1.0/(x - a[i]);
  }
}

 */

