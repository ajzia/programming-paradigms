#include "../inc/lib.h"

#include <stdio.h>

uint64_t factorial(register const uint64_t n) {
  if (n == 0)
    return 1;

  register uint64_t result = 1;
  for (uint64_t i = 2; i <= n; i++) 
    result *= i;

  return result;
}

uint64_t rec_factorial(register const uint64_t n) {
  if (n == 0) 
    return 1;

  return n * rec_factorial(n - 1);
}

uint64_t gcd(register const uint64_t x, register const uint64_t y) {
  if (x == 0 || y == 0)
    return 0;

  if (x == 1 || y == 1)
    return 1;

  register uint64_t result = 0;

  for (uint64_t i = 1; i <= x && i <= y; i++) {
    if(x % i == 0 && y % i == 0)
      result = i;
  }

  return result;
}

uint64_t rec_gcd(register const uint64_t x, register const uint64_t y) {
  if (y != 0)
    return rec_gcd(y, x % y);

  return x;
}

static int64_t gcd_extended(register int64_t a, register int64_t b, register int64_t* restrict const x, register int64_t* restrict const y) {
  int64_t q, temp, prevx = 1, prevy = 0;
  *x = 0;
  *y = 1;

  while (b != 0) {
    q = a / b;
    
    temp = (*x);
    *x = prevx - q * temp;
    prevx = temp;

    temp = *y;
    *y = prevy - q * temp;
    prevy = temp;

    temp = a;
    a = b;
    b = temp % b;
  }

  *x = prevx;
  *y = prevy;

  return a;
}

static int64_t rec_gcd_extended(register const int64_t a, register const int64_t b, register int64_t* restrict const x, register int64_t* restrict const y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }
 
  int64_t x1, y1;
  int64_t gcd = rec_gcd_extended(b % a, a, &x1, &y1);
 
  *x = y1 - (b / a) * x1;
  *y = x1;
 
  return gcd;
}

void diophantine_equation(register const int64_t a, register const int64_t b, register const int64_t c, register int64_t* restrict const x, register int64_t* restrict const y) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      *x = 1;
      *y = 1;

      return;
    } else {
      *x = LLONG_MIN;
      *y = LLONG_MIN;

      printf("No possible solutions.\n\n");
      return;
    }
  }

  int64_t x1, y1;
  register const uint64_t gcd_temp = gcd_extended(a, b, &x1, &y1);

  if (c % gcd_temp != 0) {
    *x = LLONG_MIN;
    *y = LLONG_MIN;

    printf("No possible solutions.\n\n");
    return;
  }

  *x = x1 * (c / gcd_temp);
  *y = y1 * (c / gcd_temp);

  return;
}

void rec_diophantine_equation(register const int64_t a, register const int64_t b, register const int64_t c, register int64_t* restrict const x, register int64_t* restrict const y) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      *x = 1;
      *y = 1;

      return;
    } else {
      *x = LLONG_MIN;
      *y = LLONG_MIN;

      printf("No possible solutions.\n\n");
      return;
    }
  }

  int64_t x1, y1;
  register const uint64_t gcd_temp = rec_gcd_extended(a, b, &x1, &y1);

  if (c % gcd_temp != 0) {
    *x = LLONG_MIN;
    *y = LLONG_MIN;

    printf("No possible solutions.\n\n");
    return;
  }

  *x = x1 * (c / gcd_temp);
  *y = y1 * (c / gcd_temp);

  return;
}
