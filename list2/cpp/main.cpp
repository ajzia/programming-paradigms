/*
  g++ main.cpp galois_field.cpp && ./a.out
*/
#include <iostream>
#include "galois_field.cpp"
#include <cassert>
#include <cmath>
#include <random>

using namespace std;

// random number generator
static random_device rd;    // obtain a random number from hardware
static mt19937 gen(rd());   // seed the generator
static uniform_int_distribution<> distr(-1234567890, 1234567890); // define the range

static const uint64_t TEST_PRIME = 1234567891;

static int mod(int64_t number, uint64_t mod) {
  return ((((number + mod) % mod) + mod) % mod);
}

void constructor_test(void) {
  cout << "CONSTRUCTOR TESTS:\n";

  const uint64_t x = abs(distr(gen));
  GaloisField<TEST_PRIME> gf1(x), gf2(-1);

  cout << "   positive number test:\n";
  cout << "     " << gf1 << ".number == " << mod(x, TEST_PRIME) << endl;
  assert(gf1.get_number() == mod(x, TEST_PRIME));
  cout << "     " << gf1 << ".order == " << TEST_PRIME << endl;
  assert(gf1.get_order() == TEST_PRIME);

  cout << "\n   negative number test:\n";
  cout << "     " << "GF<" << TEST_PRIME << ">(-1).number" << " == " << mod(-1, TEST_PRIME) << endl;
  assert(gf2.get_number() == mod(-1, TEST_PRIME));
  cout << "     " << gf2 << ".order == " << TEST_PRIME << endl;
  assert(gf2.get_order() == TEST_PRIME);

  cout << "  TESTS PASSED!\n";
}

void arithmetic_test(void) {
  cout << "\nARITHMETIC TESTS:\n";

  const uint64_t x = distr(gen), y = distr(gen), z = distr(gen);
  GaloisField<TEST_PRIME> gf1(x), gf2(y), gf3(z), temp(x);

  cout << "     + test:\n";
  cout << "       [" << gf1 << " + " << gf2 << "].get_number() == " << mod(gf1.get_number() + gf2.get_number(), TEST_PRIME) << endl;
  assert((gf1 + gf2).get_number() == mod(gf1.get_number() + gf2.get_number(), TEST_PRIME));
  cout << "     += test:\n";
  cout << "       [" << gf1 << " + " << gf2 << "] == " << "[" << gf1 << " += " << gf2 << "]\n";
  temp = gf1 + gf2;
  gf1 += gf2;
  assert(temp == gf1);

  cout << "\n     - test:\n";
  cout << "       [" << gf1 << " - " << gf2 << "].get_number() == " << mod(gf1.get_number() - gf2.get_number(), TEST_PRIME) << endl;
  assert((gf1 - gf2).get_number() == mod(gf1.get_number() - gf2.get_number(), TEST_PRIME));
  cout << "     -= test:\n";
  cout << "       [" << gf1 << " - " << gf2 << "] == " << "[" << gf1 << " -= " << gf2 << "]\n";
  temp = gf1 - gf2;
  gf1 -= gf2;
  assert(temp == gf1);

  cout << "\n     * test:\n";
  cout << "       [" << gf1 << " * " << gf2 << "].get_number() == " << mod(gf1.get_number() * gf2.get_number(), TEST_PRIME) << endl;
  assert((gf1 * gf2).get_number() == mod(gf1.get_number() * gf2.get_number(), TEST_PRIME));
  cout << "     *= test:\n";
  cout << "       [" << gf1 << " * " << gf2 << "] == " << "[" << gf1 << " *= " << gf2 << "]\n";
  temp = gf1 * gf2;
  gf1 *= gf2;
  assert(temp == gf1);

  cout << "\n     / test:\n";
  cout << "       [" << gf1 << " / " << gf2 << "].get_number() == " << mod(gf1.get_number() * gf2.mod_inverse().get_number(), TEST_PRIME) << endl;
  assert((gf1 / gf2).get_number() == mod(gf1.get_number() * gf2.mod_inverse().get_number(), TEST_PRIME));
  // ultimate division test
  assert((gf1/gf2) * (gf1*gf2) == (gf1 * gf1));
  cout << "     /= test:\n";
  cout << "       [" << gf1 << " / " << gf2 << "] == " << "[" << gf1 << " /= " << gf2 << "]\n";
  temp = gf1 / gf2;
  gf1 /= gf2;
  assert(temp == gf1);

  cout << "  TESTS PASSED!\n";
}

void incrementation_test(void) {
  cout << "\nINCREMENTATION TESTS:\n";

  const uint64_t x = distr(gen), y = distr(gen), z = distr(gen);
  GaloisField<TEST_PRIME> gf1(x), gf2(y), gf3(z);

  cout << "     ++ test:\n";
  cout << "       [++" << gf2 << "] == [" << gf2 << "++] == " << "[" << gf2 << " + 1]\n";
  gf1 = gf2;
  gf3 = gf2;
  ++gf2;
  gf3++;
  assert(gf2 == gf3);
  assert(gf3 == (gf1 + 1));

  cout << "\n     -- test:\n";
  cout << "       [--" << gf2 << "] == [" << gf2 << "--] == " << "[" << gf2 << " - 1]\n";
  gf1 = gf2;
  gf3 = gf2;
  --gf2;
  gf3--;
  assert(gf2 == gf3);
  assert(gf3 == (gf1 - 1));

  cout << "  TESTS PASSED!\n";
}

void comparison_test(void) {
  cout << "\nCOMPARISON TESTS:\n";

  const uint64_t x = distr(gen), y = distr(gen);
  GaloisField<TEST_PRIME> gf1(x), gf2(y), gf3(0), gf4(TEST_PRIME + 1);

  cout << "     < tests:\n";
  cout << "       [" << gf1 << " < " << gf2 << "] == " << "[" << mod(x, TEST_PRIME) << " < " << mod(y, TEST_PRIME) << "]\n";
  assert((gf1 < gf2) == (mod(x, TEST_PRIME) < mod(y, TEST_PRIME)));
  cout << "       [" << gf3 << " < GF<1234567891>(1234567891 + 1)]\n";
  assert(gf3 < gf4);


  cout << "\n     > tests:\n";
  cout << "       [" << gf1 << " > " << gf2 << "] == " << "[" << mod(x, TEST_PRIME) << " > " << mod(y, TEST_PRIME) << "]\n";
  assert((gf1 > gf2) == (mod(x, TEST_PRIME) > mod(y, TEST_PRIME)));
  gf3 += 2;
  cout << "       [" << gf3 << " > GF<1234567891>(1234567891 + 1)]\n";
  assert(gf3 > gf4);

  cout << "\n     <= tests:\n";
  cout << "       [" << gf1 << " <= " << gf2 << "] == " << "[" << mod(x, TEST_PRIME) << " <= " << mod(y, TEST_PRIME) << "]\n";
  assert((gf1 <= gf2) == (mod(x, TEST_PRIME) <= mod(y, TEST_PRIME)));
  gf3--;
  cout << "       [" << gf3 << " <= GF<1234567891>(1234567891 + 1)]\n";
  assert(gf3 <= gf4);

  cout << "\n     >= tests:\n";
  cout << "       [" << gf1 << " >= " << gf2 << "] == " << "[" << mod(x, TEST_PRIME) << " >= " << mod(y, TEST_PRIME) << "]\n";
  assert((gf1 >= gf2) == (mod(x, TEST_PRIME) >= mod(y, TEST_PRIME)));
  cout << "       [" << gf3 << " <= GF<1234567891>(1234567891 + 1)]\n";
  assert(gf3 <= gf4);

  cout << "\n     == tests:\n";
  cout << "       [" << gf1 << " == " << gf2 << "] == " << "[" << mod(x, TEST_PRIME) << " == " << mod(y, TEST_PRIME) << "]\n";
  assert((gf1 == gf2) == (mod(x, TEST_PRIME) == mod(y, TEST_PRIME)));
  cout << "       [" << gf3 << " == GF<1234567891>(1234567891 + 1)]\n";
  assert(gf3 == gf4);

  cout << "\n     != tests:\n";
  cout << "       [" << gf1 << " != " << gf2 << "] == " << "[" << mod(x, TEST_PRIME) << " != " << mod(y, TEST_PRIME) << "]\n";
  assert((gf1 != gf2) == (mod(x, TEST_PRIME) != mod(y, TEST_PRIME)));
  gf3--;
  cout << "       [" << gf3 << " != GF<1234567891>(1234567891 + 1)]\n";
  assert(gf3 != gf4); 

  cout << "\n     = tests:\n";
  int64_t n = 1537;
  cout << "       [" << gf1 << " = ("<< n << ")] == GF<" << gf1.get_order() << ">(" << mod(n, TEST_PRIME) << ")\n";
  gf1 = n;
  assert(gf1.get_number() == mod(n, TEST_PRIME)); 
  n = -1;
  cout << "       [" << gf1 << " = ("<< n << ")] == GF<" << gf1.get_order() << ">(" << mod(n, TEST_PRIME) << ")\n";
  gf1 = n;
  assert(gf1.get_number() == mod(n, TEST_PRIME)); 

  cout << "  TESTS PASSED!\n";
}

int main(void) {
  constructor_test();
  arithmetic_test();
  incrementation_test();
  comparison_test();

  return 0;
}
