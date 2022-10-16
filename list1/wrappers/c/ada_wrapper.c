// gnatmake ../../ada/lib.adb && gcc -c ada_wrapper.c && gnatbind -n lib.ali && gnatlink lib.ali ada_wrapper.o
// ./lib


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

extern void adainit();
extern void adafinal();
extern uint64_t factorial(uint64_t n);
extern uint64_t rec_factorial(uint64_t n);

extern uint64_t gcd(uint64_t x, uint64_t y);
extern uint64_t rec_gcd(uint64_t x, uint64_t y);

extern void diophantine_equation(int64_t a, int64_t b, int64_t c, int64_t* x, int64_t* y);
extern void rec_diophantine_equation(int64_t a, int64_t b, int64_t c, int64_t* x, int64_t* y);

static void diophantine_equation_test(void) {
  printf("================ [DIOPHANTINE  EQUASION] ================\n");
  enum { dimension  = 7 };
  uint64_t arr[dimension][3] = {{13, 5, 1}, {27, 4, 3}, {15, 5, 25}, {1, 1, 1}, {0, 0, 0}, {0, 0, 1}, {0, 1, 0}};

  for(int i = 0; i < dimension; i++) {
    int64_t x, y, a = arr[i][0], b = arr[i][1], c = arr[i][2];

    printf("\nDiophantine equation for a = %ld, b = %ld, c = %ld\n\n", a, b, c);
    printf("Iterative algorithm:\n");

    diophantine_equation(a, b, c, &x, &y);
    
    if (x != LLONG_MIN) {
      printf("Solution found!\n");
      printf("%lu * %ld + %lu * %ld = %lu\n\n", a, x, b, y, c);
    }

    printf("Recursive algorithm:\n");
    rec_diophantine_equation(a, b, c, &x, &y);

    if (x != LLONG_MIN) {
      printf("Solution found!\n");
      printf("%lu * %ld + %lu * %ld = %lu\n\n", a, x, b, y, c);
    }
    printf("---------------------------------------------------------\n");
  }
} 

int main(int argc, char const *argv[]) {
  adainit();

  (void)argc;
  (void)argv;

  uint64_t e = 6, f = 27, g = 51;

  printf("====================== [FACTORIAL] ======================\n\n");

  printf("Factorial:           %ld\n", factorial(e));
  printf("Recursive Facotrial: %ld\n\n", rec_factorial(e));

  printf("========================= [GCD] =========================\n\n");
  printf("GCD for           a = %ld, b = %ld: %ld\n", f, g, gcd(f, g));
  printf("Recursive GCD for a = %ld, b = %ld: %ld\n\n", f, g, rec_gcd(f, g));

  diophantine_equation_test();

  adafinal();

  return 0;
}
