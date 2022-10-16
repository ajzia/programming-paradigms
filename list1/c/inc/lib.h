#ifndef LIB_H
#define LIB_H

#include <limits.h>
#include <stdint.h>

uint64_t factorial(uint64_t n);

uint64_t rec_factorial(uint64_t n);

uint64_t gcd(uint64_t x, uint64_t y);

uint64_t rec_gcd(uint64_t x, uint64_t y);

void rec_diophantine_equation(int64_t a, int64_t b, int64_t c, int64_t* restrict x, int64_t* restrict y);

void diophantine_equation(int64_t a, int64_t b, int64_t c, int64_t* restrict x, int64_t* restrict y);

#endif
